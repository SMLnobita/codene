/*
============================================================
 DE 8: DANH SACH LIEN KET KEP cho day SINH VIEN
   - Ho ten: toi da 20 ki tu | MSSV: 10 ki tu so | 5 diem so thuc
 Yeu cau:
   1. DSLK kep: them vao DAU, xoa phan tu CUOI, tim theo MSSV.
   2. RADIX SORT tren cac lien ket cua danh sach de xep
      TANG theo ma so sinh vien (10 chu so).
============================================================
*/
#include <cstdio>
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

// Them san mot node (dung lai khi ghep lo) - khong cap phat moi
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

DNODE* Search(DLIST l, const char *mssv) {
    for (DNODE *p = l.first; p != NULL; p = p->next)
        if (strcmp(p->info.mssv, mssv) == 0) return p;
    return NULL;
}

void InDS(DLIST l) {
    printf("%-12s %-22s %s\n", "MSSV", "Ho ten", "DTB");
    for (DNODE *p = l.first; p != NULL; p = p->next)
        printf("%-12s %-22s %.2f\n", p->info.mssv, p->info.hoten, DTB(p->info));
}

void Destroy(DLIST &l) {
    while (l.first != NULL) { DNODE *p = l.first; l.first = l.first->next; delete p; }
    l.last = NULL;
}

/* ============ RADIX SORT tren DSLK kep (tang theo MSSV) ============
   MSSV la chuoi 10 chu so. Xu ly tung vi tri ki tu tu PHAI sang TRAI.
   Moi vong: tach cac node vao 10 lo (0..9) roi noi lai theo thu tu lo. */
void RadixSortList(DLIST &l) {
    if (l.first == NULL || l.first == l.last) return;

    for (int pos = LEN_MSSV - 1; pos >= 0; pos--) {
        DLIST bucket[10];
        for (int d = 0; d < 10; d++) Init(bucket[d]);

        while (l.first != NULL) {               // go tung node ra phan lo
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

    SINHVIEN mau[] = {
        {"Nguyen Van A", "2020000089", {7, 8, 6, 9, 5}},
        {"Tran Thi B",   "2020000012", {9, 9, 8, 10, 9}},
        {"Le Van C",     "2020000305", {5, 6, 4, 7, 5}},
        {"Pham Thi D",   "2020000004", {8, 7, 9, 6, 8}},
    };
    for (int i = 0; i < 4; i++) AddFirst(l, mau[i]);   // them vao dau

    printf("DANH SACH (them vao dau):\n"); InDS(l);

    DNODE *q = Search(l, "2020000305");
    printf("\nTim MSSV 2020000305: %s\n", q ? q->info.hoten : "khong thay");

    RemoveLast(l);
    printf("\nSau khi XOA phan tu cuoi:\n"); InDS(l);

    RadixSortList(l);
    printf("\nSau RADIX SORT (tang theo MSSV):\n"); InDS(l);

    Destroy(l);
    return 0;
}
