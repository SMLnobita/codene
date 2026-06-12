/*
============================================================
 DE 8 (2026): DANH SACH LIEN KET DON (du lieu so nguyen)
   1. Cai dat DSLK don voi du lieu la so nguyen.
   2. Doc input.txt -> them vao CUOI danh sach (AddTail).
   3. QUICK SORT tren phan lien ket de xep danh sach TANG.
   4. Tim so nguyen X, chen 1 node moi (gia tri cho truoc) NGAY SAU node tim duoc.
 Format input.txt: cac so nguyen cach nhau khoang trang / xuong dong.
============================================================
*/
#include <cstdio>
#include <cstdlib>

struct NODE {
    int data;
    NODE *next;
};

struct LIST {
    NODE *head, *tail;
};

void Init(LIST &l) { l.head = l.tail = NULL; }

NODE* GetNode(int x) {
    NODE *p = new NODE;
    p->data = x;
    p->next = NULL;
    return p;
}

// ---- 2. Them vao CUOI ----
void AddTail(LIST &l, int x) {
    NODE *p = GetNode(x);
    if (l.head == NULL) l.head = l.tail = p;
    else { l.tail->next = p; l.tail = p; }
}

int DocFile(const char *tenFile, LIST &l) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return 0; }
    int x, dem = 0;
    while (fscanf(fi, "%d", &x) == 1) { AddTail(l, x); dem++; }
    fclose(fi);
    return dem;
}

void InList(LIST l) {
    for (NODE *p = l.head; p != NULL; p = p->next) printf("%d -> ", p->data);
    printf("NULL\n");
}

void Destroy(LIST &l) {
    while (l.head != NULL) { NODE *p = l.head; l.head = l.head->next; delete p; }
    l.tail = NULL;
}

/* ============ 3. QUICK SORT tren DSLK don (chuan, doi lien ket) ============
   Phan hoach quanh pivot = node cuoi: node nho hon giu nguyen,
   node lon hon dua ve sau pivot. De quy 2 phan. */
NODE* getTail(NODE *cur) {
    while (cur != NULL && cur->next != NULL) cur = cur->next;
    return cur;
}

NODE* partition(NODE *head, NODE *end, NODE **newHead, NODE **newEnd) {
    NODE *pivot = end;
    NODE *prev = NULL, *cur = head, *tail = pivot;
    while (cur != pivot) {
        if (cur->data < pivot->data) {        // nho hon pivot -> giu ben trai
            if (*newHead == NULL) *newHead = cur;
            prev = cur;
            cur = cur->next;
        } else {                              // lon hon -> day ve sau pivot
            if (prev) prev->next = cur->next;
            NODE *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if (*newHead == NULL) *newHead = pivot;
    *newEnd = tail;
    return pivot;
}

NODE* quickSortRecur(NODE *head, NODE *end) {
    if (head == NULL || head == end) return head;
    NODE *newHead = NULL, *newEnd = NULL;
    NODE *pivot = partition(head, end, &newHead, &newEnd);
    if (newHead != pivot) {
        NODE *tmp = newHead;
        while (tmp->next != pivot) tmp = tmp->next;
        tmp->next = NULL;
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->next = pivot;                    // noi lai pivot
    }
    pivot->next = quickSortRecur(pivot->next, newEnd);
    return newHead;     // dau doan da sap la newHead (KHONG phai pivot)
}

void QuickSort(LIST &l) {
    l.head = quickSortRecur(l.head, getTail(l.head));
    l.tail = getTail(l.head);
}

/* ============ 4. Tim X, chen node moi (val) ngay sau node tim duoc ============ */
void TimVaChenSau(LIST &l, int X, int val) {
    NODE *p = l.head;
    while (p != NULL && p->data != X) p = p->next;
    if (p == NULL) { printf("Khong tim thay %d trong danh sach!\n", X); return; }
    NODE *q = GetNode(val);
    q->next = p->next;
    p->next = q;
    if (p == l.tail) l.tail = q;
    printf("Da chen %d ngay sau %d.\n", val, X);
}

int main() {
    LIST l; Init(l);
    int n = DocFile("input.txt", l);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("Danh sach doc tu input.txt: "); InList(l);

    QuickSort(l);
    printf("Sau QUICK SORT (tang dan): "); InList(l);

    TimVaChenSau(l, 27, 100);    // tim 27, chen 100 ngay sau
    printf("Sau khi chen           : "); InList(l);

    Destroy(l);
    return 0;
}
