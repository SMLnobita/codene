// Tuan 3 - Bai 4: Lop hang hoa
// Thuoc tinh: ten hang, ma hang, nhan hieu, gia ban, gia mua, so luong
// Co constructor (phuong thuc thiet lap) khoi tao gia tri ban dau
// Phuong thuc: nhap hang, ban hang, tang gia, giam gia
// Quan ly cac mat hang: dau an, bia, nuoc ngot. In danh sach.
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class HangHoa {
private:
  string tenHang;
  string maHang;
  string nhanHieu;
  double giaBan;
  double giaMua;
  int soLuong;

public:
  // Phuong thuc thiet lap khoi tao gia tri ban dau
  HangHoa(string ten = "", string ma = "", string nhan = "", double gBan = 0,
          double gMua = 0, int sl = 0) {
    tenHang = ten;
    maHang = ma;
    nhanHieu = nhan;
    giaBan = gBan;
    giaMua = gMua;
    soLuong = sl;
  }

  void nhapHang(int sl) { soLuong += sl; }

  void banHang(int sl) {
    if (sl <= soLuong)
      soLuong -= sl;
    else
      cout << "Khong du hang de ban!\n";
  }

  void tangGia(double phanTram) { giaBan += giaBan * phanTram / 100; }
  void giamGia(double phanTram) { giaBan -= giaBan * phanTram / 100; }

  void xuat() const {
    cout << left << setw(12) << maHang << setw(14) << tenHang << setw(12)
         << nhanHieu << right << setw(10) << giaMua << setw(10) << giaBan
         << setw(10) << soLuong << endl;
  }

  static void inTieuDe() {
    cout << left << setw(12) << "Ma hang" << setw(14) << "Ten hang" << setw(12)
         << "Nhan hieu" << right << setw(10) << "Gia mua" << setw(10)
         << "Gia ban" << setw(10) << "So luong" << endl;
  }
};

int main() {
  HangHoa dauAn("Dau an", "DA01", "Neptune", 35000, 50000, 100);
  HangHoa bia("Bia", "B01", "Tiger", 12000, 18000, 200);
  HangHoa nuocNgot("Nuoc ngot", "NN01", "Coca", 8000, 12000, 300);

  // Mot vai thao tac mau
  dauAn.banHang(20);
  bia.nhapHang(50);
  nuocNgot.tangGia(10);

  cout << "===== DANH SACH MAT HANG =====\n";
  HangHoa::inTieuDe();
  dauAn.xuat();
  bia.xuat();
  nuocNgot.xuat();

  return 0;
}
