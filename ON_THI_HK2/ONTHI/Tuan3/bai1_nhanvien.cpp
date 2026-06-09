// Tuan 3 - Bai 1: Lop nhan vien
// Thuoc tinh: Ten, nam sinh, dia chi, so dien thoai, email,
//             ngay vao lam, he so luong, so ngay nghi
// Phuong thuc: tang he so luong, doi so dien thoai, xin nghi phep
// Quan ly cong ty co 10 nhan vien, in ten/nam sinh/dia chi
#include <iostream>
#include <string>

using namespace std;

class NhanVien {
private:
  string ten;
  int namSinh;
  string diaChi;
  string soDienThoai;
  string email;
  string ngayVaoLam;
  double heSoLuong;
  int soNgayNghi;

public:
  void nhap();
  void xuatTomTat();  // ten, nam sinh, dia chi

  void tangHeSoLuong(double them) { heSoLuong += them; }
  void doiSoDienThoai(string sdtMoi) { soDienThoai = sdtMoi; }
  void xinNghiPhep(int soNgay) { soNgayNghi += soNgay; }
};

void NhanVien::nhap() {
  cout << "Ho ten: ";
  getline(cin, ten);
  cout << "Nam sinh: ";
  cin >> namSinh;
  cin.ignore();
  cout << "Dia chi: ";
  getline(cin, diaChi);
  cout << "So dien thoai: ";
  getline(cin, soDienThoai);
  cout << "Email: ";
  getline(cin, email);
  cout << "Ngay vao lam: ";
  getline(cin, ngayVaoLam);
  cout << "He so luong: ";
  cin >> heSoLuong;
  cout << "So ngay nghi: ";
  cin >> soNgayNghi;
  cin.ignore();
}

void NhanVien::xuatTomTat() {
  cout << ten << "\t" << namSinh << "\t" << diaChi << endl;
}

int main() {
  const int SO_NV = 10;
  NhanVien congTy[SO_NV];

  for (int i = 0; i < SO_NV; i++) {
    cout << "--- Nhap thong tin nhan vien thu " << i + 1 << " ---\n";
    congTy[i].nhap();
    cout << endl;
  }

  cout << "\n===== DANH SACH NHAN VIEN =====\n";
  cout << "Ho ten\tNam sinh\tDia chi\n";
  for (int i = 0; i < SO_NV; i++)
    congTy[i].xuatTomTat();

  return 0;
}
