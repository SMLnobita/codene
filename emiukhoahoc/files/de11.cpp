#include <iostream>
#include <fstream>
using namespace std;

struct TNode {
    int Key;
    TNode* pLeft;
    TNode* pRight;
};

typedef TNode* Tree;

TNode* createNode(int x) {
    TNode* p = new TNode;
    p->Key = x;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}

void insertNode(Tree& t, int x) {
    if (t == NULL) { t = createNode(x); return; }
    if (x < t->Key)       insertNode(t->pLeft, x);
    else if (x > t->Key)  insertNode(t->pRight, x);
}

Tree createTree(char* filename) {
    ifstream file(filename);
    Tree t = NULL;
    int x;
    while (file >> x)
        insertNode(t, x);
    file.close();
    return t;
}

TNode* minNode(Tree t) {
    while (t->pLeft != NULL) t = t->pLeft;
    return t;
}

void deleteNode(Tree& t, int x) {
    if (t == NULL) return;
    if (x < t->Key)       deleteNode(t->pLeft, x);
    else if (x > t->Key)  deleteNode(t->pRight, x);
    else {
        if (t->pLeft == NULL) {
            TNode* tmp = t->pRight; delete t; t = tmp;
        } else if (t->pRight == NULL) {
            TNode* tmp = t->pLeft;  delete t; t = tmp;
        } else {
            TNode* suc = minNode(t->pRight);
            t->Key = suc->Key;
            deleteNode(t->pRight, suc->Key);
        }
    }
}

// NLR: goc -> trai -> phai
void NLR(Tree t) {
    if (t == NULL) return;
    cout << t->Key << " ";
    NLR(t->pLeft);
    NLR(t->pRight);
}

int main() {
    char filename[] = "input.txt";
    Tree t = createTree(filename);

    cout << "NLR (Pre-order): ";
    NLR(t);
    cout << endl;

    int x;
    cout << "Nhap gia tri can xoa: ";
    cin >> x;
    deleteNode(t, x);

    cout << "NLR sau khi xoa " << x << ": ";
    NLR(t);
    cout << endl;

    return 0;
}
