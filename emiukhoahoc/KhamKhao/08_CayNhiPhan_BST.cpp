/*
============================================================
 ON TAP 6: CAY NHI PHAN TIM KIEM (BST)
============================================================
 - Cay nhi phan: moi nut co toi da 2 con (trai, phai).
 - BST: voi moi nut, khoa cay con TRAI < khoa nut < khoa cay con PHAI.
 - Chi phi tim kiem trung binh: O(log n).

 3 cach duyet:
   NLR (preorder) : Nut -> Trai -> Phai
   LNR (inorder)  : Trai -> Nut -> Phai  (BST: ra day TANG DAN)
   LRN (postorder): Trai -> Phai -> Nut

 Xoa nut X co 3 truong hop:
   1. X la nut LA           -> xoa truc tiep
   2. X co 1 con            -> noi cha cua X voi con cua X
   3. X co 2 con            -> the X bang nut nho nhat ben cay
                               con phai (hoac lon nhat ben trai),
                               roi xoa nut the mang.
============================================================
*/
#include <cstdio>
#include <cstdlib>

struct NODE {
    int key;
    NODE *left, *right;
};
typedef NODE* Tree;

void Init(Tree &t) { t = NULL; }

NODE* GetNode(int x) {
    NODE *p = new NODE;
    p->key = x;
    p->left = p->right = NULL;
    return p;
}

/* ---- Them nut vao BST (de quy) ----
   tra ve 1: thanh cong, 0: trung khoa */
int InsertNode(Tree &t, int x) {
    if (t == NULL) {              // vi tri can chen
        t = GetNode(x);
        return 1;
    }
    if (x == t->key) return 0;    // khong cho trung khoa
    if (x < t->key)  return InsertNode(t->left, x);
    return InsertNode(t->right, x);
}

/* ---- Tim kiem tren BST ---- */
NODE* SearchNode(Tree t, int x) {
    if (t == NULL) return NULL;
    if (x == t->key) return t;
    if (x < t->key)  return SearchNode(t->left, x);
    return SearchNode(t->right, x);
}

/* ---- 3 cach duyet ---- */
void NLR(Tree t) {                       // preorder
    if (t == NULL) return;
    printf("%d ", t->key);               // N
    NLR(t->left);                        // L
    NLR(t->right);                       // R
}

void LNR(Tree t) {                       // inorder -> tang dan
    if (t == NULL) return;
    LNR(t->left);
    printf("%d ", t->key);
    LNR(t->right);
}

void LRN(Tree t) {                       // postorder
    if (t == NULL) return;
    LRN(t->left);
    LRN(t->right);
    printf("%d ", t->key);
}

/* ---- Xoa nut khoa x ----
   searchStandFor: tim nut NHO NHAT ben cay con phai de the mang */
void searchStandFor(Tree &p, Tree &q) {  // p: nut the, q: cay con phai
    if (q->left != NULL)
        searchStandFor(p, q->left);
    else {
        p->key = q->key;                 // chep khoa nut the vao p
        p = q;                           // p tro vao nut se bi xoa that
        q = q->right;                    // noi lai cay
    }
}

int DeleteNode(Tree &t, int x) {
    if (t == NULL) return 0;             // khong tim thay
    if (x < t->key) return DeleteNode(t->left, x);
    if (x > t->key) return DeleteNode(t->right, x);
    // tim thay: t la nut can xoa
    NODE *p = t;
    if (t->left == NULL)                 // TH1+TH2: khong co con trai
        t = t->right;
    else if (t->right == NULL)           // TH2: chi co con trai
        t = t->left;
    else                                 // TH3: du 2 con
        searchStandFor(p, t->right);
    delete p;
    return 1;
}

/* ---- Dem nut, tinh chieu cao, dem nut la ---- */
int CountNode(Tree t) {
    if (t == NULL) return 0;
    return 1 + CountNode(t->left) + CountNode(t->right);
}

int Height(Tree t) {
    if (t == NULL) return 0;
    int hl = Height(t->left), hr = Height(t->right);
    return 1 + (hl > hr ? hl : hr);
}

int CountLeaf(Tree t) {
    if (t == NULL) return 0;
    if (t->left == NULL && t->right == NULL) return 1;
    return CountLeaf(t->left) + CountLeaf(t->right);
}

/* ---- Huy toan bo cay (phai dung LRN: xoa con truoc, cha sau) ---- */
void DestroyTree(Tree &t) {
    if (t == NULL) return;
    DestroyTree(t->left);
    DestroyTree(t->right);
    delete t;
    t = NULL;
}

int main() {
    Tree t;
    Init(t);

    int keys[] = {44, 18, 88, 13, 37, 59, 108, 15, 23, 40, 55, 71};
    int n = sizeof(keys) / sizeof(int);
    for (int i = 0; i < n; i++)
        InsertNode(t, keys[i]);

    printf("Duyet NLR (preorder) : "); NLR(t); printf("\n");
    printf("Duyet LNR (inorder)  : "); LNR(t); printf("\n");  // tang dan!
    printf("Duyet LRN (postorder): "); LRN(t); printf("\n");

    printf("\nSo nut    : %d\n", CountNode(t));
    printf("Chieu cao : %d\n", Height(t));
    printf("So nut la : %d\n", CountLeaf(t));

    printf("\nTim 59 : %s\n", SearchNode(t, 59) ? "thay" : "khong");
    printf("Tim 100: %s\n", SearchNode(t, 100) ? "thay" : "khong");

    // Xoa thu 3 truong hop
    DeleteNode(t, 40);    // nut la
    printf("\nXoa 40 (nut la)   , LNR: "); LNR(t); printf("\n");
    DeleteNode(t, 13);    // 1 con
    printf("Xoa 13 (mot con)  , LNR: "); LNR(t); printf("\n");
    DeleteNode(t, 44);    // 2 con (goc)
    printf("Xoa 44 (hai con)  , LNR: "); LNR(t); printf("\n");

    DestroyTree(t);
    printf("\nDa huy cay, so nut = %d\n", CountNode(t));
    return 0;
}
