// De 4 - Cau 2: Lop phan so (tu so, mau so)
// Phuong thuc: cong, tru, nhan, chia, nhap, xuat
#include <iostream>

using namespace std;

int ucln(int a, int b) {
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  while (b != 0) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

class PhanSo {
private:
  int tuSo, mauSo;

public:
  PhanSo(int t = 0, int m = 1) {
    tuSo = t;
    mauSo = (m == 0) ? 1 : m;
  }

  void rutGon() {
    if (mauSo < 0) {
      tuSo = -tuSo;
      mauSo = -mauSo;
    }
    int u = ucln(tuSo, mauSo);
    if (u != 0) {
      tuSo /= u;
      mauSo /= u;
    }
  }

  void nhap() {
    cout << "Nhap tu so: ";
    cin >> tuSo;
    cout << "Nhap mau so: ";
    cin >> mauSo;
    if (mauSo == 0) mauSo = 1;
    rutGon();
  }

  void xuat() const { cout << tuSo << "/" << mauSo; }

  PhanSo cong(PhanSo b) {
    PhanSo kq(tuSo * b.mauSo + b.tuSo * mauSo, mauSo * b.mauSo);
    kq.rutGon();
    return kq;
  }
  PhanSo tru(PhanSo b) {
    PhanSo kq(tuSo * b.mauSo - b.tuSo * mauSo, mauSo * b.mauSo);
    kq.rutGon();
    return kq;
  }
  PhanSo nhan(PhanSo b) {
    PhanSo kq(tuSo * b.tuSo, mauSo * b.mauSo);
    kq.rutGon();
    return kq;
  }
  PhanSo chia(PhanSo b) {
    PhanSo kq(tuSo * b.mauSo, mauSo * b.tuSo);
    kq.rutGon();
    return kq;
  }
};

int main() {
  PhanSo a, b, kq;

  cout << "--- Nhap phan so thu nhat ---\n";
  a.nhap();
  cout << "--- Nhap phan so thu hai ---\n";
  b.nhap();

  cout << "\nTong   = "; kq = a.cong(b); kq.xuat(); cout << endl;
  cout << "Hieu   = "; kq = a.tru(b);  kq.xuat(); cout << endl;
  cout << "Tich   = "; kq = a.nhan(b); kq.xuat(); cout << endl;
  cout << "Thuong = "; kq = a.chia(b); kq.xuat(); cout << endl;

  return 0;
}
