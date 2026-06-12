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

// KHOI TAO

void InitList(LIST &l) {
  l.pHead = nullptr;
  l.pTail = nullptr;
}

// TAO NODE

NODE *GetNode(const Student &x) {
  NODE *p = new NODE;

  if (p == nullptr) {
    cout << "Khong du bo nho!\n";
    exit(1);
  }

  p->info = x;
  p->pNext = nullptr;
  return p;
}

// THEM NODE

void AddLast(LIST &l, NODE *p) {
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

// NOI DANH SACH

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

// IN DANH SACH

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

void ReadFile(FILE *f, LIST &l) {
  if (f == nullptr) {
    cout << "File khong hop le.\n";
    return;
  }

  char line[256];

  while (fgets(line, sizeof(line), f) != nullptr) {
    if (line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
      continue;

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

// RADIX SORT LINKED LIST - TANG DAN THEO TUOI
// Tuoi nho hon dung truoc.
// Nam sinh lon hon dung truoc.

int GetDateKey(const Student &s) {
  int date = s.Birthday.year * 10000 + s.Birthday.month * 100 + s.Birthday.day;

  return 99991231 - date;
}

int GetMaxKey(const LIST &l) {
  int maxKey = 0;

  for (NODE *p = l.pHead; p != nullptr; p = p->pNext) {
    int key = GetDateKey(p->info);

    if (key > maxKey)
      maxKey = key;
  }

  return maxKey;
}

void RadixSortLL(LIST &l) {
  if (l.pHead == nullptr || l.pHead == l.pTail)
    return;

  int maxKey = GetMaxKey(l);

  for (int exp = 1; maxKey / exp > 0; exp *= 10) {
    LIST bucket[10];

    for (int i = 0; i < 10; i++) {
      InitList(bucket[i]);
    }

    while (l.pHead != nullptr) {
      NODE *p = l.pHead;
      l.pHead = l.pHead->pNext;

      if (l.pHead == nullptr)
        l.pTail = nullptr;

      p->pNext = nullptr;

      int digit = (GetDateKey(p->info) / exp) % 10;

      AddLast(bucket[digit], p);
    }

    InitList(l);

    for (int i = 0; i < 10; i++) {
      ConcatList(l, bucket[i]);
    }
  }
}

void RemoveList(LIST &l) {
  while (l.pHead != nullptr) {
    NODE *p = l.pHead;
    l.pHead = l.pHead->pNext;
    delete p;
  }

  l.pTail = nullptr;
}

int main() {
  LIST l;
  InitList(l);

  FILE *f = fopen("data.txt", "r");

  ReadFile(f, l);

  cout << "DANH SACH BAN DAU:\n";
  PrintList(l);

  RadixSortLL(l);

  cout << "\nDANH SACH SAU KHI SAP XEP TANG THEO TUOI:\n";
  PrintList(l);

  f = fopen("result_radix.txt", "w");

  WriteFile(f, l);

  cout << "\nDa ghi ket qua vao file result_radix.txt\n";

  RemoveList(l);
  return 0;
}