// De 3 - Cau 1: Lop hinh hoc co phuong thuc ao tinh dien tich
// Lop tam giac ke thua, nhap 3 canh va cai dat lai tinh dien tich
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

class HinhHoc {
public:
  virtual double tinhDienTich() = 0;  // phuong thuc ao
  virtual ~HinhHoc() {}
};

class TamGiac : public HinhHoc {
private:
  double a, b, c;

public:
  void nhap() {
    cout << "Nhap 3 canh tam giac (a b c): ";
    cin >> a >> b >> c;
  }

  // Cong thuc Heron
  double tinhDienTich() override {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
  }
};

int main() {
  TamGiac tg;
  tg.nhap();

  cout << fixed << setprecision(2);
  cout << "Dien tich tam giac = " << tg.tinhDienTich() << endl;

  return 0;
}
