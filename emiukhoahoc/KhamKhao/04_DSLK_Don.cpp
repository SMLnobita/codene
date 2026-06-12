/*
============================================================
 ON TAP 4a: DANH SACH LIEN KET DON (Singly Linked List)
============================================================
 - Moi node: data + con tro link tro toi node sau.
 - LIST quan ly bang 2 con tro: first (dau) va last (cuoi).
 - Cac thao tac: tao rong, them (dau/cuoi/sau q), xoa
   (dau/cuoi/sau q), tim kiem, duyet, huy toan bo.
 Luu y kinh dien:
 - Them/xoa phai xet rieng truong hop danh sach RONG.
 - Xoa node phai free de tranh ro ri bo nho.
============================================================
*/
#include <cstdio>
#include <cstdlib>

struct NODE {
    int data;
    NODE *link;     // tro node ke tiep
};

struct LIST {
    NODE *first;
    NODE *last;
};

// ---- Tao danh sach rong ----
void Init(LIST &l) {
    l.first = l.last = NULL;
}

// ---- Tao node moi ----
NODE* GetNode(int x) {
    NODE *p = new NODE;
    if (p == NULL) { printf("Het bo nho!\n"); exit(1); }
    p->data = x;
    p->link = NULL;
    return p;
}

// ---- Them vao DAU danh sach ----
void AddFirst(LIST &l, NODE *new_ele) {
    if (l.first == NULL) {            // danh sach rong
        l.first = l.last = new_ele;
    } else {
        new_ele->link = l.first;
        l.first = new_ele;
    }
}

// ---- Them vao CUOI danh sach ----
void AddLast(LIST &l, NODE *new_ele) {
    if (l.first == NULL) {
        l.first = l.last = new_ele;
    } else {
        l.last->link = new_ele;
        l.last = new_ele;
    }
}

// ---- Them sau node q ----
void AddAfter(LIST &l, NODE *new_ele, NODE *q) {
    if (q != NULL) {
        new_ele->link = q->link;
        q->link = new_ele;
        if (q == l.last) l.last = new_ele;
    } else {
        AddFirst(l, new_ele);          // q NULL -> them dau
    }
}

// ---- Tim node co data = x ----
NODE* Search(LIST l, int x) {
    NODE *p = l.first;
    while (p != NULL && p->data != x)
        p = p->link;
    return p;                          // NULL neu khong thay
}

// ---- Xoa node DAU ----
void RemoveFirst(LIST &l) {
    if (l.first == NULL) return;       // rong, khong xoa
    NODE *p = l.first;
    l.first = p->link;
    if (l.first == NULL) l.last = NULL; // ds tro thanh rong
    delete p;
}

// ---- Xoa node SAU q ----
void RemoveAfter(LIST &l, NODE *q) {
    if (q == NULL || q->link == NULL) return;
    NODE *p = q->link;                 // p la node can xoa
    q->link = p->link;
    if (p == l.last) l.last = q;
    delete p;
}

// ---- Xoa node CUOI (phai tim node truoc last) ----
void RemoveLast(LIST &l) {
    if (l.first == NULL) return;
    if (l.first == l.last) { RemoveFirst(l); return; }  // 1 phan tu
    NODE *q = l.first;
    while (q->link != l.last) q = q->link;  // q: node truoc last
    delete l.last;
    q->link = NULL;
    l.last = q;
}

// ---- Xoa node co gia tri x ----
bool RemoveX(LIST &l, int x) {
    NODE *q = NULL, *p = l.first;
    while (p != NULL && p->data != x) { q = p; p = p->link; }
    if (p == NULL) return false;       // khong thay
    if (q == NULL) RemoveFirst(l);     // x o dau
    else RemoveAfter(l, q);
    return true;
}

// ---- Duyet danh sach ----
void PrintList(LIST l) {
    for (NODE *p = l.first; p != NULL; p = p->link)
        printf("%d -> ", p->data);
    printf("NULL\n");
}

// ---- Huy toan bo danh sach ----
void Destroy(LIST &l) {
    while (l.first != NULL) {
        NODE *p = l.first;
        l.first = l.first->link;
        delete p;
    }
    l.last = NULL;
}

int main() {
    LIST l;
    Init(l);

    AddLast(l, GetNode(10));
    AddLast(l, GetNode(20));
    AddLast(l, GetNode(30));
    AddFirst(l, GetNode(5));
    printf("Sau khi them      : "); PrintList(l);   // 5 10 20 30

    NODE *q = Search(l, 20);
    if (q) AddAfter(l, GetNode(25), q);
    printf("Them 25 sau 20    : "); PrintList(l);   // 5 10 20 25 30

    RemoveFirst(l);
    printf("Xoa dau           : "); PrintList(l);   // 10 20 25 30
    RemoveLast(l);
    printf("Xoa cuoi          : "); PrintList(l);   // 10 20 25
    RemoveX(l, 20);
    printf("Xoa node 20       : "); PrintList(l);   // 10 25

    printf("Tim 25: %s\n", Search(l, 25) ? "thay" : "khong thay");
    printf("Tim 99: %s\n", Search(l, 99) ? "thay" : "khong thay");

    Destroy(l);
    printf("Sau khi huy       : "); PrintList(l);   // NULL
    return 0;
}
