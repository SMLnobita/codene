#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

typedef struct BinaryTreeADT* BinaryTree;

struct BinaryTreeADT {
    Node* root;
};

Node* createNode(int x) {
    Node* p = new Node;
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

void insertNode(Node*& root, int x) {
    if (root == NULL) {
        root = createNode(x);
        return;
    }

    if (x < root->data)
        insertNode(root->left, x);
    else if (x > root->data)
        insertNode(root->right, x);
}

BinaryTree createTree(char* filename) {
    ifstream file(filename);

    BinaryTree t = new BinaryTreeADT;
    t->root = NULL;

    int x;
    while (file >> x) {
        insertNode(t->root, x);
    }

    file.close();
    return t;
}

void TraversalLevel(BinaryTree t) {
    if (t == NULL || t->root == NULL)
        return;

    queue<Node*> q;
    q.push(t->root);

    while (!q.empty()) {
        Node* p = q.front();
        q.pop();

        cout << p->data << " ";

        if (p->left != NULL)
            q.push(p->left);

        if (p->right != NULL)
            q.push(p->right);
    }
}

Node* SearchNode(BinaryTree t, int x) {
    if (t == NULL)
        return NULL;

    Node* p = t->root;

    while (p != NULL) {
        if (x == p->data)
            return p;
        else if (x < p->data)
            p = p->left;
        else
            p = p->right;
    }

    return NULL;
}

bool hasLeft(BinaryTree t, int x) {
    Node* p = SearchNode(t, x);
    return p != NULL && p->left != NULL;
}

bool hasRight(BinaryTree t, int x) {
    Node* p = SearchNode(t, x);
    return p != NULL && p->right != NULL;
}

BinaryTree Left(BinaryTree t, int x) {
    Node* p = SearchNode(t, x);

    if (p == NULL || p->left == NULL)
        return NULL;

    BinaryTree sub = new BinaryTreeADT;
    sub->root = p->left;
    return sub;
}

BinaryTree Right(BinaryTree t, int x) {
    Node* p = SearchNode(t, x);

    if (p == NULL || p->right == NULL)
        return NULL;

    BinaryTree sub = new BinaryTreeADT;
    sub->root = p->right;
    return sub;
}

int main() {
    char filename[] = "input_bai2.txt";
    BinaryTree t = createTree(filename);

    cout << "Level-order: ";
    TraversalLevel(t);

    int x;
    cout << "\nNhap x can tim: ";
    cin >> x;

    Node* p = SearchNode(t, x);
    if (p != NULL)
        cout << "Tim thay node " << x;
    else
        cout << "Khong tim thay node " << x;

    cout << "\nCo con trai khong? " << (hasLeft(t, x) ? "Co" : "Khong");
    cout << "\nCo con phai khong? " << (hasRight(t, x) ? "Co" : "Khong");

    BinaryTree leftTree = Left(t, x);
    if (leftTree != NULL) {
        cout << "\nCay con trai cua " << x << ": ";
        TraversalLevel(leftTree);
    }

    BinaryTree rightTree = Right(t, x);
    if (rightTree != NULL) {
        cout << "\nCay con phai cua " << x << ": ";
        TraversalLevel(rightTree);
    }

    return 0;
}
