/*
============================================================
 ON TAP 4c: STACK va QUEUE (cai dat bang danh sach lien ket)
============================================================
 STACK (ngan xep) - LIFO (Last In First Out):
   Push(x) : them vao DAU danh sach
   Pop()   : lay ra tu DAU danh sach
   Top()   : xem phan tu dau, khong xoa
   Empty() : kiem tra rong
   Ung dung: khu de quy, kiem tra ngoac, duyet DFS, undo...

 QUEUE (hang doi) - FIFO (First In First Out):
   EnQueue(x): them vao CUOI danh sach
   DeQueue() : lay ra tu DAU danh sach
   Front()   : xem phan tu dau, khong xoa
   Empty()   : kiem tra rong
   Ung dung: hang doi xu ly, duyet BFS, buffer...
============================================================
*/
#include <cstdio>
#include <cstdlib>

struct NODE {
    int data;
    NODE *link;
};

/* ======================= STACK ======================= */
struct STACK {
    NODE *top;     // dinh stack = dau danh sach
};

void InitS(STACK &s) { s.top = NULL; }

bool EmptyS(STACK s) { return s.top == NULL; }

void Push(STACK &s, int x) {       // them vao dau
    NODE *p = new NODE;
    p->data = x;
    p->link = s.top;
    s.top = p;
}

int Pop(STACK &s) {                // lay tu dau
    if (EmptyS(s)) { printf("Stack rong!\n"); exit(1); }
    NODE *p = s.top;
    int x = p->data;
    s.top = p->link;
    delete p;
    return x;
}

int Top(STACK s) {                 // xem, khong xoa
    if (EmptyS(s)) { printf("Stack rong!\n"); exit(1); }
    return s.top->data;
}

/* ======================= QUEUE ======================= */
struct QUEUE {
    NODE *front;   // dau hang (lay ra)
    NODE *rear;    // cuoi hang (them vao)
};

void InitQ(QUEUE &q) { q.front = q.rear = NULL; }

bool EmptyQ(QUEUE q) { return q.front == NULL; }

void EnQueue(QUEUE &q, int x) {    // them vao cuoi
    NODE *p = new NODE;
    p->data = x;
    p->link = NULL;
    if (EmptyQ(q)) q.front = q.rear = p;
    else {
        q.rear->link = p;
        q.rear = p;
    }
}

int DeQueue(QUEUE &q) {            // lay tu dau
    if (EmptyQ(q)) { printf("Queue rong!\n"); exit(1); }
    NODE *p = q.front;
    int x = p->data;
    q.front = p->link;
    if (q.front == NULL) q.rear = NULL;
    delete p;
    return x;
}

int Front(QUEUE q) {
    if (EmptyQ(q)) { printf("Queue rong!\n"); exit(1); }
    return q.front->data;
}

/* ============ Ung dung: kiem tra day ngoac dung ============ */
bool NgoacDung(const char *s) {
    STACK st; InitS(st);
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') Push(st, c);
        else if (c == ')' || c == ']' || c == '}') {
            if (EmptyS(st)) return false;
            char mo = (char)Pop(st);
            if ((c == ')' && mo != '(') ||
                (c == ']' && mo != '[') ||
                (c == '}' && mo != '{')) return false;
        }
    }
    bool ok = EmptyS(st);
    while (!EmptyS(st)) Pop(st);   // don dep
    return ok;
}

int main() {
    // ---- Stack: vao 1 2 3 -> ra 3 2 1 ----
    printf("== STACK (LIFO) ==\n");
    STACK s; InitS(s);
    Push(s, 1); Push(s, 2); Push(s, 3);
    printf("Top = %d\n", Top(s));
    printf("Pop ra: ");
    while (!EmptyS(s)) printf("%d ", Pop(s));   // 3 2 1
    printf("\n");

    // ---- Queue: vao 1 2 3 -> ra 1 2 3 ----
    printf("\n== QUEUE (FIFO) ==\n");
    QUEUE q; InitQ(q);
    EnQueue(q, 1); EnQueue(q, 2); EnQueue(q, 3);
    printf("Front = %d\n", Front(q));
    printf("DeQueue ra: ");
    while (!EmptyQ(q)) printf("%d ", DeQueue(q)); // 1 2 3
    printf("\n");

    // ---- Ung dung stack ----
    printf("\n== KIEM TRA NGOAC ==\n");
    printf("\"{[()]}\" -> %s\n", NgoacDung("{[()]}") ? "DUNG" : "SAI");
    printf("\"([)]\"   -> %s\n", NgoacDung("([)]")   ? "DUNG" : "SAI");
    return 0;
}
