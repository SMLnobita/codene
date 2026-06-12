/*
============================================================
 DE 8 (C++) + FILE I/O: DANH SACH LIEN KET KEP cho SINH VIEN
   1. Doc tu input.txt vao DSLK kep (them vao DAU),
      xoa phan tu CUOI, tim theo MSSV.
   2. RADIX SORT tren cac lien ket de xep TANG theo MSSV (10 chu so),
      ghi ket qua ra output.txt.
 Format file: Ho ten, MSSV, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define LEN_MSSV 10

struct SINHVIEN {
    char hoten[21];
    char mssv[11];
    float diem[5];
};

struct DNODE {
    SINHVIEN info;
    DNODE *prev, *next;
};

struct DLIST {
    DNODE *first, *last;
};

float DTB(const SINHVIEN &sv) {
    float tong = 0;
    for (int i = 0; i < 5; i++) tong += sv.diem[i];
    return tong / 5;
}

void Init(DLIST &l) { l.first = l.last = NULL; }

DNODE* GetNode(const SINHVIEN &sv) {
    DNODE *p = new DNODE;
    p->info = sv;
    p->prev = p->next = NULL;
    return p;
}

void AddFirst(DLIST &l, const SINHVIEN &sv) {
    DNODE *p = GetNode(sv);
    if (l.first == NULL) l.first = l.last = p;
    else { p->next = l.first; l.first->prev = p; l.first = p; }
}

// Noi lai mot node co san vao cuoi (dung khi ghep lo radix)
void AddNodeLast(DLIST &l, DNODE *p) {
    p->prev = p->next = NULL;
    if (l.first == NULL) l.first = l.last = p;
    else { l.last->next = p; p->prev = l.last; l.last = p; }
}

void RemoveLast(DLIST &l) {
    if (l.last == NULL) return;
    DNODE *p = l.last;
    l.last = p->prev;
    if (l.last == NULL) l.first = NULL;
    else l.last->next = NULL;
    delete p;
}

DNODE* Search(DLIST &l, const char *mssv) {
    for (DNODE *p = l.first; p != NULL; p = p->next)
        if (strcmp(p->info.mssv, mssv) == 0) return p;
    return NULL;
}

void InDS(DLIST &l) {
    printf("%-22s %-12s %s\n", "Ho ten", "MSSV", "DTB");
    for (DNODE *p = l.first; p != NULL; p = p->next)
        printf("%-22s %-12s %.2f\n", p->info.hoten, p->info.mssv, DTB(p->info));
}

void Destroy(DLIST &l) {
    while (l.first != NULL) { DNODE *p = l.first; l.first = l.first->next; delete p; }
    l.last = NULL;
}

// ---- 1. Doc input.txt bang fscanf -> them vao DAU danh sach ----
//   %[^,] doc den khi gap dau phay; dau cach dau format bo qua khoang trang.
//   Moi dong khop du 7 truong thi fscanf tra ve 7 -> tao 1 sinh vien.
void DocFile(const char *tenFile, DLIST &l) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return; }
    SINHVIEN s;
    while (fscanf(fi, " %20[^,], %10[^,], %f, %f, %f, %f, %f",
                  s.hoten, s.mssv,
                  &s.diem[0], &s.diem[1], &s.diem[2], &s.diem[3], &s.diem[4]) == 7)
        AddFirst(l, s);
    fclose(fi);
}

void GhiFile(const char *tenFile, DLIST &l) {
    FILE *fo = fopen(tenFile, "wt");
    if (fo == NULL) { printf("Khong mo duoc %s de ghi!\n", tenFile); return; }
    for (DNODE *p = l.first; p != NULL; p = p->next) {
        fprintf(fo, "%s, %s", p->info.hoten, p->info.mssv);
        for (int j = 0; j < 5; j++) fprintf(fo, ", %g", p->info.diem[j]);
        fprintf(fo, "\n");
    }
    fclose(fo);
}

/* ============ RADIX SORT tren DSLK kep (tang theo MSSV) ============ */
void RadixSortList(DLIST &l) {
    if (l.first == NULL || l.first == l.last) return;
    for (int pos = LEN_MSSV - 1; pos >= 0; pos--) {
        DLIST bucket[10];
        for (int d = 0; d < 10; d++) Init(bucket[d]);

        while (l.first != NULL) {              // go tung node ra phan lo
            DNODE *p = l.first;
            l.first = l.first->next;
            int d = p->info.mssv[pos] - '0';
            AddNodeLast(bucket[d], p);
        }
        Init(l);
        for (int d = 0; d < 10; d++) {          // noi cac lo lai theo thu tu
            DNODE *p = bucket[d].first;
            while (p != NULL) {
                DNODE *next = p->next;
                AddNodeLast(l, p);
                p = next;
            }
        }
    }
}

int main() {
    DLIST l; Init(l);
    DocFile("input.txt", l);
    if (l.first == NULL) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt (them vao dau):\n"); InDS(l);

    DNODE *q = Search(l, "2020000305");
    printf("\nTim MSSV 2020000305: %s\n", q ? q->info.hoten : "khong thay");

    RemoveLast(l);
    printf("\nSau khi XOA phan tu cuoi:\n"); InDS(l);

    RadixSortList(l);
    printf("\nSau RADIX SORT (tang theo MSSV):\n"); InDS(l);

    GhiFile("output.txt", l);
    printf("\nDa ghi ket qua vao output.txt\n");

    Destroy(l);
    return 0;
}
