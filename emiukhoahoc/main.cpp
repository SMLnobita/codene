#include  <iostream>

typedef struct tagNode  {
    int Info;
    struct tagNode *pNext;
} NODE;

typedef struct tagList {
    NODE *pHead;
    NODE *pTail;
} LIST;

NODE *getNode(int value) {
    NODE *newNode= new NODE;
    newNode->Info=value;
    newNode->pNext=nullptr;
    return newNode;
}

void addFirst(LIST &myList, int value) {
    NODE *newNode = getNode(value);
    if (myList.pHead==nullptr) {
        myList.pHead=newNode;
        myList.pTail=myList.pHead;
    } else {
        newNode->pNext=myList.pHead;
        myList.pHead=newNode;
    }
}

void addTail(LIST &myList, int value) {
    NODE *newNode = getNode(value);
    if (myList.pHead==nullptr) {
        myList.pHead=newNode;
        myList.pTail=myList.pHead;
    } else {
        myList.pTail->pNext=newNode;
        myList.pTail=newNode;
    }
}

void addAfter(LIST &myList,NODE *q, int value) {
    if (q==nullptr) {
        addFirst(myList,value);
        return;
    }
    NODE *newNode = getNode(value);
    newNode->pNext=q->pNext;
    q->pNext=newNode;
    if (q == myList.pTail)
        myList.pTail=newNode;
}

void removeList(LIST &myList) {
    while (myList.pHead!=nullptr) {
        NODE *p = myList.pHead;
        myList.pHead=myList.pHead->pNext;
        delete p;
    }
    myList.pTail=nullptr;
}

void removeHead(LIST &myList) {
    if (myList.pHead!=nullptr) {
        NODE *p = myList.pHead;
        myList.pHead=myList.pHead->pNext;
        delete p;
        if (myList.pHead==nullptr)
            myList.pTail=nullptr;
    }
}

void removeNode(LIST &myList, int value) {
    NODE *p = myList.pHead;
    NODE *q = nullptr;
    while (p != nullptr) {
        if (p->Info == value)
            break;
        q = p;
        p = p->pNext;
    }
    // Không tìm thấy
    if (p == nullptr)
        return;
    // Không phải node đầu
    if (q != nullptr) {
        if (p == myList.pTail)
            myList.pTail = q;
        q->pNext = p->pNext;
        delete p;
    }
    // Là node đầu
    else {
        myList.pHead = p->pNext;
        if (myList.pHead == nullptr)
            myList.pTail = nullptr;
        delete p;
    }
}

void initList(LIST &myList) {
    myList.pHead=nullptr;
    myList.pTail=nullptr;
}

// thuat toan xap sep
void hoanvi(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void listSelectionSort(const LIST &myList) {
    NODE *p = myList.pHead;
    while (p!=myList.pTail) {
        NODE *q = p->pNext;
        NODE *min = p;
        while (q!=nullptr) {
            if (q->Info< min->Info) {
                min = q;
            }
            q = q->pNext;
        }
        hoanvi(min->Info,p->Info);
        p = p->pNext;
    }
}

int main() {
    LIST myList;

    initList(myList);

    addFirst(myList,40);
    addTail(myList,20);
    addTail(myList,60);
    addTail(myList,100);
    //removeNode(myList,20);
    //removeHead(myList);
    NODE *temp = myList.pHead;
    while (temp!=nullptr && temp->Info!= 10) {
        temp=temp->pNext;
    }

    addAfter(myList,temp,25);
    listSelectionSort(myList);
    NODE *p = myList.pHead;
    while (p!=nullptr) {
        std::cout << p->Info << " ";
        p = p->pNext;
    }

    removeList(myList);

    return 0;
}