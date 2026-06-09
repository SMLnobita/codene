// De 2 - Cau 1: Lop Point co toa do x, y
// - Phuong thuc Display hien thi toa do
// - Phuong thuc huy bo (destructor)
#include <iostream>

using namespace std;

class Point {
private:
  double x, y;

public:
  Point(double x = 0, double y = 0) {
    this->x = x;
    this->y = y;
  }

  void Display() const { cout << "(" << x << ", " << y << ")" << endl; }

  // Phuong thuc huy bo
  ~Point() { cout << "Huy bo Point (" << x << ", " << y << ")\n"; }
};

int main() {
  Point p(3, 5);
  cout << "Toa do diem: ";
  p.Display();

  // Khi ra khoi main, destructor tu dong duoc goi
  return 0;
}
