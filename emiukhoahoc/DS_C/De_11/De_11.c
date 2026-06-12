/*
============================================================
 DE 11 (C): CAY NHI PHAN TIM KIEM (BST) bang danh sach lien ket
   1. Cai dat BST. 2. Them node. 3. Xoa node.
   4. In duong di cua cay theo NLR (Node - Left - Right, preorder).
============================================================
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int key;
    struct NODE *left, *right;
} NODE;
typedef NODE* Tree;

void Init(Tree *t) { *t = NULL; }

NODE* GetNode(int x) {
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p->key = x;
    p->left = p->right = NULL;
    return p;
}

/* ---- 2. Them node vao BST (khong cho trung khoa) ---- */
int InsertNode(Tree *t, int x) {
    if (*t == NULL) { *t = GetNode(x); return 1; }
    if (x == (*t)->key) return 0;
    if (x < (*t)->key) return InsertNode(&(*t)->left, x);
    return InsertNode(&(*t)->right, x);
}

/* ---- 3. Xoa node: the mang bang node nho nhat ben cay con phai ---- */
void searchStandFor(Tree *p, Tree *q) {
    if ((*q)->left != NULL) searchStandFor(p, &(*q)->left);
    else {
        (*p)->key = (*q)->key;      /* chep khoa nut the */
        *p = *q;                    /* p tro vao nut se xoa that */
        *q = (*q)->right;           /* noi lai cay */
    }
}

int DeleteNode(Tree *t, int x) {
    if (*t == NULL) return 0;                       /* khong tim thay */
    if (x < (*t)->key) return DeleteNode(&(*t)->left, x);
    if (x > (*t)->key) return DeleteNode(&(*t)->right, x);
    NODE *p = *t;                                   /* tim thay node can xoa */
    if ((*t)->left == NULL) *t = (*t)->right;       /* 0 hoac chi con phai */
    else if ((*t)->right == NULL) *t = (*t)->left;  /* chi con trai */
    else searchStandFor(&p, &(*t)->right);          /* du 2 con */
    free(p);
    return 1;
}

/* ---- 4. Duyet NLR (preorder) ---- */
void NLR(Tree t) {
    if (t == NULL) return;
    printf("%d ", t->key);
    NLR(t->left);
    NLR(t->right);
}

void DestroyTree(Tree *t) {
    if (*t == NULL) return;
    DestroyTree(&(*t)->left);
    DestroyTree(&(*t)->right);
    free(*t);
    *t = NULL;
}

int main(void) {
    Tree t; Init(&t);

    int keys[] = {44, 18, 88, 13, 37, 59, 108, 15, 23, 40, 55, 71};
    int n = sizeof(keys) / sizeof(int);
    for (int i = 0; i < n; i++) InsertNode(&t, keys[i]);

    printf("Duyet NLR ban dau   : "); NLR(t); printf("\n");

    InsertNode(&t, 50);
    printf("Sau khi them 50 (NLR): "); NLR(t); printf("\n");

    DeleteNode(&t, 44);     /* xoa goc (node 2 con) */
    printf("Sau khi xoa 44 (NLR): "); NLR(t); printf("\n");

    DestroyTree(&t);
    return 0;
}
