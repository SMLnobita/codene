#include <cstdio>
#include <iostream>

struct NODE {
  int data;
  NODE *pNext;
};

struct LIST {
  NODE *pHead;
  NODE *pTail;
};

void Init(LIST &myList) { myList.pHead = myList.pTail = NULL; }

NODE *GetNode(int value) {
  NODE *p = new NODE;
  p->data = value;
  p->pNext = NULL;
  return p;
}

void AddTail(LIST &myList, NODE *p) {
  p->pNext = NULL;
  if (myList.pHead == NULL) {
    myList.pHead = myList.pTail = p;
  } else {
    myList.pTail->pNext = p;
    myList.pTail = p;
  }
}

int DocFile(const char *tenFile, LIST &myList) {
  FILE *fi = fopen(tenFile, "rt");
  int x, dem = 0;
  while (fscanf(fi, "%d", &x) == 1) {
    AddTail(myList, GetNode(x));
    dem++;
  }
  fclose(fi);
  return dem;
}

void InList(LIST &myList) {
  NODE *p = myList.pHead;
  while (p != NULL) {
    printf("%d -> ", p->data);
    p = p->pNext;
  }
  printf("NULL\n");
}

void Destroy(LIST &myList) {
  while (myList.pHead != NULL) {
    NODE *p = myList.pHead;
    myList.pHead = myList.pHead->pNext;
    delete p;
  }
  myList.pTail = NULL;
}

void ListQSort(LIST &l) {
  if (l.pHead == l.pTail)
    return;

  LIST l1, l2;
  l1.pHead = l1.pTail = NULL;
  l2.pHead = l2.pTail = NULL;

  NODE *X = l.pHead;
  l.pHead = X->pNext;

  while (l.pHead != NULL) {
    NODE *p = l.pHead;
    l.pHead = p->pNext;
    p->pNext = NULL;
    if (p->data <= X->data)
      AddTail(l1, p);
    else
      AddTail(l2, p);
  }

  ListQSort(l1);
  ListQSort(l2);

  if (l1.pHead != NULL) {
    l.pHead = l1.pHead;
    l1.pTail->pNext = X;
  } else {
    l.pHead = X;
  }

  X->pNext = l2.pHead;

  if (l2.pHead != NULL)
    l.pTail = l2.pTail;
  else
    l.pTail = X;
}

void TimVaChenSau(LIST &myList, int X, int val) {
  NODE *p = myList.pHead;
  while (p != NULL && p->data != X) {
    p = p->pNext;
  }

  if (p == NULL) {
    printf("Khong tim thay\n");
    return;
  }

  NODE *q = GetNode(val);
  q->pNext = p->pNext;
  p->pNext = q;
  if (p == myList.pTail) {
    myList.pTail = q;
  }
  printf("Da chen %d vao sau %d\n", val, X);
}

int main() {
  LIST myList;
  Init(myList);
  int n = DocFile("input2.txt", myList);
  printf("Danh sach LIST: ");
  InList(myList);

  ListQSort(myList);
  printf("Danh sach sau khi sap xep: ");
  InList(myList);

  TimVaChenSau(myList, 82, 100);
  printf("Danh sach sau khi chen: ");
  InList(myList);

  return 0;
}