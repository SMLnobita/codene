// De 4 - Cau 1: Lop diem he toa do (x, y, z)
// Toan tu == kiem tra 2 diem co trung nhau khong
#include <iostream>

using namespace std;

class Diem3D {
private:
  double x, y, z;

public:
  Diem3D(double x = 0, double y = 0, double z = 0) {
    this->x = x;
    this->y = y;
    this->z = z;
  }

  void nhap() {
    cout << "Nhap x y z: ";
    cin >> x >> y >> z;
  }

  void xuat() const { cout << "(" << x << ", " << y << ", " << z << ")"; }

  // 2 diem trung nhau khi co cung x, y, z
  bool operator==(const Diem3D &b) const {
    return x == b.x && y == b.y && z == b.z;
  }
};

int main() {
  Diem3D A(1, 2, 3), B(1, 2, 3), C(4, 5, 6);

  cout << "A = "; A.xuat(); cout << endl;
  cout << "B = "; B.xuat(); cout << endl;
  cout << "C = "; C.xuat(); cout << endl;

  cout << "\nA == B ? " << (A == B ? "Trung nhau" : "Khac nhau") << endl;
  cout << "A == C ? " << (A == C ? "Trung nhau" : "Khac nhau") << endl;

  return 0;
}
