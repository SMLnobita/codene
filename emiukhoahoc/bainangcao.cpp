#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
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
    struct tagNode *pPrev;  // thêm con trỏ trước cho DSLK kép
} NODE;

typedef struct {
    NODE *pHead;
    NODE *pTail;
} LIST;

// ===================== KHỞI TẠO =====================

void banDau(LIST &myList) {
    myList.pHead = nullptr;
    myList.pTail = nullptr;
}

// ===================== TẠO NODE =====================

NODE* GetNode(const Student &value) {
    NODE *newNode = new NODE;
    newNode->info  = value;
    newNode->pNext = nullptr;
    newNode->pPrev = nullptr;
    return newNode;
}

// ===================== THÊM NODE =====================

void AddFirst(LIST &myList, const Student &value) {
    NODE *newNode = GetNode(value);
    if (myList.pHead == nullptr) {
        myList.pHead = myList.pTail = newNode;
    } else {
        newNode->pNext      = myList.pHead;
        myList.pHead->pPrev = newNode;
        myList.pHead        = newNode;
    }
}

void AddLast(LIST &myList, const Student &value) {
    NODE *newNode = GetNode(value);
    if (myList.pHead == nullptr) {
        myList.pHead = myList.pTail = newNode;
    } else {
        newNode->pPrev      = myList.pTail;
        myList.pTail->pNext = newNode;
        myList.pTail        = newNode;
    }
}

void AddAfter(LIST &myList, const Student &value, NODE *q) {
    if (q == nullptr) {
        AddFirst(myList, value);
        return;
    }
    NODE *newNode  = GetNode(value);
    newNode->pNext = q->pNext;
    newNode->pPrev = q;
    if (q->pNext != nullptr)
        q->pNext->pPrev = newNode;
    q->pNext = newNode;
    if (q == myList.pTail)
        myList.pTail = newNode;
}

// ===================== TÌM NODE =====================

NODE* SearchNode(const LIST &myList, const Student &value) {
    NODE *p = myList.pHead;
    while (p != nullptr) {
        if (strcmp(p->info.studentID, value.studentID) == 0)
            return p;
        p = p->pNext;
    }
    return nullptr;
}

// ===================== XÓA NODE =====================

void removeFirst(LIST &myList) {
    if (myList.pHead == nullptr) return;
    NODE *p = myList.pHead;
    myList.pHead = myList.pHead->pNext;
    if (myList.pHead != nullptr)
        myList.pHead->pPrev = nullptr;
    else
        myList.pTail = nullptr;
    delete p;
}

void removeLast(LIST &myList) {
    if (myList.pHead == nullptr) return;
    if (myList.pHead == myList.pTail) {
        delete myList.pHead;
        myList.pHead = myList.pTail = nullptr;
        return;
    }
    NODE *p = myList.pTail;
    myList.pTail        = myList.pTail->pPrev;
    myList.pTail->pNext = nullptr;
    delete p;
}

void removeList(LIST &myList) {
    while (myList.pHead != nullptr) {
        NODE *p = myList.pHead;
        myList.pHead = myList.pHead->pNext;
        delete p;
    }
    myList.pTail = nullptr;
}

// ===================== IN DANH SÁCH =====================

void PrintStudent(const Student &s) {
    cout << left << setw(12) << s.studentID
         << setw(24) << s.name
         << setw(6)  << fixed << setprecision(1) << s.GPA;
    cout << setw(2) << setfill('0') << +s.Birthday.day  << "/"
         << setw(2) << setfill('0') << +s.Birthday.month << "/"
         << s.Birthday.year << setfill(' ') << "\n";
}

void PrintList(const LIST &myList) {
    cout << left << setw(12) << "MSSV"
         << setw(24) << "Ho Ten"
         << setw(6)  << "GPA"
         << "Ngay Sinh\n";
    cout << string(56, '-') << "\n";
    NODE *p = myList.pHead;
    while (p != nullptr) {
        PrintStudent(p->info);
        p = p->pNext;
    }
}

// ===================== GHI FILE =====================

void WriteFile(const LIST &myList, const char *filename) {
    ofstream f(filename);
    if (!f) {
        cout << "Khong mo duoc file " << filename << "\n";
        return;
    }
    NODE *p = myList.pHead;
    while (p != nullptr) {
        // định dạng: 23200085,Nguyen Tran Qui Hoa,24 6 2005,8.5
        f << p->info.studentID                  << ","
          << p->info.name                       << ","
          << setw(2) << setfill('0') << (int)p->info.Birthday.day   << "/"
          << setw(2) << setfill('0') << (int)p->info.Birthday.month << "/"
          << setfill(' ') << p->info.Birthday.year << ","
          << p->info.GPA                         << "\n";
        p = p->pNext;
    }
    f.close();
    cout << "Da ghi " << filename << " thanh cong.\n";
}

// ===================== ĐỌC FILE =====================

void ReadFile(LIST &myList, const char *filename) {
    ifstream f(filename);
    if (!f) {
        cout << "Khong mo duoc file " << filename << "\n";
        return;
    }
    char line[120];
    while (f.getline(line, sizeof(line))) {
        if (strlen(line) == 0) continue;

        Student s;
        int day, month;

        // tách theo dấu ','
        char *token = strtok(line, ",");
        if (!token) continue;
        strncpy(s.studentID, token, 8); s.studentID[8] = '\0';

        token = strtok(nullptr, ",");
        if (!token) continue;
        strncpy(s.name, token, 49); s.name[49] = '\0';

        token = strtok(nullptr, ",");
        if (!token) continue;
        sscanf(token, "%d/%d/%u", &day, &month, &s.Birthday.year);
        s.Birthday.day   = (unsigned char)day;
        s.Birthday.month = (unsigned char)month;

        token = strtok(nullptr, ",");
        if (!token) continue;
        s.GPA = (float)atof(token);

        AddLast(myList, s);
    }
    f.close();
    cout << "Da doc " << filename << " thanh cong.\n";
}

// ===================== LỌC GPA < 5 =====================
// Xóa SV có GPA < 5 khỏi list1, thêm vào list2

void FilterLowGPA(LIST &list1, LIST &list2) {
    NODE *p = list1.pHead;
    while (p != nullptr) {
        NODE *next = p->pNext;
        if (p->info.GPA < 5.0f) {
            // thêm vào list2
            AddLast(list2, p->info);

            // gỡ khỏi list1
            if (p->pPrev != nullptr)
                p->pPrev->pNext = p->pNext;
            else
                list1.pHead = p->pNext;

            if (p->pNext != nullptr)
                p->pNext->pPrev = p->pPrev;
            else
                list1.pTail = p->pPrev;

            delete p;
        }
        p = next;
    }
}


// ===================== MAIN =====================

int main() {
    LIST list1, list2;
    banDau(list1);
    banDau(list2);

    // --- Đọc từ data.txt ---
    ReadFile(list1, "data.txt");

    cout << "=== DANH SACH BAN DAU ===\n";
    PrintList(list1);

    // --- Lọc GPA < 5 ---
    FilterLowGPA(list1, list2);

    cout << "\n=== DANH SACH SV GPA < 5 ===\n";
    PrintList(list2);

    // --- Ghi list2 ra output.txt ---
    WriteFile(list2, "output.txt");

    // --- Dọn bộ nhớ ---
    removeList(list1);
    removeList(list2);
    return 0;
}
