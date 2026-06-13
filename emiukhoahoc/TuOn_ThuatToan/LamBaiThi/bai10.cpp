#include <cstdio>
#include <iostream>

struct NODE {
  char data;
  NODE *link;
};

struct STACK {
  NODE *top;
};

void Init(STACK &s) { s.top = NULL; }

bool Emty(STACK s) { return s.top == NULL; }

void Push(STACK &s, char x) {
  NODE *p = new NODE;
  p->data = x;
  p->link = s.top;
  s.top = p;
}

char Pop(STACK &s) {
  NODE *p = s.top;
  char c = p->data;
  s.top = p->link;
  delete p;
  return c;
}

char Top(STACK &s) { return s.top->data; }

bool Khop(char mo, char dong) {
  return (mo == '(' && dong == ')') || (mo == '[' && dong == ']') ||
         (mo == '{' && dong == '}');
}

bool NgoacDung(const char *s) {
  STACK st;
  Init(st);
  bool ok = true;
  for (int i = 0; s[i] != '\0' && ok; i++) {
    char c = s[i];
    if (c == '(' || c == '[' || c == '{')
      Push(st, c);
    else if (c == ')' || c == ']' || c == '}') {
      if (Emty(st))
        ok = false;
      else if (!Khop(Pop(st), c))
        ok = false;
    }
  }
  if (!Emty(st))
    ok = false;
  while (!Emty(st))
    Pop(st);
  return ok;
}

int main() {
  const char *test = "Toi la sinh vien (nam nhat) khoa Dien tu - Vien thong.";
  printf("%-55s -> %s\n", test, NgoacDung(test) ? "DUNG" : "SAI");
}