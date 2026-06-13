#include <cstdio>
#include <cstring>

struct DNODE {
  char data[11];
  DNODE *pNext;
  DNODE *pPrev;
};

struct DLIST {
  DNODE *pHead;
  DNODE *pTail;
};

void Init(DLIST &l) { l.pHead = l.pTail = NULL; }

DNODE *GetNode(const char *s) {
  DNODE *p = new DNODE;
  strncpy(p->data, s, 10);
  p->data[10] = '\0';
  p->pNext = p->pPrev = NULL;
  return p;
}

void AddFirst(DLIST &l, DNODE *new_ele) {
  if (l.pHead == NULL) {
    l.pHead = new_ele;
    l.pTail = l.pHead;
  } else {
    new_ele->pNext = l.pHead; // (1)
    l.pHead->pPrev = new_ele; // (2)
    l.pHead = new_ele;        // (3)
  }
}

void AddTail(DLIST &l, DNODE *new_ele) {
  if (l.pHead == NULL) {
    l.pHead = new_ele;
    l.pTail = l.pHead;
  } else {
    l.pTail->pNext = new_ele; // (1)
    new_ele->pPrev = l.pTail; // (2)
    l.pTail = new_ele;        // (3)
  }
}

void AddAfter(DLIST &l, DNODE *q, DNODE *new_ele) {
  if (q != NULL) {
    DNODE *p = q->pNext;
    new_ele->pNext = p; // (1)
    new_ele->pPrev = q; // (2)
    q->pNext = new_ele; // (3)
    if (p != NULL)
      p->pPrev = new_ele; // (4)
    if (q == l.pTail)
      l.pTail = new_ele;
  } else { // chèn vào đầu danh sách
    AddFirst(l, new_ele);
  }
}

// Chèn có thứ tự ASCII
void InsertSorted(DLIST &l, DNODE *new_ele) {
  if (l.pHead == NULL || strcmp(new_ele->data, l.pHead->data) <= 0) {
    AddFirst(l, new_ele);
    return;
  }
  DNODE *cur = l.pHead;
  while (cur->pNext != NULL && strcmp(new_ele->data, cur->pNext->data) > 0)
    cur = cur->pNext;
  AddAfter(l, cur, new_ele);
}

void DocFile(const char *tenFile, DLIST &l) {
  FILE *fi = fopen(tenFile, "rt");
  if (fi == NULL) {
    printf("Khong mo duoc file\n");
    return;
  }
  char buf[11];
  while (fscanf(fi, "%10s", buf) == 1)
    InsertSorted(l, GetNode(buf));
  fclose(fi);
}

void InList(DLIST &l) {
  DNODE *p = l.pHead;
  while (p != NULL) {
    printf("[%s] <-> ", p->data);
    p = p->pNext;
  }
  printf("NULL\n");
}

// Câu 3: Xóa, duyệt từ cuối về đầu
void XoaTuCuoi(DLIST &l, const char *target) {
  DNODE *p = l.pTail;
  while (p != NULL) {
    if (strcmp(p->data, target) == 0) {
      if (p->pPrev != NULL)
        p->pPrev->pNext = p->pNext;
      else
        l.pHead = p->pNext;

      if (p->pNext != NULL)
        p->pNext->pPrev = p->pPrev;
      else
        l.pTail = p->pPrev;

      delete p;
      printf("Da xoa \"%s\"\n", target);
      return;
    }
    p = p->pPrev;
  }
  printf("Khong tim thay \"%s\"\n", target);
}

void Destroy(DLIST &l) {
  while (l.pHead != NULL) {
    DNODE *p = l.pHead;
    l.pHead = l.pHead->pNext;
    delete p;
  }
  l.pTail = NULL;
}

int main() {
  DLIST myList;
  Init(myList);

  DocFile("input.txt", myList);
  printf("Danh sach (ASCII sort): ");
  InList(myList);

  XoaTuCuoi(myList, "hello");
  printf("Sau khi xoa: ");
  InList(myList);

  Destroy(myList);
  return 0;
}