// Tuan 4 - Bai 6: Lop Geometry co phuong thuc ao tinh dien tich
// TamGiac  ke thua Geometry
// TuGiac   ke thua Geometry
// HinhChuNhat ke thua TuGiac
// HinhTron ke thua TuGiac (theo de bai)
// Tao tam giac, hinh chu nhat, hinh vuong va in dien tich
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

class Geometry {
public:
  virtual double tinhDienTich() = 0;  // phuong thuc ao thuan tuy
  virtual void xuat() {
    cout << "Dien tich = " << fixed << setprecision(2) << tinhDienTich()
         << endl;
  }
  virtual ~Geometry() {}
};

class TamGiac : public Geometry {
private:
  double a, b, c;

public:
  // Phuong thuc thiet lap: nhap 3 canh
  TamGiac(double a = 0, double b = 0, double c = 0) {
    this->a = a;
    this->b = b;
    this->c = c;
  }
  double tinhDienTich() override {
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
  }
  void xuat() override {
    cout << "Tam giac (3 canh " << a << ", " << b << ", " << c << ") ";
    Geometry::xuat();
  }
};

// Lop tu giac ke thua Geometry (chua cai dat tinh dien tich -> van truu tuong)
class TuGiac : public Geometry {};

class HinhChuNhat : public TuGiac {
protected:
  double dai, rong;

public:
  // Phuong thuc thiet lap: nhap chieu dai, chieu rong
  HinhChuNhat(double dai = 0, double rong = 0) {
    this->dai = dai;
    this->rong = rong;
  }
  double tinhDienTich() override { return dai * rong; }
  void xuat() override {
    cout << "Hinh chu nhat (" << dai << " x " << rong << ") ";
    Geometry::xuat();
  }
};

// Hinh vuong: truong hop dac biet cua hinh chu nhat
class HinhVuong : public HinhChuNhat {
public:
  HinhVuong(double canh = 0) : HinhChuNhat(canh, canh) {}
  void xuat() override {
    cout << "Hinh vuong (canh " << dai << ") ";
    Geometry::xuat();
  }
};

int main() {
  TamGiac tg(3, 4, 5);
  HinhChuNhat hcn(4, 6);
  HinhVuong hv(5);

  // Dung con tro lop cha goi phuong thuc ao (tinh da hinh)
  Geometry *ds[3] = {&tg, &hcn, &hv};

  cout << "===== DIEN TICH CAC HINH =====\n";
  for (int i = 0; i < 3; i++)
    ds[i]->xuat();

  return 0;
}
