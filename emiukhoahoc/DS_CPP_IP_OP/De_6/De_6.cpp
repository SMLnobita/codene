/*
============================================================
 DE 6 (C++) + FILE I/O: DANH SACH LIEN KET KEP cho SINH VIEN
   1. Doc tu input.txt vao DSLK kep (them vao CUOI),
      xoa phan tu DAU, tim theo MSSV.
   2. MERGE SORT tren cac lien ket de xep TANG theo DTB,
      ghi ket qua ra output.txt.
 Format file: Ho ten, MSSV, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

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

// ---- Them vao CUOI ----
void AddLast(DLIST &l, const SINHVIEN &sv) {
    DNODE *p = GetNode(sv);
    if (l.first == NULL) l.first = l.last = p;
    else { l.last->next = p; p->prev = l.last; l.last = p; }
}

// ---- Xoa phan tu DAU ----
void RemoveFirst(DLIST &l) {
    if (l.first == NULL) return;
    DNODE *p = l.first;
    l.first = p->next;
    if (l.first == NULL) l.last = NULL;
    else l.first->prev = NULL;
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

// ---- 1. Doc input.txt bang fscanf -> them vao CUOI danh sach ----
//   %[^,] doc den khi gap dau phay; dau cach dau format bo qua khoang trang.
//   Moi dong khop du 7 truong thi fscanf tra ve 7 -> tao 1 sinh vien.
void DocFile(const char *tenFile, DLIST &l) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return; }
    SINHVIEN s;
    while (fscanf(fi, " %20[^,], %10[^,], %f, %f, %f, %f, %f",
                  s.hoten, s.mssv,
                  &s.diem[0], &s.diem[1], &s.diem[2], &s.diem[3], &s.diem[4]) == 7)
        AddLast(l, s);
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

/* ============ MERGE SORT tren DSLK kep (tang theo DTB) ============ */
DNODE* Split(DNODE *head) {
    DNODE *slow = head, *fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    DNODE *mid = slow->next;
    slow->next = NULL;
    if (mid != NULL) mid->prev = NULL;
    return mid;
}

DNODE* MergeTwo(DNODE *a, DNODE *b) {
    if (a == NULL) return b;
    if (b == NULL) return a;
    if (DTB(a->info) <= DTB(b->info)) {
        a->next = MergeTwo(a->next, b);
        a->next->prev = a;
        a->prev = NULL;
        return a;
    } else {
        b->next = MergeTwo(a, b->next);
        b->next->prev = b;
        b->prev = NULL;
        return b;
    }
}

DNODE* MergeSort(DNODE *head) {
    if (head == NULL || head->next == NULL) return head;
    DNODE *mid = Split(head);
    DNODE *left  = MergeSort(head);
    DNODE *right = MergeSort(mid);
    return MergeTwo(left, right);
}

void MergeSortList(DLIST &l) {
    l.first = MergeSort(l.first);
    DNODE *p = l.first;
    while (p != NULL && p->next != NULL) p = p->next;
    l.last = p;
}

int main() {
    DLIST l; Init(l);
    DocFile("input.txt", l);
    if (l.first == NULL) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt (them vao cuoi):\n"); InDS(l);

    DNODE *q = Search(l, "2020000305");
    printf("\nTim MSSV 2020000305: %s\n", q ? q->info.hoten : "khong thay");

    RemoveFirst(l);
    printf("\nSau khi XOA phan tu dau:\n"); InDS(l);

    MergeSortList(l);
    printf("\nSau MERGE SORT (tang theo DTB):\n"); InDS(l);

    GhiFile("output.txt", l);
    printf("\nDa ghi ket qua vao output.txt\n");

    Destroy(l);
    return 0;
}
