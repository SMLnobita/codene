/*
============================================================
 ON TAP 4b: DANH SACH LIEN KET DOI (kep) va LIEN KET VONG
============================================================
 1. DSLK DOI: moi node co 2 con tro prev / next
    -> duyet duoc 2 chieu, xoa 1 node khong can node truoc.
 2. DSLK VONG: node cuoi tro nguoc ve node dau
    (last->link = first). Duyet phai dung dieu kien dung
    "quay lai dau" thay vi NULL.
============================================================
*/
#include <cstdio>
#include <cstdlib>

/* ====================== DSLK DOI ====================== */
struct DNODE {
    int data;
    DNODE *prev, *next;
};

struct DLIST {
    DNODE *first, *last;
};

void DInit(DLIST &l) { l.first = l.last = NULL; }

DNODE* DGetNode(int x) {
    DNODE *p = new DNODE;
    p->data = x;
    p->prev = p->next = NULL;
    return p;
}

void DAddFirst(DLIST &l, DNODE *p) {
    if (l.first == NULL) l.first = l.last = p;
    else {
        p->next = l.first;
        l.first->prev = p;
        l.first = p;
    }
}

void DAddLast(DLIST &l, DNODE *p) {
    if (l.first == NULL) l.first = l.last = p;
    else {
        l.last->next = p;
        p->prev = l.last;
        l.last = p;
    }
}

// Them p vao SAU node q
void DAddAfter(DLIST &l, DNODE *p, DNODE *q) {
    if (q == NULL) { DAddFirst(l, p); return; }
    p->next = q->next;
    p->prev = q;
    if (q->next != NULL) q->next->prev = p;
    q->next = p;
    if (q == l.last) l.last = p;
}

DNODE* DSearch(DLIST l, int x) {
    DNODE *p = l.first;
    while (p != NULL && p->data != x) p = p->next;
    return p;
}

// Xoa node p bat ky - uu diem cua DSLK doi: O(1), khong can tim node truoc
void DRemove(DLIST &l, DNODE *p) {
    if (p == NULL) return;
    if (p->prev != NULL) p->prev->next = p->next;
    else l.first = p->next;            // p la node dau
    if (p->next != NULL) p->next->prev = p->prev;
    else l.last = p->prev;             // p la node cuoi
    delete p;
}

void DRemoveFirst(DLIST &l) { DRemove(l, l.first); }
void DRemoveLast (DLIST &l) { DRemove(l, l.last);  }

void DPrint(DLIST l) {
    for (DNODE *p = l.first; p != NULL; p = p->next)
        printf("%d <-> ", p->data);
    printf("NULL\n");
}

void DPrintNguoc(DLIST l) {            // duyet nguoc nho prev
    for (DNODE *p = l.last; p != NULL; p = p->prev)
        printf("%d <-> ", p->data);
    printf("NULL\n");
}

void DDestroy(DLIST &l) {
    while (l.first != NULL) DRemoveFirst(l);
}

/* ====================== DSLK VONG ====================== */
struct CNODE {
    int data;
    CNODE *link;
};

// danh sach vong chi can giu 1 con tro last (last->link = first)
struct CLIST {
    CNODE *last;
};

void CInit(CLIST &l) { l.last = NULL; }

void CAddLast(CLIST &l, int x) {
    CNODE *p = new CNODE;
    p->data = x;
    if (l.last == NULL) {           // rong: tu tro vao chinh no
        p->link = p;
        l.last = p;
    } else {
        p->link = l.last->link;     // p->link = first
        l.last->link = p;
        l.last = p;
    }
}

void CPrint(CLIST l) {
    if (l.last == NULL) { printf("(rong)\n"); return; }
    CNODE *first = l.last->link;
    CNODE *p = first;
    do {                            // dieu kien dung: quay ve first
        printf("%d -> ", p->data);
        p = p->link;
    } while (p != first);
    printf("(quay ve dau)\n");
}

void CDestroy(CLIST &l) {
    if (l.last == NULL) return;
    CNODE *first = l.last->link;
    l.last->link = NULL;            // cat vong roi huy nhu DSLK don
    while (first != NULL) {
        CNODE *p = first;
        first = first->link;
        delete p;
    }
    l.last = NULL;
}

int main() {
    // ---- DSLK doi ----
    printf("== DSLK DOI ==\n");
    DLIST dl; DInit(dl);
    DAddLast(dl, DGetNode(1));
    DAddLast(dl, DGetNode(2));
    DAddLast(dl, DGetNode(3));
    DAddFirst(dl, DGetNode(0));
    printf("Danh sach        : "); DPrint(dl);        // 0 1 2 3
    printf("Duyet nguoc      : "); DPrintNguoc(dl);   // 3 2 1 0
    DAddAfter(dl, DGetNode(99), DSearch(dl, 2));
    printf("Them 99 sau 2    : "); DPrint(dl);
    DRemove(dl, DSearch(dl, 1));
    printf("Xoa node 1       : "); DPrint(dl);
    DRemoveFirst(dl); DRemoveLast(dl);
    printf("Xoa dau + cuoi   : "); DPrint(dl);
    DDestroy(dl);

    // ---- DSLK vong ----
    printf("\n== DSLK VONG ==\n");
    CLIST cl; CInit(cl);
    for (int i = 1; i <= 5; i++) CAddLast(cl, i * 10);
    CPrint(cl);    // 10 20 30 40 50 quay ve dau
    CDestroy(cl);
    return 0;
}
