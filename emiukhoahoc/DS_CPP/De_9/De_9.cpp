/*
============================================================
 DE 9:
   1. Cai dat STACK dung danh sach lien ket, du lieu la ki tu.
   2. Kiem tra mot chuoi dau vao co phai la day NGOAC DUNG
      (parentheses (), brackets [], braces {}) hay khong
      bang cach su dung stack.
============================================================
*/
#include <cstdio>
#include <cstring>

struct NODE {
    char data;          // du lieu la ki tu
    NODE *link;
};

struct STACK {
    NODE *top;          // dinh stack = dau danh sach
};

void Init(STACK &s) { s.top = NULL; }

bool Empty(STACK s) { return s.top == NULL; }

// ---- Push: them vao dau ----
void Push(STACK &s, char x) {
    NODE *p = new NODE;
    p->data = x;
    p->link = s.top;
    s.top = p;
}

// ---- Pop: lay tu dau ----
char Pop(STACK &s) {
    NODE *p = s.top;
    char x = p->data;
    s.top = p->link;
    delete p;
    return x;
}

char Top(STACK s) { return s.top->data; }

// ---- Kiem tra ngoac dong 'dong' co khop ngoac mo 'mo' khong ----
bool Khop(char mo, char dong) {
    return (mo == '(' && dong == ')') ||
           (mo == '[' && dong == ']') ||
           (mo == '{' && dong == '}');
}

// ---- Kiem tra day ngoac dung ----
bool NgoacDung(const char *s) {
    STACK st; Init(st);
    bool ok = true;
    for (int i = 0; s[i] != '\0' && ok; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{')
            Push(st, c);                        // ngoac mo -> day vao stack
        else if (c == ')' || c == ']' || c == '}') {
            if (Empty(st)) ok = false;          // thua ngoac dong
            else if (!Khop(Pop(st), c)) ok = false;  // sai loai ngoac
        }
    }
    if (!Empty(st)) ok = false;                 // con ngoac mo chua dong
    while (!Empty(st)) Pop(st);                 // don dep bo nho
    return ok;
}

int main() {
    const char *test[] = {
        "{[()]}", "([)]", "(((", "a(b)[c]{d}", "}", "{[a+b]*(c-d)}"
    };
    int n = sizeof(test) / sizeof(test[0]);

    printf("KIEM TRA DAY NGOAC DUNG (dung stack):\n");
    for (int i = 0; i < n; i++)
        printf("  \"%s\" -> %s\n", test[i], NgoacDung(test[i]) ? "DUNG" : "SAI");
    return 0;
}
