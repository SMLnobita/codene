// Tuan 5 - Bai 9: Tinh luong cho 3 loai nhan vien
// Lop cha "Nguoi" co phuong thuc ao tinh luong.
//   NV san xuat : luong = luong can ban + so san pham * 15000
//   NV van phong: luong = so ngay lam viec * 100000
//   Quan ly     : luong = so ngay lam viec * 100000 + 200000 * he so phu cap
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Nguoi {
protected:
  string hoTen;
  string ngaySinh;
  double luong;

public:
  Nguoi(string ht = "", string ns = "") {
    hoTen = ht;
    ngaySinh = ns;
    luong = 0;
  }
  virtual double tinhLuong() = 0;  // phuong thuc ao
  void xuat() {
    cout << left << setw(20) << hoTen << setw(14) << ngaySinh << right
         << setw(14) << fixed << setprecision(0) << tinhLuong() << endl;
  }
  virtual ~Nguoi() {}
};

class NhanVienSanXuat : public Nguoi {
private:
  double luongCanBan;
  int soSanPham;

public:
  NhanVienSanXuat(string ht, string ns, double lcb, int sp)
      : Nguoi(ht, ns) {
    luongCanBan = lcb;
    soSanPham = sp;
  }
  double tinhLuong() override { return luongCanBan + soSanPham * 15000.0; }
};

class NhanVienVanPhong : public Nguoi {
private:
  int soNgayLamViec;

public:
  NhanVienVanPhong(string ht, string ns, int ngay) : Nguoi(ht, ns) {
    soNgayLamViec = ngay;
  }
  double tinhLuong() override { return soNgayLamViec * 100000.0; }
};

class QuanLy : public Nguoi {
private:
  int soNgayLamViec;
  double heSoPhuCap;

public:
  QuanLy(string ht, string ns, int ngay, double hs) : Nguoi(ht, ns) {
    soNgayLamViec = ngay;
    heSoPhuCap = hs;
  }
  double tinhLuong() override {
    return soNgayLamViec * 100000.0 + 200000.0 * heSoPhuCap;
  }
};

int main() {
  NhanVienSanXuat sx("Nguyen Van A", "01/01/1990", 4000000, 120);
  NhanVienVanPhong vp("Tran Thi B", "05/05/1992", 26);
  QuanLy ql("Le Van C", "10/10/1985", 26, 2.5);

  Nguoi *congTy[3] = {&sx, &vp, &ql};

  cout << left << setw(20) << "Ho ten" << setw(14) << "Ngay sinh" << right
       << setw(14) << "Luong" << endl;
  for (int i = 0; i < 3; i++)
    congTy[i]->xuat();

  return 0;
}
