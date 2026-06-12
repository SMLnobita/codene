/*
============================================================
 DE 10:
   1. Cai dat QUEUE dung danh sach lien ket, du lieu la ki tu.
   2. Su dung queue (va stack) bang danh sach lien ket de kiem tra
      mot chuoi co phai la PALINDROME hay khong.
      Palindrome: doc tu trai sang phai = doc tu phai sang trai.
      Vi du: "radar", "level", "madam".
============================================================
*/
#include <cstdio>
#include <cstring>
#include <cctype>

struct NODE {
    char data;
    NODE *link;
};

/* ===================== QUEUE (FIFO) ===================== */
struct QUEUE {
    NODE *front, *rear;
};

void InitQ(QUEUE &q) { q.front = q.rear = NULL; }
bool EmptyQ(QUEUE q) { return q.front == NULL; }

void EnQueue(QUEUE &q, char x) {        // them vao cuoi
    NODE *p = new NODE;
    p->data = x; p->link = NULL;
    if (EmptyQ(q)) q.front = q.rear = p;
    else { q.rear->link = p; q.rear = p; }
}

char DeQueue(QUEUE &q) {                 // lay tu dau
    NODE *p = q.front;
    char x = p->data;
    q.front = p->link;
    if (q.front == NULL) q.rear = NULL;
    delete p;
    return x;
}

/* ===================== STACK (LIFO) ===================== */
struct STACK {
    NODE *top;
};

void InitS(STACK &s) { s.top = NULL; }
bool EmptyS(STACK s) { return s.top == NULL; }

void Push(STACK &s, char x) {
    NODE *p = new NODE;
    p->data = x; p->link = s.top;
    s.top = p;
}

char Pop(STACK &s) {
    NODE *p = s.top;
    char x = p->data;
    s.top = p->link;
    delete p;
    return x;
}

/* ===== Kiem tra palindrome =====
   Day moi ki tu vao CA queue (FIFO) va stack (LIFO).
   Queue tra ra theo thu tu goc, stack tra ra theo thu tu nguoc.
   Neu moi cap deu bang nhau -> palindrome. */
bool LaPalindrome(const char *s) {
    QUEUE q; InitQ(q);
    STACK st; InitS(st);
    for (int i = 0; s[i] != '\0'; i++) {
        char c = (char)tolower((unsigned char)s[i]);
        EnQueue(q, c);
        Push(st, c);
    }
    bool ok = true;
    while (!EmptyQ(q) && ok)
        if (DeQueue(q) != Pop(st)) ok = false;
    while (!EmptyQ(q)) DeQueue(q);       // don dep neu thoat som
    while (!EmptyS(st)) Pop(st);
    return ok;
}

int main() {
    const char *test[] = { "radar", "level", "madam", "hello", "abccba", "abc" };
    int n = sizeof(test) / sizeof(test[0]);

    printf("KIEM TRA PALINDROME (dung queue + stack):\n");
    for (int i = 0; i < n; i++)
        printf("  \"%s\" -> %s\n", test[i],
               LaPalindrome(test[i]) ? "LA palindrome" : "KHONG");
    return 0;
}
