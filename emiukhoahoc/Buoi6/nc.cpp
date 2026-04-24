#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>

using namespace std;

// ===================== STRUCT =====================

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
  struct tagNode *pPrev;
} NODE;

typedef struct {
  NODE *pHead;
  NODE *pTail;
} LIST;

// ===================== KHOI TAO =====================

void banDau(LIST &myList) {
  myList.pHead = nullptr;
  myList.pTail = nullptr;
}

bool IsEmpty(const LIST &myList) { return myList.pHead == nullptr; }

// ===================== TAO NODE =====================

NODE *GetNode(const Student &value) {
  NODE *newNode = new NODE;
  newNode->info = value;
  newNode->pNext = nullptr;
  newNode->pPrev = nullptr;
  return newNode;
}

// ===================== THEM NODE =====================

void AddLast(LIST &myList, const Student &value) {
  NODE *newNode = GetNode(value);

  if (myList.pHead == nullptr) {
    myList.pHead = myList.pTail = newNode;
  } else {
    newNode->pPrev = myList.pTail;
    myList.pTail->pNext = newNode;
    myList.pTail = newNode;
  }
}

// Them node co san vao cuoi list, khong cap phat node moi
void AppendNode(LIST &myList, NODE *p) {
  if (p == nullptr)
    return;

  p->pNext = nullptr;
  p->pPrev = nullptr;

  if (myList.pHead == nullptr) {
    myList.pHead = myList.pTail = p;
  } else {
    p->pPrev = myList.pTail;
    myList.pTail->pNext = p;
    myList.pTail = p;
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
    b.pHead->pPrev = a.pTail;
    a.pTail = b.pTail;
  }

  b.pHead = nullptr;
  b.pTail = nullptr;
}

// Cap nhat lai pTail sau khi da thay doi pHead
void UpdateTail(LIST &myList) {
  myList.pTail = myList.pHead;

  if (myList.pTail == nullptr)
    return;

  while (myList.pTail->pNext != nullptr) {
    myList.pTail = myList.pTail->pNext;
  }
}

// ===================== SO SANH =====================

int CompareGPA(const Student &a, const Student &b) {
  if (a.GPA < b.GPA)
    return -1;
  if (a.GPA > b.GPA)
    return 1;

  // Neu GPA bang nhau thi xep theo MSSV
  return strcmp(a.studentID, b.studentID);
}

int CompareID(const Student &a, const Student &b) {
  return strcmp(a.studentID, b.studentID);
}

// ===================== IN DANH SACH =====================

void PrintStudent(const Student &s) {
  cout << left << setw(12) << s.studentID << setw(26) << s.name << setw(8)
       << fixed << setprecision(1) << s.GPA;

  cout << right << setfill('0') << setw(2) << (int)s.Birthday.day << "/"
       << setw(2) << (int)s.Birthday.month << "/" << s.Birthday.year
       << setfill(' ') << left << "\n";
}

void PrintList(const LIST &myList) {
  cout << left << setw(12) << "MSSV" << setw(26) << "Ho ten" << setw(8) << "GPA"
       << "Ngay sinh\n";

  cout << string(58, '-') << "\n";

  NODE *p = myList.pHead;

  while (p != nullptr) {
    PrintStudent(p->info);
    p = p->pNext;
  }
}

// ===================== DOC FILE =====================
// Dinh dang file data.txt:
// 23200085,Nguyen Tran Qui Hoa,24/06/2005,8.5

void ReadFile(FILE *f, LIST &myList) {
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
    int day = 0;
    int month = 0;
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

    AddLast(myList, s);
  }
}

// ===================== GHI FILE =====================

void WriteFile(FILE *f, LIST myList) {
  if (f == nullptr) {
    cout << "File khong hop le.\n";
    return;
  }

  NODE *p = myList.pHead;

  while (p != nullptr) {
    fprintf(f, "%s,%s,%02d/%02d/%u,%.1f\n", p->info.studentID, p->info.name,
            (int)p->info.Birthday.day, (int)p->info.Birthday.month,
            p->info.Birthday.year, p->info.GPA);

    p = p->pNext;
  }
}

// ====================================================
// CAU 1 NANG CAO:
// Sap xep diem tang dan bang Merge Sort tren lien ket
// ====================================================

// Tach danh sach thanh 2 nua
NODE *SplitList(NODE *head) {
  if (head == nullptr || head->pNext == nullptr) {
    return nullptr;
  }

  NODE *slow = head;
  NODE *fast = head;

  while (fast->pNext != nullptr && fast->pNext->pNext != nullptr) {
    slow = slow->pNext;
    fast = fast->pNext->pNext;
  }

  NODE *second = slow->pNext;
  slow->pNext = nullptr;

  if (second != nullptr) {
    second->pPrev = nullptr;
  }

  return second;
}

// Tron 2 danh sach da sap xep theo GPA
NODE *MergeByGPA(NODE *a, NODE *b) {
  if (a == nullptr)
    return b;
  if (b == nullptr)
    return a;

  NODE *head = nullptr;
  NODE *tail = nullptr;

  while (a != nullptr && b != nullptr) {
    NODE *chosen = nullptr;

    if (CompareGPA(a->info, b->info) <= 0) {
      chosen = a;
      a = a->pNext;
    } else {
      chosen = b;
      b = b->pNext;
    }

    chosen->pNext = nullptr;
    chosen->pPrev = nullptr;

    if (head == nullptr) {
      head = tail = chosen;
    } else {
      tail->pNext = chosen;
      chosen->pPrev = tail;
      tail = chosen;
    }
  }

  NODE *remain = (a != nullptr) ? a : b;

  while (remain != nullptr) {
    NODE *next = remain->pNext;

    remain->pNext = nullptr;
    remain->pPrev = nullptr;

    if (head == nullptr) {
      head = tail = remain;
    } else {
      tail->pNext = remain;
      remain->pPrev = tail;
      tail = remain;
    }

    remain = next;
  }

  return head;
}

// De quy Merge Sort
NODE *MergeSortNode(NODE *head) {
  if (head == nullptr || head->pNext == nullptr) {
    if (head != nullptr) {
      head->pPrev = nullptr;
    }
    return head;
  }

  NODE *second = SplitList(head);

  head = MergeSortNode(head);
  second = MergeSortNode(second);

  return MergeByGPA(head, second);
}

void MergeSortLL(LIST &myList) {
  myList.pHead = MergeSortNode(myList.pHead);
  UpdateTail(myList);
}

// ====================================================
// CAU 2 NANG CAO:
// Sap xep sinh vien theo ID tang dan bang Radix Sort
// tren phan lien ket
// ====================================================

int MaxIDLength(const LIST &myList) {
  int maxLen = 0;

  NODE *p = myList.pHead;

  while (p != nullptr) {
    int len = strlen(p->info.studentID);

    if (len > maxLen) {
      maxLen = len;
    }

    p = p->pNext;
  }

  return maxLen;
}

// Lay chu so cua MSSV tu phai sang trai
// pos = 0: hang don vi
// pos = 1: hang chuc
// pos = 2: hang tram
int GetDigitFromRight(const char id[], int pos) {
  int len = strlen(id);
  int index = len - 1 - pos;

  if (index < 0) {
    return 0;
  }

  if (isdigit((unsigned char)id[index])) {
    return id[index] - '0';
  }

  return 0;
}

void RadixSortIDLL(LIST &myList) {
  int maxLen = MaxIDLength(myList);

  for (int pos = 0; pos < maxLen; pos++) {
    LIST bucket[10];

    for (int i = 0; i < 10; i++) {
      banDau(bucket[i]);
    }

    NODE *p = myList.pHead;

    // Tach het node cua myList dua vao cac bucket
    while (p != nullptr) {
      NODE *next = p->pNext;

      p->pNext = nullptr;
      p->pPrev = nullptr;

      int digit = GetDigitFromRight(p->info.studentID, pos);

      AppendNode(bucket[digit], p);

      p = next;
    }

    banDau(myList);

    // Noi bucket 0 -> 9 lai thanh danh sach moi
    for (int i = 0; i < 10; i++) {
      ConcatList(myList, bucket[i]);
    }
  }
}

// ===================== XOA DANH SACH =====================

void removeList(LIST &myList) {
  while (myList.pHead != nullptr) {
    NODE *p = myList.pHead;
    myList.pHead = myList.pHead->pNext;
    delete p;
  }

  myList.pTail = nullptr;
}

// ===================== MAIN =====================

int main() {
  LIST myList;
  banDau(myList);

  FILE *f = fopen("data.txt", "r");

  if (f == nullptr) {
    cout << "Khong mo duoc file data.txt de doc.\n";
    return 1;
  }

  ReadFile(f, myList);
  fclose(f);

  cout << "DANH SACH BAN DAU:\n";
  PrintList(myList);

  cout << "\n===== MENU =====\n";
  cout << "1. Cau 1 nang cao: Merge Sort diem GPA tang dan tren lien ket\n";
  cout << "2. Cau 2 nang cao: Radix Sort ID tang dan tren lien ket\n";
  cout << "Nhap lua chon: ";

  int chon;
  cin >> chon;

  if (chon == 1) {
    MergeSortLL(myList);

    cout << "\nDANH SACH SAU KHI MERGE SORT THEO GPA TANG DAN:\n";
    PrintList(myList);
  } else if (chon == 2) {
    RadixSortIDLL(myList);

    cout << "\nDANH SACH SAU KHI RADIX SORT THEO ID TANG DAN:\n";
    PrintList(myList);
  } else {
    cout << "Lua chon khong hop le.\n";
    removeList(myList);
    return 0;
  }

  f = fopen("data_sorted.txt", "w");

  if (f == nullptr) {
    cout << "Khong mo duoc file data_sorted.txt de ghi.\n";
    removeList(myList);
    return 1;
  }

  WriteFile(f, myList);
  fclose(f);

  cout << "\nDa ghi ket qua vao file data_sorted.txt\n";

  removeList(myList);

  return 0;
}