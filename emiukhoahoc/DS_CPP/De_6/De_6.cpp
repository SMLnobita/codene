/*
============================================================
 DE 6: DANH SACH LIEN KET KEP cho day SINH VIEN
   - Ho ten: toi da 20 ki tu | MSSV: 10 ki tu so | 5 diem so thuc
 Yeu cau:
   1. DSLK kep: them vao CUOI, xoa phan tu DAU, tim theo MSSV.
   2. MERGE SORT tren cac lien ket cua danh sach de xep
      TANG theo diem trung binh cua 5 mon hoc.
============================================================
*/
#include <cstdio>
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
    else {
        l.last->next = p;
        p->prev = l.last;
        l.last = p;
    }
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

// ---- Tim theo MSSV ----
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

/* ============ MERGE SORT tren DSLK kep (tang theo DTB) ============
   Tach doi danh sach (slow/fast), de quy sap moi nua roi tron lai.
   Lam viec truc tiep tren cac lien ket (noi lai prev/next). */
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
    DNODE *p = l.first;                 // cap nhat lai con tro last
    while (p != NULL && p->next != NULL) p = p->next;
    l.last = p;
}

int main() {
    DLIST l; Init(l);

    SINHVIEN mau[] = {
        {"Nguyen Van A", "2020000001", {7, 8, 6, 9, 5}},
        {"Tran Thi B",   "2020000002", {9, 9, 8, 10, 9}},
        {"Le Van C",     "2020000003", {5, 6, 4, 7, 5}},
        {"Pham Thi D",   "2020000004", {8, 7, 9, 6, 8}},
    };
    for (int i = 0; i < 4; i++) AddLast(l, mau[i]);    // them vao cuoi

    printf("DANH SACH (them vao cuoi):\n"); InDS(l);

    DNODE *q = Search(l, "2020000003");
    printf("\nTim MSSV 2020000003: %s\n", q ? q->info.hoten : "khong thay");

    RemoveFirst(l);
    printf("\nSau khi XOA phan tu dau:\n"); InDS(l);

    MergeSortList(l);
    printf("\nSau MERGE SORT (tang theo DTB):\n"); InDS(l);

    Destroy(l);
    return 0;
}
