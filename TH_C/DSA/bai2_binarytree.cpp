#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

struct Node {
  int data;
  Node *left;
  Node *right;
};

typedef struct BinaryTreeADT *BinaryTree;

struct BinaryTreeADT {
  Node *root;
};

Node *createNode(int x) {
  Node *p = new Node;
  p->data = x;
  p->left = NULL;
  p->right = NULL;
  return p;
}

void insertNode(Node *&root, int x) {
  if (root == NULL) {
    root = createNode(x);
    return;
  }

  if (x < root->data)
    insertNode(root->left, x);
  else if (x > root->data)
    insertNode(root->right, x);
}

BinaryTree createTree(char *filename) {
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

Node *SearchNode(BinaryTree t, int x) {
  if (t == NULL)
    return NULL;

  Node *p = t->root;

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

BinaryTree Left(BinaryTree t, int x) {
  Node *p = SearchNode(t, x);

  if (p == NULL || p->left == NULL)
    return NULL;

  BinaryTree sub = new BinaryTreeADT;
  sub->root = p->left;
  return sub;
}

int main() {
  char filename[] = "input_bai2.txt";
  BinaryTree t = createTree(filename);

  int x;
  cout << "\nNhap x can tim: ";
  cin >> x;
  Node *p = SearchNode(t, x);

  if (p != NULL)
    cout << "Tim thay node " << x;
  else
    cout << "Khong tim thay node " << x;

  BinaryTree leftTree = Left(t, x);

  if (leftTree != NULL) {
    cout << "Node goc cua cay con trai cua " << x << " la: ";
    cout << leftTree->root->data << endl;
  } else {
    cout << "Node " << x << " khong co cay con trai" << endl;
  }

  return 0;
}
