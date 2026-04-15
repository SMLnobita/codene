//
// Created by nguyenhoa on 4/13/2026.
//
#include <cstring>
#include <iomanip>
#include <iostream>
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
}Student;

typedef struct tagNode {
    Student info;
    struct tagNode *pNext;
}NODE;

typedef struct {
    NODE *pHead;
    NODE *pTail;
}LIST;

NODE* GetNode(const Student &value) {
    NODE *newNode = new NODE;
    newNode->info=value;
    newNode->pNext=nullptr;
    return newNode;
}

void AddFirst(LIST &myList,const Student &value) {
    NODE *newNode = GetNode(value);
    if (myList.pHead==nullptr) {
        myList.pHead=newNode;
        myList.pTail=newNode;
    } else {
        newNode->pNext=myList.pHead;
        myList.pHead=newNode;
    }
}

void AddLast(LIST &myList, const Student &value) {
    NODE *newNode = GetNode(value);
    if (myList.pHead==nullptr) {
        myList.pHead=newNode;
        myList.pTail=newNode;
    } else {
        myList.pTail->pNext=newNode;
        myList.pTail=newNode;
    }
}

NODE *SearchNode(const LIST &myList,const Student &value) {
    NODE *p = myList.pHead;
    while (p!=nullptr) {
        if (strcmp(p->info.studentID,value.studentID)==0) {
            return p;
        }
        p = p->pNext;
    }
    return nullptr;
}

void AddAfter(LIST &myList,const Student &value, NODE *q) {
    if (q==nullptr) {
        AddFirst(myList,value);
        return;
    }
    NODE *newNode = GetNode(value);
    newNode->pNext=q->pNext;
    q->pNext=newNode;
    if (q == myList.pTail)
        myList.pTail=newNode;
}

void banDau(LIST &myList) {
    myList.pHead=nullptr;
    myList.pTail=nullptr;
}

Student createStudent(const char *id,const char *name, unsigned char day, unsigned char month, unsigned int year, float gpa) {
    Student s;
    strcpy(s.name,name);
    s.Birthday.day=day;
    s.Birthday.month=month;
    s.Birthday.year=year;
    strcpy(s.studentID,id);
    s.GPA=gpa;
    return s;
}

void PrintNe(const Student &s) {
    cout << left << setw(12) << s.studentID << setw(24) << s.name << setw(10) << s.GPA;
    cout << setw(2) << setfill('0') << +s.Birthday.day << "/"
    << setw(2) << setfill('0') << +s.Birthday.month << "/" << s.Birthday.year  << setfill(' ')<< endl;
}

void PrintList(LIST myList) {
    NODE *p = myList.pHead;
    cout << left << setw(12) << "MSSV" << setw(24) << "Name" << setw(10) << "GPA"  << "Birth Day" << endl;
    while (p!=nullptr) {
        PrintNe(p->info);
        p = p->pNext;
    }
}

void removeList(LIST &myList) {
    while (myList.pHead!=nullptr) {
        NODE *p = myList.pHead;
        myList.pHead=myList.pHead->pNext;
        delete p;
    }
    myList.pTail=nullptr;
}

void removeFirst(LIST &myList) {
    if (myList.pHead!=nullptr) {
        NODE *p = myList.pHead;
        myList.pHead=myList.pHead->pNext;
        delete p;
    }
    if (myList.pHead==nullptr){
        myList.pTail=nullptr;
    }
}

void removeLast(LIST &myList) {
    // list rỗng
    if (myList.pHead == nullptr) return;

    // chỉ có 1 node
    if (myList.pHead == myList.pTail) {
        delete myList.pHead;
        myList.pHead = nullptr;
        myList.pTail = nullptr;
        return;
    }

    // tìm node trước tail
    NODE *p = myList.pHead;
    while (p->pNext != myList.pTail) {
        p = p->pNext;
    }

    delete myList.pTail;
    p->pNext = nullptr;
    myList.pTail = p;
}

int main() {
    LIST myList;
    banDau(myList);

    Student s1 = createStudent("23200085","Nguyen Tran Qui Hoa", 24, 6, 2005, 8.5);
    Student s2 = createStudent("23200008","Dinh Tien Dung", 19,9,2005,9);
    Student s3= createStudent("2320007", "Nguyen Huu Duc", 19,5,2005,10);
    Student s4 = createStudent("23200081", "Nguyen Nhat Hao", 24,2,2005,10);

    AddFirst(myList,s1);
    AddLast(myList,s2);
    AddFirst(myList,s3);

    NODE *temp = SearchNode(myList,s3);
    AddAfter(myList,s4,temp);
    //removeFirst(myList);
    //removeLast(myList);
    PrintList(myList);

    removeList(myList);
    return  0;
}