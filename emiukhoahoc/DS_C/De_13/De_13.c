/*
============================================================
 DE 13 (C): CAY NHI PHAN TIM KIEM (BST) bang danh sach lien ket
   1. Cai dat BST. 2. Them node. 3. Xoa node.
   4. In duong di cua cay theo LRN (Left - Right - Node, postorder).
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

int InsertNode(Tree *t, int x) {
    if (*t == NULL) { *t = GetNode(x); return 1; }
    if (x == (*t)->key) return 0;
    if (x < (*t)->key) return InsertNode(&(*t)->left, x);
    return InsertNode(&(*t)->right, x);
}

void searchStandFor(Tree *p, Tree *q) {
    if ((*q)->left != NULL) searchStandFor(p, &(*q)->left);
    else { (*p)->key = (*q)->key; *p = *q; *q = (*q)->right; }
}

int DeleteNode(Tree *t, int x) {
    if (*t == NULL) return 0;
    if (x < (*t)->key) return DeleteNode(&(*t)->left, x);
    if (x > (*t)->key) return DeleteNode(&(*t)->right, x);
    NODE *p = *t;
    if ((*t)->left == NULL) *t = (*t)->right;
    else if ((*t)->right == NULL) *t = (*t)->left;
    else searchStandFor(&p, &(*t)->right);
    free(p);
    return 1;
}

/* ---- 4. Duyet LRN (postorder) ---- */
void LRN(Tree t) {
    if (t == NULL) return;
    LRN(t->left);
    LRN(t->right);
    printf("%d ", t->key);
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

    printf("Duyet LRN ban dau   : "); LRN(t); printf("\n");

    InsertNode(&t, 50);
    printf("Sau khi them 50 (LRN): "); LRN(t); printf("\n");

    DeleteNode(&t, 44);
    printf("Sau khi xoa 44 (LRN): "); LRN(t); printf("\n");

    DestroyTree(&t);
    return 0;
}
