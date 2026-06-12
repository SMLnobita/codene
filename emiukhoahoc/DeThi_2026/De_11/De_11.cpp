/*
============================================================
 DE 11 (2026): QUEUE bang danh sach lien ket don (du lieu: ky tu)
   1. Cai dat Queue: EnQueue(c), DeQueue(), Empty(), Front().
   2. Kiem tra mot chuoi co phai PALINDROME hay khong dung Queue.
      Y tuong: dua ky tu vao Queue (thu tu goc) va Stack (thu tu nguoc),
      lay ra dong thoi va so sanh tung cap.
   VD palindrome: level, radar, deified, racecar, hannah, civic...
============================================================
*/
#include <cstdio>
#include <cstdlib>
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

void EnQueue(QUEUE &q, char c) {        // them vao cuoi
    NODE *p = new NODE;
    p->data = c; p->link = NULL;
    if (EmptyQ(q)) q.front = q.rear = p;
    else { q.rear->link = p; q.rear = p; }
}

char DeQueue(QUEUE &q) {                 // lay tu dau
    NODE *p = q.front;
    char c = p->data;
    q.front = p->link;
    if (q.front == NULL) q.rear = NULL;
    delete p;
    return c;
}

char Front(QUEUE q) { return q.front->data; }

/* ===================== STACK (LIFO) ho tro ===================== */
struct STACK { NODE *top; };
void InitS(STACK &s) { s.top = NULL; }
bool EmptyS(STACK s) { return s.top == NULL; }
void Push(STACK &s, char c) { NODE *p = new NODE; p->data = c; p->link = s.top; s.top = p; }
char Pop(STACK &s) { NODE *p = s.top; char c = p->data; s.top = p->link; delete p; return c; }

// Kiem tra palindrome
bool LaPalindrome(const char *s) {
    QUEUE q; InitQ(q);
    STACK st; InitS(st);
    for (int i = 0; s[i] != '\0'; i++) {
        char c = (char)tolower((unsigned char)s[i]);
        EnQueue(q, c);     // thu tu goc
        Push(st, c);       // thu tu nguoc
    }
    bool ok = true;
    while (!EmptyQ(q) && ok)
        if (DeQueue(q) != Pop(st)) ok = false;   // so sanh tung cap
    while (!EmptyQ(q)) DeQueue(q);
    while (!EmptyS(st)) Pop(st);
    return ok;
}

int main() {
    const char *test[] = {
        "level", "radar", "deified", "racecar", "hannah",
        "rotator", "civic", "noon", "kayak", "reviver", "hello"
    };
    int n = sizeof(test) / sizeof(test[0]);

    printf("KIEM TRA PALINDROME (dung Queue):\n");
    for (int i = 0; i < n; i++)
        printf("  %-10s -> %s\n", test[i],
               LaPalindrome(test[i]) ? "LA palindrome" : "KHONG");
    return 0;
}
