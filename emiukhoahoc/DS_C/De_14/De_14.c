/*
============================================================
 DE 14 (C): CAY NHI PHAN AVL bang danh sach lien ket
   1. Cai dat cay AVL.
   2. Tao ngau nhien cay AVL tu mot mang chu so.
   3. Them mot node co gia tri ngau nhien vao AVL.
   4. Can bang lai cay AVL (cac phep quay LL, RR, LR, RL).
============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {
    int key;
    int height;             /* chieu cao node (de tinh do lech) */
    struct NODE *left, *right;
} NODE;
typedef NODE* AVLTree;

int Height(NODE *p) { return p == NULL ? 0 : p->height; }
int Max(int a, int b) { return a > b ? a : b; }

NODE* GetNode(int x) {
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p->key = x;
    p->height = 1;
    p->left = p->right = NULL;
    return p;
}

int BalanceFactor(NODE *p) {
    return p == NULL ? 0 : Height(p->left) - Height(p->right);
}

void CapNhatChieuCao(NODE *p) {
    p->height = 1 + Max(Height(p->left), Height(p->right));
}

/* ---- Phep quay phai (xu ly lech trai - truong hop LL) ---- */
NODE* QuayPhai(NODE *y) {
    NODE *x = y->left;
    NODE *T2 = x->right;
    x->right = y;
    y->left = T2;
    CapNhatChieuCao(y);
    CapNhatChieuCao(x);
    return x;
}

/* ---- Phep quay trai (xu ly lech phai - truong hop RR) ---- */
NODE* QuayTrai(NODE *x) {
    NODE *y = x->right;
    NODE *T2 = y->left;
    y->left = x;
    x->right = T2;
    CapNhatChieuCao(x);
    CapNhatChieuCao(y);
    return y;
}

/* ---- 4. Can bang lai mot node theo do lech ---- */
NODE* CanBang(NODE *p) {
    CapNhatChieuCao(p);
    int bf = BalanceFactor(p);
    if (bf > 1) {                          /* lech TRAI */
        if (BalanceFactor(p->left) < 0)    /* truong hop LR */
            p->left = QuayTrai(p->left);
        return QuayPhai(p);
    }
    if (bf < -1) {                         /* lech PHAI */
        if (BalanceFactor(p->right) > 0)   /* truong hop RL */
            p->right = QuayPhai(p->right);
        return QuayTrai(p);
    }
    return p;
}

/* ---- 3. Them node vao AVL roi tu can bang ---- */
NODE* InsertNode(NODE *t, int x) {
    if (t == NULL) return GetNode(x);
    if (x < t->key)      t->left  = InsertNode(t->left, x);
    else if (x > t->key) t->right = InsertNode(t->right, x);
    else return t;                         /* khong cho trung khoa */
    return CanBang(t);
}

/* ---- 2. Tao cay AVL tu mot mang chu so ---- */
AVLTree TaoTuMang(int a[], int n) {
    AVLTree t = NULL;
    for (int i = 0; i < n; i++) t = InsertNode(t, a[i]);
    return t;
}

/* ---- Tao ngau nhien AVL tu n gia tri ngau nhien ---- */
AVLTree TaoNgauNhien(int n) {
    AVLTree t = NULL;
    for (int i = 0; i < n; i++) t = InsertNode(t, rand() % 100);
    return t;
}

void LNR(NODE *t) {
    if (t == NULL) return;
    LNR(t->left);
    printf("%d ", t->key);
    LNR(t->right);
}

void InCay(NODE *t, int muc) {
    if (t == NULL) return;
    InCay(t->right, muc + 1);
    for (int i = 0; i < muc; i++) printf("      ");
    printf("%d(bf=%d)\n", t->key, BalanceFactor(t));
    InCay(t->left, muc + 1);
}

void Destroy(NODE *t) {
    if (t == NULL) return;
    Destroy(t->left);
    Destroy(t->right);
    free(t);
}

int main(void) {
    srand((unsigned)time(NULL));

    /* 2. Tao AVL tu mang chu so co san */
    int a[] = {30, 20, 40, 10, 25, 35, 50, 5, 15};
    int n = sizeof(a) / sizeof(int);
    AVLTree t = TaoTuMang(a, n);

    printf("Cay AVL tu mang chu so (LNR): "); LNR(t); printf("\n");
    printf("Chieu cao cay = %d\n\n", Height(t));
    printf("Cau truc cay (xoay 90 do):\n"); InCay(t, 0);

    /* 3. Them mot node co gia tri ngau nhien */
    int x = rand() % 100;
    printf("\nThem gia tri ngau nhien: %d\n", x);
    t = InsertNode(t, x);
    printf("Sau khi them (LNR): "); LNR(t); printf("\n");
    printf("Chieu cao cay = %d (cay van can bang)\n", Height(t));

    Destroy(t);
    return 0;
}
