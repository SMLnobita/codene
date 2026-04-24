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
// 1. MERGE SORT - tang dan GPA (doi link)
// ====================================================

// Tim node o giua cua list dung slow/fast pointer
NODE *GetMiddle(NODE *head) {
  if (head == nullptr)
    return nullptr;

  NODE *slow = head;
  NODE *fast = head->pNext;

  while (fast != nullptr && fast->pNext != nullptr) {
    slow = slow->pNext;
    fast = fast->pNext->pNext;
  }

  return slow;
}

// Tron 2 list da sap xep tang dan theo GPA thanh 1 list da sap xep
LIST Merge(LIST a, LIST b) {
  LIST result;
  InitList(result);

  while (a.pHead != nullptr && b.pHead != nullptr) {
    NODE *p;

    if (CompareByGPA(a.pHead->info, b.pHead->info) <= 0) {
      p = a.pHead;
      a.pHead = p->pNext;
      if (a.pHead == nullptr)
        a.pTail = nullptr;
    } else {
      p = b.pHead;
      b.pHead = p->pNext;
      if (b.pHead == nullptr)
        b.pTail = nullptr;
    }

    p->pNext = nullptr;
    AppendNode(result, p);
  }

  // Noi phan con lai (1 trong 2 list co the con node)
  ConcatList(result, a);
  ConcatList(result, b);

  return result;
}

// Ham de quy: chia doi, sort 2 nua, tron lai
LIST MergeSortRec(LIST src) {
  if (src.pHead == nullptr || src.pHead == src.pTail) {
    return src;
  }

  NODE *mid = GetMiddle(src.pHead);

  LIST left, right;
  InitList(left);
  InitList(right);

  left.pHead = src.pHead;
  left.pTail = mid;
  right.pHead = mid->pNext;
  right.pTail = src.pTail;
  mid->pNext = nullptr;

  left = MergeSortRec(left);
  right = MergeSortRec(right);

  return Merge(left, right);
}

void MergeSortLL(LIST &l) { l = MergeSortRec(l); }

// ====================================================
// 2. RADIX SORT - tang dan MSSV (doi link)
// ====================================================

// Gia su tat ca MSSV co cung do dai, chi gom cac ky tu '0'-'9'.
// LSD Radix Sort: duyet tu chu so phai sang trai,
// moi luot phan phoi vao 10 bucket roi gom lai.
void RadixSortLL(LIST &l) {
  if (l.pHead == nullptr || l.pHead == l.pTail)
    return;

  const int BUCKET_COUNT = 10;
  int len = (int)strlen(l.pHead->info.studentID);

  LIST bucket[BUCKET_COUNT];

  for (int pos = len - 1; pos >= 0; pos--) {
    for (int i = 0; i < BUCKET_COUNT; i++) {
      InitList(bucket[i]);
    }

    // Phan phoi tung node vao bucket tuong ung voi chu so tai vi tri pos
    while (l.pHead != nullptr) {
      NODE *p = l.pHead;
      l.pHead = p->pNext;
      if (l.pHead == nullptr)
        l.pTail = nullptr;
      p->pNext = nullptr;

      char c = p->info.studentID[pos];
      int digit = 0;
      if (c >= '0' && c <= '9')
        digit = c - '0';

      AppendNode(bucket[digit], p);
    }

    // Gom cac bucket lai theo thu tu 0 -> 9
    for (int i = 0; i < BUCKET_COUNT; i++) {
      ConcatList(l, bucket[i]);
    }
  }
}

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

  cout << "\nChon thuat toan sap xep (bai tap nang cao):\n";
  cout << "1. Merge Sort - tang dan GPA  (doi link)\n";
  cout << "2. Radix Sort - tang dan MSSV (doi link)\n";
  cout << "Nhap lua chon: ";

  int chon;
  cin >> chon;

  const char *filename = nullptr;

  if (chon == 1) {
    MergeSortLL(l);
    filename = "result_merge.txt";
  } else if (chon == 2) {
    RadixSortLL(l);
    filename = "result_radix.txt";
  } else {
    cout << "Lua chon khong hop le, mac dinh dung Merge Sort.\n";
    MergeSortLL(l);
    filename = "result_merge.txt";
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