/*
============================================================
 DE 12 (2026): CAY NHI PHAN TIM KIEM (BST) - khoa la MSSV
   SINH VIEN: ho ten, MSSV (10 chu so), ngay sinh, 5 diem.
   1. Cai dat BST dung danh sach lien ket, dung MSSV lam khoa.
   2. Them mot node vao cay.
   3. Tim node theo MSSV va xoa node khoi cay.
   4. In duong di cua cay theo NLR, LNR, LRN.
 Format input.txt: Ho ten, MSSV, dd/mm/yyyy, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstring>

struct NGAYSINH { int ngay, thang, nam; };
struct SINHVIEN {
    char hoten[21];
    char mssv[11];
    NGAYSINH ns;
    float diem[5];
};

struct NODE {
    SINHVIEN info;
    NODE *left, *right;
};
typedef NODE* Tree;

void Init(Tree &t) { t = NULL; }

NODE* GetNode(const SINHVIEN &sv) {
    NODE *p = new NODE;
    p->info = sv;
    p->left = p->right = NULL;
    return p;
}

/* ---- 2. Them node vao BST theo khoa MSSV (so sanh chuoi) ---- */
int InsertNode(Tree &t, const SINHVIEN &sv) {
    if (t == NULL) { t = GetNode(sv); return 1; }
    int c = strcmp(sv.mssv, t->info.mssv);
    if (c == 0) return 0;                 // trung MSSV -> khong them
    if (c < 0) return InsertNode(t->left, sv);
    return InsertNode(t->right, sv);
}

/* ---- 3a. Tim node theo MSSV ---- */
NODE* SearchNode(Tree t, const char *mssv) {
    while (t != NULL) {
        int c = strcmp(mssv, t->info.mssv);
        if (c == 0) return t;
        t = (c < 0) ? t->left : t->right;
    }
    return NULL;
}

/* ---- 3b. Xoa node theo MSSV (3 truong hop) ---- */
void TheMangNhoNhatPhai(Tree &p, Tree &q) {
    if (q->left != NULL) TheMangNhoNhatPhai(p, q->left);
    else { p->info = q->info; p = q; q = q->right; }
}

int DeleteNode(Tree &t, const char *mssv) {
    if (t == NULL) return 0;
    int c = strcmp(mssv, t->info.mssv);
    if (c < 0) return DeleteNode(t->left, mssv);
    if (c > 0) return DeleteNode(t->right, mssv);
    NODE *p = t;                          // tim thay node can xoa
    if (t->left == NULL) t = t->right;
    else if (t->right == NULL) t = t->left;
    else TheMangNhoNhatPhai(p, t->right);
    delete p;
    return 1;
}

/* ---- 4. Cac cach duyet ---- */
void NLR(Tree t) {
    if (t == NULL) return;
    printf("%s(%s) ", t->info.mssv, t->info.hoten);
    NLR(t->left);
    NLR(t->right);
}
void LNR(Tree t) {                        // -> tang dan theo MSSV
    if (t == NULL) return;
    LNR(t->left);
    printf("%s(%s) ", t->info.mssv, t->info.hoten);
    LNR(t->right);
}
void LRN(Tree t) {
    if (t == NULL) return;
    LRN(t->left);
    LRN(t->right);
    printf("%s(%s) ", t->info.mssv, t->info.hoten);
}

void DestroyTree(Tree &t) {
    if (t == NULL) return;
    DestroyTree(t->left);
    DestroyTree(t->right);
    delete t;
    t = NULL;
}

/* ---- Doc input.txt va dung cay ---- */
int DocFileVaTaoCay(const char *tenFile, Tree &t) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return 0; }
    SINHVIEN s;
    int dem = 0;
    while (fscanf(fi, " %20[^,], %10[^,], %d/%d/%d, %f, %f, %f, %f, %f",
                  s.hoten, s.mssv,
                  &s.ns.ngay, &s.ns.thang, &s.ns.nam,
                  &s.diem[0], &s.diem[1], &s.diem[2], &s.diem[3], &s.diem[4]) == 10) {
        if (InsertNode(t, s)) dem++;
    }
    fclose(fi);
    return dem;
}

int main() {
    Tree t; Init(t);
    int n = DocFileVaTaoCay("input.txt", t);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }
    printf("Da tao BST tu %d sinh vien (khoa = MSSV).\n", n);

    printf("\nNLR: "); NLR(t); printf("\n");
    printf("LNR: "); LNR(t); printf("\n");   // tang dan theo MSSV
    printf("LRN: "); LRN(t); printf("\n");

    // 2. Them 1 node moi
    SINHVIEN sv = {"Le Thi Moi", "2320000200", {1, 1, 2005}, {7, 7, 7, 7, 7}};
    InsertNode(t, sv);
    printf("\nSau khi THEM 2320000200 (LNR): "); LNR(t); printf("\n");

    // 3. Tim va xoa theo MSSV
    const char *xoa = "2320000010";
    if (SearchNode(t, xoa)) {
        DeleteNode(t, xoa);
        printf("Sau khi XOA %s (LNR)       : ", xoa); LNR(t); printf("\n");
    } else printf("Khong tim thay %s de xoa\n", xoa);

    DestroyTree(t);
    return 0;
}
