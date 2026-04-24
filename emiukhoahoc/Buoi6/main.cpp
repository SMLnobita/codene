#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct birth {
  unsigned char day;
  unsigned char month;
  unsigned int year;
};

typedef struct {
  char name[50];
  struct birth Birthday;
  char studentID[9];
  float GPA;
} Student;

typedef struct tagNode {
  Student info;
  struct tagNode *pNext;
} NODE;

typedef struct {
  NODE *pHead;
  NODE *pTail;
} LIST;

// ===================== KHOI TAO =====================

void InitList(LIST &l) {
  l.pHead = nullptr;
  l.pTail = nullptr;
}

// ===================== SO SANH =====================
// Tang dan theo GPA.
// Neu GPA bang nhau thi sap xep theo MSSV.
int CompareByGPA(const Student &a, const Student &b) {
  if (a.GPA < b.GPA)
    return -1;
  if (a.GPA > b.GPA)
    return 1;
  return strcmp(a.studentID, b.studentID);
}

// Tang dan theo tuoi.
// Tuoi nho (tre nhat, nam sinh lon) -> len truoc.
// Tuoi lon (gia nhat, nam sinh nho) -> xuong sau.
int CompareByAge(const Student &a, const Student &b) {
  if (a.Birthday.year > b.Birthday.year)
    return -1;
  if (a.Birthday.year < b.Birthday.year)
    return 1;

  if (a.Birthday.month > b.Birthday.month)
    return -1;
  if (a.Birthday.month < b.Birthday.month)
    return 1;

  if (a.Birthday.day > b.Birthday.day)
    return -1;
  if (a.Birthday.day < b.Birthday.day)
    return 1;

  return strcmp(a.studentID, b.studentID);
}

void SwapStudent(Student &a, Student &b) {
  Student temp = a;
  a = b;
  b = temp;
}

// ===================== TAO NODE =====================

NODE *GetNode(const Student &x) {
  NODE *p = new NODE;
  if (p == nullptr) {
    cout << "Khong du bo nho de cap phat node!\n";
    exit(1);
  }
  p->info = x;
  p->pNext = nullptr;
  return p;
}

// ===================== THEM NODE =====================

void AddLast(LIST &l, NODE *p) {
  if (p == nullptr)
    return;

  if (l.pHead == nullptr) {
    l.pHead = l.pTail = p;
  } else {
    l.pTail->pNext = p;
    l.pTail = p;
  }
}

// Them node co san vao cuoi list, khong cap phat node moi
void AppendNode(LIST &l, NODE *p) {
  if (p == nullptr)
    return;

  p->pNext = nullptr;

  if (l.pHead == nullptr) {
    l.pHead = l.pTail = p;
  } else {
    l.pTail->pNext = p;
    l.pTail = p;
  }
}

// Tach 1 node ra khoi list. prev = node dung ngay truoc p.
// Neu p la pHead thi prev = nullptr.
void DetachNode(LIST &l, NODE *prev, NODE *p) {
  if (p == nullptr)
    return;

  if (prev == nullptr) {
    l.pHead = p->pNext;
    if (l.pHead == nullptr)
      l.pTail = nullptr;
  } else {
    prev->pNext = p->pNext;
    if (p == l.pTail)
      l.pTail = prev;
  }

  p->pNext = nullptr;
}

// Noi list b vao cuoi list a
void ConcatList(LIST &a, LIST &b) {
  if (b.pHead == nullptr)
    return;

  if (a.pHead == nullptr) {
    a.pHead = b.pHead;
    a.pTail = b.pTail;
  } else {
    a.pTail->pNext = b.pHead;
    a.pTail = b.pTail;
  }

  b.pHead = nullptr;
  b.pTail = nullptr;
}

// ===================== IN DANH SACH =====================

void PrintStudent(const Student &s) {
  cout << left << setw(12) << s.studentID << setw(26) << s.name << setw(8)
       << fixed << setprecision(1) << s.GPA;

  cout << right << setfill('0') << setw(2) << (int)s.Birthday.day << "/"
       << setw(2) << (int)s.Birthday.month << "/" << s.Birthday.year
       << setfill(' ') << left << '\n';
}

void PrintList(const LIST &l) {
  cout << left << setw(12) << "MSSV" << setw(26) << "Ho ten" << setw(8) << "GPA"
       << "Ngay sinh\n";

  cout << string(58, '-') << '\n';

  for (NODE *p = l.pHead; p != nullptr; p = p->pNext) {
    PrintStudent(p->info);
  }
}

// ===================== DOC FILE =====================
// Dinh dang data.txt:
// 23200085,Nguyen Tran Qui Hoa,24/06/2005,8.5

void ReadFile(FILE *f, LIST &l) {
  if (f == nullptr) {
    cout << "File khong hop le.\n";
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), f) != nullptr) {
    if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0') {
      continue;
    }

    Student s{};
    int day = 0, month = 0;
    unsigned int year = 0;

    char *token = strtok(line, ",\r\n");
    if (token == nullptr)
      continue;
    strncpy(s.studentID, token, sizeof(s.studentID) - 1);
    s.studentID[sizeof(s.studentID) - 1] = '\0';

    token = strtok(nullptr, ",\r\n");
    if (token == nullptr)
      continue;
    strncpy(s.name, token, sizeof(s.name) - 1);
    s.name[sizeof(s.name) - 1] = '\0';

    token = strtok(nullptr, ",\r\n");
    if (token == nullptr)
      continue;

    // Chap nhan ca 24/06/2005 va 24 06 2005
    if (sscanf(token, "%d/%d/%u", &day, &month, &year) != 3) {
      if (sscanf(token, "%d %d %u", &day, &month, &year) != 3) {
        continue;
      }
    }

    s.Birthday.day = (unsigned char)day;
    s.Birthday.month = (unsigned char)month;
    s.Birthday.year = year;

    token = strtok(nullptr, ",\r\n");
    if (token == nullptr)
      continue;
    s.GPA = (float)atof(token);

    AddLast(l, GetNode(s));
  }

  fclose(f);
}

// ===================== GHI FILE =====================

void WriteFile(FILE *f, LIST l) {
  if (f == nullptr) {
    cout << "File khong hop le.\n";
    return;
  }

  for (NODE *p = l.pHead; p != nullptr; p = p->pNext) {
    fprintf(f, "%s,%s,%02d/%02d/%u,%.1f\n", p->info.studentID, p->info.name,
            (int)p->info.Birthday.day, (int)p->info.Birthday.month,
            p->info.Birthday.year, p->info.GPA);
  }

  fclose(f);
}

// ====================================================
// SAP XEP TREN PHAN DATA
// ====================================================

// Interchange Sort - tang dan theo GPA
void InterchangeSortLL(LIST &l) {
  for (NODE *p = l.pHead; p != nullptr; p = p->pNext) {
    for (NODE *q = p->pNext; q != nullptr; q = q->pNext) {
      if (CompareByGPA(p->info, q->info) > 0) {
        SwapStudent(p->info, q->info);
      }
    }
  }
}

// Bubble Sort - tang dan theo tuoi
// List don khong di lui duoc, nen dung bien end de danh dau
// bien tren cua vung da sap xep (tu end tro di da sorted).
void BubbleSortLL(LIST &l) {
  if (l.pHead == nullptr || l.pHead == l.pTail)
    return;

  bool swapped;
  NODE *end = nullptr;

  do {
    swapped = false;
    NODE *p = l.pHead;

    while (p->pNext != end) {
      NODE *q = p->pNext;

      if (CompareByAge(p->info, q->info) > 0) {
        SwapStudent(p->info, q->info);
        swapped = true;
      }
      p = p->pNext;
    }

    // Sau luot nay p la phan tu vua day len -> sorted tu p
    end = p;

  } while (swapped);
}

// ====================================================
// SAP XEP TREN LINK
// ====================================================

// Selection Sort - tang dan theo tuoi
void SelectionSortLL(LIST &l) {
  LIST sorted;
  InitList(sorted);

  while (l.pHead != nullptr) {
    // Tim node min, dong thoi track node dung ngay truoc no
    // de con tach ra khoi list (vi list don khong di lui).
    NODE *prevMin = nullptr;
    NODE *minNode = l.pHead;
    NODE *prev = l.pHead;

    for (NODE *p = l.pHead->pNext; p != nullptr; p = p->pNext) {
      if (CompareByAge(p->info, minNode->info) < 0) {
        minNode = p;
        prevMin = prev;
      }
      prev = p;
    }

    DetachNode(l, prevMin, minNode);
    AppendNode(sorted, minNode);
  }

  l = sorted;
}

// Quick Sort - tang dan theo GPA
LIST QuickSortRec(LIST src) {
  if (src.pHead == nullptr || src.pHead == src.pTail) {
    if (src.pHead != nullptr) {
      src.pHead->pNext = nullptr;
      src.pTail = src.pHead;
    }
    return src;
  }

  Student pivot = src.pHead->info;

  LIST less, equal, greater;
  InitList(less);
  InitList(equal);
  InitList(greater);

  NODE *p = src.pHead;

  while (p != nullptr) {
    NODE *next = p->pNext;
    p->pNext = nullptr;

    int cmp = CompareByGPA(p->info, pivot);

    if (cmp < 0) {
      AppendNode(less, p);
    } else if (cmp > 0) {
      AppendNode(greater, p);
    } else {
      AppendNode(equal, p);
    }

    p = next;
  }

  less = QuickSortRec(less);
  greater = QuickSortRec(greater);

  ConcatList(less, equal);
  ConcatList(less, greater);

  return less;
}

void QuickSortLL(LIST &l) { l = QuickSortRec(l); }

// ===================== XOA DANH SACH =====================

void RemoveList(LIST &l) {
  while (l.pHead != nullptr) {
    NODE *p = l.pHead;
    l.pHead = l.pHead->pNext;
    delete p;
  }

  l.pTail = nullptr;
}

// ===================== MAIN =====================

int main() {
  LIST l;
  InitList(l);

  FILE *f = fopen("data.txt", "r");

  if (f == nullptr) {
    cout << "Khong mo duoc file data.txt de doc.\n";
    return 1;
  }

  ReadFile(f, l);

  cout << "DANH SACH BAN DAU:\n";
  PrintList(l);

  cout << "\nChon thuat toan sap xep:\n";
  cout << "1. Interchange Sort - tang dan GPA  (doi data)\n";
  cout << "2. Bubble Sort      - tang dan tuoi (doi data)\n";
  cout << "3. Selection Sort   - tang dan tuoi (doi link)\n";
  cout << "4. Quick Sort       - tang dan GPA  (doi link)\n";
  cout << "Nhap lua chon: ";

  int chon;
  cin >> chon;

  const char *filename = nullptr;

  if (chon == 1) {
    InterchangeSortLL(l);
    filename = "result_interchange.txt";
  } else if (chon == 2) {
    BubbleSortLL(l);
    filename = "result_bubble.txt";
  } else if (chon == 3) {
    SelectionSortLL(l);
    filename = "result_selection.txt";
  } else if (chon == 4) {
    QuickSortLL(l);
    filename = "result_quicksort.txt";
  } else {
    cout << "Lua chon khong hop le, mac dinh dung Quick Sort.\n";
    QuickSortLL(l);
    filename = "result_quicksort.txt";
  }

  cout << "\nDANH SACH SAU KHI SAP XEP:\n";
  PrintList(l);

  f = fopen(filename, "w");

  if (f == nullptr) {
    cout << "Khong mo duoc file " << filename << " de ghi.\n";
    RemoveList(l);
    return 1;
  }

  WriteFile(f, l);

  cout << "\nDa ghi ket qua vao file " << filename << "\n";

  RemoveList(l);
  return 0;
}