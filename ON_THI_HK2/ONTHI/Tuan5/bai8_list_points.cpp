// Tuan 5 - Bai 8: Lop list_points - danh sach lien ket cac doi tuong point
// Phuong thuc: duyet, them vao dau, them vao vi tri hien tai,
//              xoa mot phan tu, xoa toan bo danh sach
#include <iostream>

using namespace std;

class point {
private:
  int x, y;

public:
  point(int ox = 0, int oy = 0) {
    x = ox;
    y = oy;
  }
  void display() const { cout << "(" << x << ", " << y << ")"; }
};

// Mot nut trong danh sach lien ket
struct Node {
  point p;
  Node *next;
  Node(point pt) : p(pt), next(nullptr) {}
};

class list_points {
private:
  Node *dau;     // dau danh sach
  Node *current; // vi tri hien tai

public:
  list_points() {
    dau = nullptr;
    current = nullptr;
  }
  ~list_points() { xoaTatCa(); }

  // Duyet danh sach
  void duyet() const {
    if (dau == nullptr) {
      cout << "Danh sach rong\n";
      return;
    }
    Node *t = dau;
    while (t != nullptr) {
      t->p.display();
      if (t->next != nullptr) cout << " -> ";
      t = t->next;
    }
    cout << endl;
  }

  // Them 1 phan tu vao dau danh sach
  void themDau(point p) {
    Node *moi = new Node(p);
    moi->next = dau;
    dau = moi;
    current = moi;
  }

  // Them phan tu vao sau vi tri hien tai (current)
  void themSauHienTai(point p) {
    if (current == nullptr) {
      themDau(p);
      return;
    }
    Node *moi = new Node(p);
    moi->next = current->next;
    current->next = moi;
    current = moi;
  }

  // Xoa mot phan tu (phan tu dau tien co toa do trung voi p tham chieu vi tri)
  // O day xoa phan tu dau danh sach lam vi du don gian
  void xoaDau() {
    if (dau == nullptr) return;
    Node *t = dau;
    dau = dau->next;
    if (current == t) current = dau;
    delete t;
  }

  // Xoa toan bo danh sach
  void xoaTatCa() {
    while (dau != nullptr) {
      Node *t = dau;
      dau = dau->next;
      delete t;
    }
    current = nullptr;
  }
};

int main() {
  list_points ds;

  ds.themDau(point(1, 1));
  ds.themDau(point(2, 2));
  ds.themDau(point(3, 3));
  cout << "Sau khi them 3 phan tu vao dau:\n";
  ds.duyet();

  ds.themSauHienTai(point(9, 9));
  cout << "Sau khi them (9,9) sau vi tri hien tai:\n";
  ds.duyet();

  ds.xoaDau();
  cout << "Sau khi xoa phan tu dau:\n";
  ds.duyet();

  ds.xoaTatCa();
  cout << "Sau khi xoa toan bo:\n";
  ds.duyet();

  return 0;
}
