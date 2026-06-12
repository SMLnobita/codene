/*
============================================================
 DE 10 (2026): STACK bang danh sach lien ket don (du lieu: ky tu)
   1. Cai dat Stack: Push(c), Pop(), Empty(), Top().
   2. Kiem tra mot chuoi co dong ngoac DUNG hay khong dung Stack.
      Chi xet 3 loai ngoac: () [] {}, bo qua cac ky tu khac.
   VD:
     "Toi la sinh vien (nam nhat) khoa Dien tu - Vien thong." -> DUNG
     "y = {[(x^2 + 2x) - z]dx}." -> DUNG
============================================================
*/
#include <cstdio>
#include <cstdlib>

struct NODE {
    char data;
    NODE *link;
};

struct STACK {
    NODE *top;          // dinh stack = dau danh sach
};

void Init(STACK &s) { s.top = NULL; }

bool Empty(STACK s) { return s.top == NULL; }

// Push: them vao dau
void Push(STACK &s, char c) {
    NODE *p = new NODE;
    p->data = c;
    p->link = s.top;
    s.top = p;
}

// Pop: lay tu dau
char Pop(STACK &s) {
    NODE *p = s.top;
    char c = p->data;
    s.top = p->link;
    delete p;
    return c;
}

// Top: xem dinh, khong xoa
char Top(STACK s) { return s.top->data; }

bool Khop(char mo, char dong) {
    return (mo == '(' && dong == ')') ||
           (mo == '[' && dong == ']') ||
           (mo == '{' && dong == '}');
}

// Kiem tra day ngoac dung
bool NgoacDung(const char *s) {
    STACK st; Init(st);
    bool ok = true;
    for (int i = 0; s[i] != '\0' && ok; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{')
            Push(st, c);                        // ngoac mo -> day vao stack
        else if (c == ')' || c == ']' || c == '}') {
            if (Empty(st)) ok = false;          // thua ngoac dong
            else if (!Khop(Pop(st), c)) ok = false;
        }
    }
    if (!Empty(st)) ok = false;                 // con ngoac mo chua dong
    while (!Empty(st)) Pop(st);                 // don dep
    return ok;
}

int main() {
    const char *test[] = {
        "Toi la sinh vien (nam nhat) khoa Dien tu - Vien thong.",
        "y = {[(x^2 + 2x) - z]dx}.",
        "([)]",
        "(((",
        "a[b]{c}"
    };
    int n = sizeof(test) / sizeof(test[0]);

    printf("KIEM TRA DONG NGOAC DUNG (dung Stack):\n");
    for (int i = 0; i < n; i++)
        printf("  %-55s -> %s\n", test[i], NgoacDung(test[i]) ? "DUNG" : "SAI");
    return 0;
}
