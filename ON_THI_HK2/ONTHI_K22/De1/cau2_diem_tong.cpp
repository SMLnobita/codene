// De 1 - Cau 2: Lop diem tren he toa do 2 chieu
// Tinh tong 2 diem: A + B = (xA + xB, yA + yB)
#include <iostream>

using namespace std;

class Diem {
private:
  double x, y;

public:
  Diem(double x = 0, double y = 0) {
    this->x = x;
    this->y = y;
  }

  void nhap() {
    cout << "Nhap x: ";
    cin >> x;
    cout << "Nhap y: ";
    cin >> y;
  }

  // A + B = (xA + xB, yA + yB)
  Diem operator+(const Diem &B) const { return Diem(x + B.x, y + B.y); }

  void xuat() const { cout << "(" << x << ", " << y << ")"; }
};

int main() {
  Diem A(2, 3), B(4, 1);

  cout << "A = ";
  A.xuat();
  cout << "\nB = ";
  B.xuat();

  Diem C = A + B;
  cout << "\nA + B = ";
  C.xuat();
  cout << endl;

  return 0;
}
