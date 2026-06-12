/*
============================================================
 DE 9 (C):
   1. Cai dat STACK dung danh sach lien ket, du lieu la ki tu.
   2. Kiem tra mot chuoi co phai la day NGOAC DUNG hay khong
      (parentheses (), brackets [], braces {}) bang stack.
============================================================
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    char data;
    struct NODE *link;
} NODE;

typedef struct {
    NODE *top;          /* dinh stack = dau danh sach */
} STACK;

void Init(STACK *s) { s->top = NULL; }

int Empty(STACK *s) { return s->top == NULL; }

/* ---- Push: them vao dau ---- */
void Push(STACK *s, char x) {
    NODE *p = (NODE*)malloc(sizeof(NODE));
    p->data = x;
    p->link = s->top;
    s->top = p;
}

/* ---- Pop: lay tu dau ---- */
char Pop(STACK *s) {
    NODE *p = s->top;
    char x = p->data;
    s->top = p->link;
    free(p);
    return x;
}

char Top(STACK *s) { return s->top->data; }

int Khop(char mo, char dong) {
    return (mo == '(' && dong == ')') ||
           (mo == '[' && dong == ']') ||
           (mo == '{' && dong == '}');
}

/* ---- Kiem tra day ngoac dung ---- */
int NgoacDung(const char *s) {
    STACK st; Init(&st);
    int ok = 1;
    for (int i = 0; s[i] != '\0' && ok; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{')
            Push(&st, c);                       /* ngoac mo -> day vao stack */
        else if (c == ')' || c == ']' || c == '}') {
            if (Empty(&st)) ok = 0;             /* thua ngoac dong */
            else if (!Khop(Pop(&st), c)) ok = 0;
        }
    }
    if (!Empty(&st)) ok = 0;                    /* con ngoac mo chua dong */
    while (!Empty(&st)) Pop(&st);               /* don dep bo nho */
    return ok;
}

int main(void) {
    const char *test[] = {
        "{[()]}", "([)]", "(((", "a(b)[c]{d}", "}", "{[a+b]*(c-d)}"
    };
    int n = sizeof(test) / sizeof(test[0]);

    printf("KIEM TRA DAY NGOAC DUNG (dung stack):\n");
    for (int i = 0; i < n; i++)
        printf("  \"%s\" -> %s\n", test[i], NgoacDung(test[i]) ? "DUNG" : "SAI");
    return 0;
}
