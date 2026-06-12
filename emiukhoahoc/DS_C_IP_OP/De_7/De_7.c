/*
============================================================
 DE 7 (C) + FILE I/O: DANH SACH LIEN KET KEP cho SINH VIEN
   1. Doc tu input.txt vao DSLK kep (them vao DAU),
      xoa phan tu CUOI, tim theo MSSV.
   2. INSERTION SORT tren cac lien ket de xep TANG theo DTB,
      ghi ket qua ra output.txt.
 Format file: Ho ten, MSSV, d1, d2, d3, d4, d5
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

void AddFirst(DLIST *l, SINHVIEN sv) {
    DNODE *p = GetNode(sv);
    if (l->first == NULL) l->first = l->last = p;
    else { p->next = l->first; l->first->prev = p; l->first = p; }
}

void RemoveLast(DLIST *l) {
    if (l->last == NULL) return;
    DNODE *p = l->last;
    l->last = p->prev;
    if (l->last == NULL) l->first = NULL;
    else l->last->next = NULL;
    free(p);
}

DNODE* Search(DLIST *l, const char *mssv) {
    for (DNODE *p = l->first; p != NULL; p = p->next)
        if (strcmp(p->info.mssv, mssv) == 0) return p;
    return NULL;
}

void InDS(DLIST *l) {
    printf("%-22s %-12s %s\n", "Ho ten", "MSSV", "DTB");
    for (DNODE *p = l->first; p != NULL; p = p->next)
        printf("%-22s %-12s %.2f\n", p->info.hoten, p->info.mssv, DTB(p->info));
}

void Destroy(DLIST *l) {
    while (l->first != NULL) { DNODE *p = l->first; l->first = l->first->next; free(p); }
    l->last = NULL;
}

/* ---- 1. Doc input.txt bang fscanf -> them vao DAU danh sach ----
   %[^,] doc den khi gap dau phay; dau cach dau format bo qua khoang trang.
   Moi dong khop du 7 truong thi fscanf tra ve 7 -> tao 1 sinh vien. */
void DocFile(const char *tenFile, DLIST *l) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return; }
    SINHVIEN s;
    while (fscanf(fi, " %20[^,], %10[^,], %f, %f, %f, %f, %f",
                  s.hoten, s.mssv,
                  &s.diem[0], &s.diem[1], &s.diem[2], &s.diem[3], &s.diem[4]) == 7)
        AddFirst(l, s);
    fclose(fi);
}

void GhiFile(const char *tenFile, DLIST *l) {
    FILE *fo = fopen(tenFile, "wt");
    if (fo == NULL) { printf("Khong mo duoc %s de ghi!\n", tenFile); return; }
    for (DNODE *p = l->first; p != NULL; p = p->next) {
        fprintf(fo, "%s, %s", p->info.hoten, p->info.mssv);
        for (int j = 0; j < 5; j++) fprintf(fo, ", %g", p->info.diem[j]);
        fprintf(fo, "\n");
    }
    fclose(fo);
}

/* ============ INSERTION SORT tren DSLK kep (tang theo DTB) ============ */
void InsertionSortList(DLIST *l) {
    if (l->first == NULL) return;
    for (DNODE *i = l->first->next; i != NULL; i = i->next) {
        SINHVIEN x = i->info;
        DNODE *j = i->prev;
        while (j != NULL && DTB(j->info) > DTB(x)) {
            j->next->info = j->info;
            j = j->prev;
        }
        if (j == NULL) l->first->info = x;
        else j->next->info = x;
    }
}

int main(void) {
    DLIST l; Init(&l);
    DocFile("input.txt", &l);
    if (l.first == NULL) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt (them vao dau):\n"); InDS(&l);

    DNODE *q = Search(&l, "2020000004");
    printf("\nTim MSSV 2020000004: %s\n", q ? q->info.hoten : "khong thay");

    RemoveLast(&l);
    printf("\nSau khi XOA phan tu cuoi:\n"); InDS(&l);

    InsertionSortList(&l);
    printf("\nSau INSERTION SORT (tang theo DTB):\n"); InDS(&l);

    GhiFile("output.txt", &l);
    printf("\nDa ghi ket qua vao output.txt\n");

    Destroy(&l);
    return 0;
}
