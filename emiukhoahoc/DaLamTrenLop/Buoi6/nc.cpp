#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct tagNode {
  int info;
  struct tagNode *pNext;
} NODE;

typedef struct {
  NODE *pHead;
  NODE *pTail;
} LIST;

// Khởi tạo stack rỗng
void InitStack(LIST &s) {
  s.pHead = nullptr;
  s.pTail = nullptr;
}

// Kiểm tra stack có rỗng không
bool Empty(const LIST &s) { return s.pHead == nullptr; }

// Tạo node mới
NODE *GetNode(int x) {
  NODE *p = new NODE;

  if (p == nullptr) {
    cout << "Khong du bo nho!\n";
    exit(1);
  }

  p->info = x;
  p->pNext = nullptr;

  return p;
}

// Thêm phần tử vào đỉnh stack
void Push(LIST &s, int x) {
  NODE *p = GetNode(x);

  if (Empty(s)) {
    s.pHead = s.pTail = p;
  } else {
    p->pNext = s.pHead;
    s.pHead = p;
  }
}

// Lấy phần tử ở đỉnh stack ra
bool Pop(LIST &s, int &x) {
  if (Empty(s)) {
    return false;
  }

  NODE *p = s.pHead;
  x = p->info;

  s.pHead = s.pHead->pNext;

  if (s.pHead == nullptr) {
    s.pTail = nullptr;
  }

  delete p;
  return true;
}

// Xem phần tử ở đỉnh stack, không xóa
bool Top(const LIST &s, int &x) {
  if (Empty(s)) {
    return false;
  }

  x = s.pHead->info;
  return true;
}

// In các phần tử trong stack
void PrintStack(const LIST &s) {
  if (Empty(s)) {
    cout << "Stack rong!\n";
    return;
  }

  cout << "Stack hien tai: ";

  for (NODE *p = s.pHead; p != nullptr; p = p->pNext) {
    cout << p->info << " ";
  }

  cout << endl;
}

// Xóa toàn bộ stack trước khi thoát
void ClearStack(LIST &s) {
  int x;

  while (Pop(s, x)) {
  }
}

int main() {
  LIST s;
  InitStack(s);

  int choice;
  int x;

  do {
    cout << "\nMENU STACK\n";
    cout << "1. Push\n";
    cout << "2. Pop\n";
    cout << "3. Top\n";
    cout << "4. Empty\n";
    cout << "5. Xuat stack\n";
    cout << "0. Thoat\n";
    cout << "Nhap lua chon: ";
    cin >> choice;

    switch (choice) {
    case 1:
      system("cls");
      cout << "Nhap gia tri can them: ";
      cin >> x;
      Push(s, x);
      cout << "Da them " << x << " vao stack.\n";
      break;

    case 2:
      system("cls");
      if (Pop(s, x)) {
        cout << "Phan tu vua lay ra: " << x << endl;
      } else {
        cout << "Stack rong, khong the Pop!\n";
      }
      break;

    case 3:
      system("cls");
      if (Top(s, x)) {
        cout << "Phan tu tren dinh stack: " << x << endl;
      } else {
        cout << "Stack rong, khong co Top!\n";
      }
      break;

    case 4:
      system("cls");
      if (Empty(s)) {
        cout << "Stack dang rong.\n";
      } else {
        cout << "Stack khong rong.\n";
      }
      break;

    case 5:
      system("cls");
      PrintStack(s);
      break;

    case 0:
      system("cls");
      ClearStack(s);
      cout << "Da thoat chuong trinh.\n";
      break;

    default:
      system("cls");
      cout << "Lua chon khong hop le!\n";
      break;
    }

  } while (choice != 0);

  return 0;
}