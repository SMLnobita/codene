// Tuan 4 - Bai 7: Lop phuong tien co phuong thuc ao chuyen dong
// Thuoc tinh: mau sac, kich thuoc dai, rong, so banh xe
// XeMay, XeHoi, XeDap ke thua tu PhuongTien
#include <iostream>
#include <string>

using namespace std;

class PhuongTien {
protected:
  string mauSac;
  double dai, rong;
  int soBanhXe;

public:
  PhuongTien(string mau = "", double d = 0, double r = 0, int banh = 0) {
    mauSac = mau;
    dai = d;
    rong = r;
    soBanhXe = banh;
  }
  virtual void chuyenDong() = 0;  // phuong thuc ao
  void xuatThongTin() {
    cout << "Mau: " << mauSac << ", kich thuoc: " << dai << "x" << rong
         << ", so banh xe: " << soBanhXe << endl;
  }
  virtual ~PhuongTien() {}
};

class XeMay : public PhuongTien {
public:
  XeMay(string mau = "", double d = 0, double r = 0) : PhuongTien(mau, d, r, 2) {}
  void chuyenDong() override { cout << "Xe may chuyen dong bang 2 banh\n"; }
};

class XeHoi : public PhuongTien {
public:
  XeHoi(string mau = "", double d = 0, double r = 0) : PhuongTien(mau, d, r, 4) {}
  void chuyenDong() override { cout << "Xe hoi chuyen dong bang 4 banh\n"; }
};

class XeDap : public PhuongTien {
public:
  XeDap(string mau = "", double d = 0, double r = 0) : PhuongTien(mau, d, r, 2) {}
  void chuyenDong() override { cout << "Xe dap chuyen dong bang 2 banh\n"; }
};

int main() {
  XeMay xm("Do", 2.0, 0.7);
  XeHoi xh("Den", 4.5, 1.8);
  XeDap xd("Xanh", 1.8, 0.6);

  PhuongTien *ds[3] = {&xm, &xh, &xd};
  for (int i = 0; i < 3; i++) {
    ds[i]->xuatThongTin();
    ds[i]->chuyenDong();
    cout << endl;
  }

  return 0;
}
