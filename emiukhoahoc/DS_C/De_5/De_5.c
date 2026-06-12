/*
============================================================
 DE 5 (C): DANH SACH LIEN KET KEP cho day SINH VIEN
   - Ho ten: toi da 20 ki tu | MSSV: 10 ki tu so | 5 diem so thuc
 Yeu cau:
   1. DSLK kep: them vao DAU, xoa phan tu CUOI, tim theo MSSV.
   2. QUICK SORT tren cac lien ket de xep TANG theo DTB 5 mon.
============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char hoten[21];
    char mssv[11];
    float diem[5];
} SINHVIEN;

typedef struct DNODE {
    SINHVIEN info;
    struct DNODE *prev, *next;
} DNODE;

typedef struct {
    DNODE *first, *last;
} DLIST;

float DTB(SINHVIEN sv) {
    float tong = 0;
    for (int i = 0; i < 5; i++) tong += sv.diem[i];
    return tong / 5;
}

void Init(DLIST *l) { l->first = l->last = NULL; }

DNODE* GetNode(SINHVIEN sv) {
    DNODE *p = (DNODE*)malloc(sizeof(DNODE));
    p->info = sv;
    p->prev = p->next = NULL;
    return p;
}

/* ---- Them vao DAU ---- */
void AddFirst(DLIST *l, SINHVIEN sv) {
    DNODE *p = GetNode(sv);
    if (l->first == NULL) l->first = l->last = p;
    else {
        p->next = l->first;
        l->first->prev = p;
        l->first = p;
    }
}

/* ---- Xoa phan tu CUOI ---- */
void RemoveLast(DLIST *l) {
    if (l->last == NULL) return;
    DNODE *p = l->last;
    l->last = p->prev;
    if (l->last == NULL) l->first = NULL;
    else l->last->next = NULL;
    free(p);
}

/* ---- Tim theo MSSV ---- */
DNODE* Search(DLIST *l, const char *mssv) {
    for (DNODE *p = l->first; p != NULL; p = p->next)
        if (strcmp(p->info.mssv, mssv) == 0) return p;
    return NULL;
}

void InDS(DLIST *l) {
    printf("%-12s %-22s %s\n", "MSSV", "Ho ten", "DTB");
    for (DNODE *p = l->first; p != NULL; p = p->next)
        printf("%-12s %-22s %.2f\n", p->info.mssv, p->info.hoten, DTB(p->info));
}

void Destroy(DLIST *l) {
    while (l->first != NULL) { DNODE *p = l->first; l->first = l->first->next; free(p); }
    l->last = NULL;
}

/* ============ QUICK SORT tren DSLK kep (tang theo DTB) ============
   Phan hoach Lomuto: chot la node "high", hoan vi DU LIEU (info)
   giua cac node -> giu nguyen cau truc lien ket. */
void hoanvi(SINHVIEN *a, SINHVIEN *b) { SINHVIEN t = *a; *a = *b; *b = t; }

DNODE* Partition(DNODE *low, DNODE *high) {
    float pivot = DTB(high->info);
    DNODE *i = low->prev;
    for (DNODE *j = low; j != high; j = j->next) {
        if (DTB(j->info) <= pivot) {
            i = (i == NULL) ? low : i->next;
            hoanvi(&i->info, &j->info);
        }
    }
    i = (i == NULL) ? low : i->next;
    hoanvi(&i->info, &high->info);
    return i;
}

void QuickSort(DNODE *low, DNODE *high) {
    if (high != NULL && low != high && low != high->next) {
        DNODE *p = Partition(low, high);
        QuickSort(low, p->prev);
        QuickSort(p->next, high);
    }
}

void QuickSortList(DLIST *l) { QuickSort(l->first, l->last); }

int main(void) {
    DLIST l; Init(&l);

    SINHVIEN mau[] = {
        {"Nguyen Van A", "2020000001", {7, 8, 6, 9, 5}},
        {"Tran Thi B",   "2020000002", {9, 9, 8, 10, 9}},
        {"Le Van C",     "2020000003", {5, 6, 4, 7, 5}},
        {"Pham Thi D",   "2020000004", {8, 7, 9, 6, 8}},
    };
    for (int i = 0; i < 4; i++) AddFirst(&l, mau[i]);   /* them vao dau */

    printf("DANH SACH (them vao dau):\n"); InDS(&l);

    DNODE *q = Search(&l, "2020000002");
    printf("\nTim MSSV 2020000002: %s\n", q ? q->info.hoten : "khong thay");

    RemoveLast(&l);
    printf("\nSau khi XOA phan tu cuoi:\n"); InDS(&l);

    QuickSortList(&l);
    printf("\nSau QUICK SORT (tang theo DTB):\n"); InDS(&l);

    Destroy(&l);
    return 0;
}
