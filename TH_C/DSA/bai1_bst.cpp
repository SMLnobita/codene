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
    if (t == NULL) {
        t = createNode(x);
        return;
    }

    if (x < t->Key)
        insertNode(t->pLeft, x);
    else if (x > t->Key)
        insertNode(t->pRight, x);
}

Tree createTree(char* filename) {
    ifstream file(filename);
    Tree t = NULL;
    int x;

    while (file >> x) {
        insertNode(t, x);
    }

    file.close();
    return t;
}

void Preorder(Tree t) {
    if (t != NULL) {
        cout << t->Key << " ";
        Preorder(t->pLeft);
        Preorder(t->pRight);
    }
}

void Inorder(Tree t) {
    if (t != NULL) {
        Inorder(t->pLeft);
        cout << t->Key << " ";
        Inorder(t->pRight);
    }
}

void Postorder(Tree t) {
    if (t != NULL) {
        Postorder(t->pLeft);
        Postorder(t->pRight);
        cout << t->Key << " ";
    }
}

int main() {
    char filename[] = "input_bai1.txt";
    Tree t = createTree(filename);

    cout << "Preorder: ";
    Preorder(t);

    cout << "\nInorder: ";
    Inorder(t);

    cout << "\nPostorder: ";
    Postorder(t);

    return 0;
}
