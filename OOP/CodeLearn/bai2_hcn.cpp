#include <iostream>
using namespace std;

class hinhChuNhat {
public:
  double chieudai;
  double chieurong;
  void layGiaTri() {
    cin >> chieudai;
    cin >> chieurong;
  }
  double getArea() { return chieudai * chieurong; }
  double getPerimeter() { return (chieudai + chieurong) * 2; }
  void inMangHinh() {
    cout << "Area = " << getArea() << endl;
    cout << "Perimeter = " << getPerimeter() << endl;
  }
};

int main() {
  hinhChuNhat hcn;
  hcn.layGiaTri();
  hcn.inMangHinh();
  return 0;
}