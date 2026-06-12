/*
============================================================
 DE 9 (2026): DANH SACH LIEN KET KEP (du lieu: chuoi 10 ky tu)
   1. Cai dat DSLK kep, du lieu moi node la chuoi 10 ky tu.
   2. Doc input.txt va chen vao danh sach sao cho danh sach LUON
      SAP XEP TANG theo ASCII, dung 3 thao tac: chen DAU, chen CUOI,
      chen SAU q.
   3. Xoa ky tu (chuoi) can tim theo cach duyet TU CUOI ve DAU.
 Format input.txt: moi dong 1 chuoi (toi da 10 ky tu).
============================================================
*/
#include <cstdio>
#include <cstring>

struct DNODE {
    char data[11];          // chuoi 10 ky tu + '\0'
    DNODE *prev, *next;
};

struct DLIST {
    DNODE *first, *last;
};

void Init(DLIST &l) { l.first = l.last = NULL; }

DNODE* GetNode(const char *s) {
    DNODE *p = new DNODE;
    strncpy(p->data, s, 10); p->data[10] = '\0';
    p->prev = p->next = NULL;
    return p;
}

// chen DAU
void ChenDau(DLIST &l, DNODE *p) {
    if (l.first == NULL) l.first = l.last = p;
    else { p->next = l.first; l.first->prev = p; l.first = p; }
}

// chen CUOI
void ChenCuoi(DLIST &l, DNODE *p) {
    if (l.first == NULL) l.first = l.last = p;
    else { l.last->next = p; p->prev = l.last; l.last = p; }
}

// chen SAU node q
void ChenSau(DLIST &l, DNODE *p, DNODE *q) {
    p->next = q->next;
    p->prev = q;
    if (q->next != NULL) q->next->prev = p;
    q->next = p;
    if (q == l.last) l.last = p;
}

/* ---- 2. Chen 1 chuoi sao cho danh sach van SAP XEP tang theo ASCII ----
   - nho hon phan tu dau  -> chen DAU
   - lon hon phan tu cuoi -> chen CUOI
   - con lai              -> tim q (q <= s < q->next) roi chen SAU q */
void ChenCoThuTu(DLIST &l, const char *s) {
    DNODE *p = GetNode(s);
    if (l.first == NULL) { ChenDau(l, p); return; }
    if (strcmp(s, l.first->data) <= 0) { ChenDau(l, p); return; }
    if (strcmp(s, l.last->data)  >= 0) { ChenCuoi(l, p); return; }
    DNODE *q = l.first;
    while (q->next != NULL && strcmp(q->next->data, s) < 0) q = q->next;
    ChenSau(l, p, q);
}

void DocFile(const char *tenFile, DLIST &l) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return; }
    char s[64];
    while (fscanf(fi, "%10s", s) == 1) ChenCoThuTu(l, s);
    fclose(fi);
}

/* ---- 3. Xoa chuoi can tim, duyet TU CUOI ve DAU ---- */
void XoaTuCuoi(DLIST &l, const char *s) {
    DNODE *p = l.last;
    while (p != NULL && strcmp(p->data, s) != 0) p = p->prev;   // duyet nguoc
    if (p == NULL) { printf("Khong tim thay \"%s\"\n", s); return; }
    if (p->prev != NULL) p->prev->next = p->next; else l.first = p->next;
    if (p->next != NULL) p->next->prev = p->prev; else l.last = p->prev;
    delete p;
    printf("Da xoa \"%s\"\n", s);
}

void InXuoi(DLIST l) {
    printf("Xuoi : ");
    for (DNODE *p = l.first; p != NULL; p = p->next) printf("%s <-> ", p->data);
    printf("NULL\n");
}

void InNguoc(DLIST l) {
    printf("Nguoc: ");
    for (DNODE *p = l.last; p != NULL; p = p->prev) printf("%s <-> ", p->data);
    printf("NULL\n");
}

void Destroy(DLIST &l) {
    while (l.first != NULL) { DNODE *p = l.first; l.first = l.first->next; delete p; }
    l.last = NULL;
}

int main() {
    DLIST l; Init(l);
    DocFile("input.txt", l);
    if (l.first == NULL) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH SAU KHI CHEN CO THU TU (tang theo ASCII):\n");
    InXuoi(l);
    InNguoc(l);

    printf("\nXoa \"2320000101\" (duyet tu cuoi ve dau):\n");
    XoaTuCuoi(l, "2320000101");
    InXuoi(l);

    Destroy(l);
    return 0;
}
