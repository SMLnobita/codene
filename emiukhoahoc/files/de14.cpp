#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct TNode {
    int Key;
    int height;
    TNode* pLeft;
    TNode* pRight;
};

typedef TNode* Tree;

TNode* createNode(int x) {
    TNode* p = new TNode;
    p->Key = x;
    p->height = 1;
    p->pLeft = NULL;
    p->pRight = NULL;
    return p;
}

int getHeight(Tree t) { return t ? t->height : 0; }

void updateHeight(Tree t) {
    if (t) t->height = 1 + max(getHeight(t->pLeft), getHeight(t->pRight));
}

int balanceFactor(Tree t) {
    return t ? getHeight(t->pLeft) - getHeight(t->pRight) : 0;
}

Tree rotateRight(Tree y) {
    Tree x = y->pLeft;
    Tree T = x->pRight;
    x->pRight = y; y->pLeft = T;
    updateHeight(y); updateHeight(x);
    return x;
}

Tree rotateLeft(Tree x) {
    Tree y = x->pRight;
    Tree T = y->pLeft;
    y->pLeft = x; x->pRight = T;
    updateHeight(x); updateHeight(y);
    return y;
}

Tree balance(Tree t) {
    updateHeight(t);
    int bf = balanceFactor(t);
    if (bf > 1) {
        if (balanceFactor(t->pLeft) < 0)
            t->pLeft = rotateLeft(t->pLeft);  // LR
        return rotateRight(t);                // LL
    }
    if (bf < -1) {
        if (balanceFactor(t->pRight) > 0)
            t->pRight = rotateRight(t->pRight); // RL
        return rotateLeft(t);                   // RR
    }
    return t;
}

Tree insertNode(Tree t, int x) {
    if (t == NULL) return createNode(x);
    if (x < t->Key)       t->pLeft  = insertNode(t->pLeft,  x);
    else if (x > t->Key)  t->pRight = insertNode(t->pRight, x);
    return balance(t);
}

// Tao AVL tu mang ngau nhien
Tree createTreeRandom(int arr[], int n) {
    Tree t = NULL;
    for (int i = 0; i < n; i++)
        t = insertNode(t, arr[i]);
    return t;
}

void LNR(Tree t) {
    if (t == NULL) return;
    LNR(t->pLeft);
    cout << t->Key << " ";
    LNR(t->pRight);
}

int main() {
    srand((unsigned)time(NULL));

    const int N = 10;
    int arr[N];
    cout << "Mang ngau nhien: ";
    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100 + 1;
        cout << arr[i] << " ";
    }
    cout << endl;

    Tree t = createTreeRandom(arr, N);
    cout << "LNR AVL (tang dan): ";
    LNR(t);
    cout << endl;

    int newVal = rand() % 100 + 1;
    cout << "Chen them " << newVal << " vao AVL" << endl;
    t = insertNode(t, newVal);
    cout << "LNR sau khi chen: ";
    LNR(t);
    cout << endl;

    return 0;
}
