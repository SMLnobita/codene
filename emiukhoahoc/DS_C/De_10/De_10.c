/*
============================================================
 DE 10 (C):
   1. Cai dat QUEUE dung danh sach lien ket, du lieu la ki tu.
   2. Su dung queue (va stack) de kiem tra mot chuoi co phai
      la PALINDROME hay khong. Vi du: "radar", "level", "madam".
============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct NODE {
    char data;
    struct NODE *link;
} NODE;

/* ===================== QUEUE (FIFO) ===================== */
typedef struct {
    NODE *front, *rear;
} QUEUE;

void InitQ(QUEUE *q) { q->front = q->rear = NULL; }
int EmptyQ(QUEUE *q) { return q->front == NULL; }

void EnQueue(QUEUE *q, char x) {        /* them vao cuoi */
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p->data = x; p->link = NULL;
    if (EmptyQ(q)) q->front = q->rear = p;
    else { q->rear->link = p; q->rear = p; }
}

char DeQueue(QUEUE *q) {                 /* lay tu dau */
    NODE *p = q->front;
    char x = p->data;
    q->front = p->link;
    if (q->front == NULL) q->rear = NULL;
    free(p);
    return x;
}

/* ===================== STACK (LIFO) ===================== */
typedef struct {
    NODE *top;
} STACK;

void InitS(STACK *s) { s->top = NULL; }
int EmptyS(STACK *s) { return s->top == NULL; }

void Push(STACK *s, char x) {
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p->data = x; p->link = s->top;
    s->top = p;
}

char Pop(STACK *s) {
    NODE *p = s->top;
    char x = p->data;
    s->top = p->link;
    free(p);
    return x;
}

/* ===== Kiem tra palindrome =====
   Day moi ki tu vao CA queue (FIFO) va stack (LIFO).
   Queue tra ra theo thu tu goc, stack tra ra nguoc lai.
   Moi cap bang nhau -> palindrome. */
int LaPalindrome(const char *s) {
    QUEUE q; InitQ(&q);
    STACK st; InitS(&st);
    for (int i = 0; s[i] != '\0'; i++) {
        char c = (char)tolower((unsigned char)s[i]);
        EnQueue(&q, c);
        Push(&st, c);
    }
    int ok = 1;
    while (!EmptyQ(&q) && ok)
        if (DeQueue(&q) != Pop(&st)) ok = 0;
    while (!EmptyQ(&q)) DeQueue(&q);     /* don dep neu thoat som */
    while (!EmptyS(&st)) Pop(&st);
    return ok;
}

int main(void) {
    const char *test[] = { "radar", "level", "madam", "hello", "abccba", "abc" };
    int n = sizeof(test) / sizeof(test[0]);

    printf("KIEM TRA PALINDROME (dung queue + stack):\n");
    for (int i = 0; i < n; i++)
        printf("  \"%s\" -> %s\n", test[i],
               LaPalindrome(test[i]) ? "LA palindrome" : "KHONG");
    return 0;
}
