// De 7: Quan ly thu cung (Animal -> Cho, Meo) trong NgoiNha
// Animal: ten, tuoi, can nang; constructor, Nhap, Xuat, TinhTien()
//   Cho: + chieu cao, chieu dai; tien an = can nang * 0.05
//   Meo: + loai meo;            tien an = (can nang - 1) * 0.04
// NgoiNha: nhap cho, nhap meo, xuat danh sach, tinh tong tien an
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Animal {
protected:
  string ten;
  int tuoi;
  double canNang;

public:
  Animal() {
    ten = "";
    tuoi = 0;
    canNang = 0;
  }
  Animal(string ten, int tuoi, double canNang) {
    this->ten = ten;
    this->tuoi = tuoi;
    this->canNang = canNang;
  }
  virtual ~Animal() {}

  virtual void Nhap() {
    cout << "Ten: ";
    getline(cin, ten);
    cout << "Tuoi: ";
    cin >> tuoi;
    cout << "Can nang (kg): ";
    cin >> canNang;
    cin.ignore();
  }

  virtual void Xuat() {
    cout << "Ten: " << ten << ", Tuoi: " << tuoi
         << ", Can nang: " << canNang << " kg";
  }

  virtual double TinhTien() = 0;  // phuong thuc ao tinh tien an
};

class Cho : public Animal {
private:
  double chieuCao;  // cm
  double chieuDai;  // cm

public:
  Cho() : Animal() {
    chieuCao = 0;
    chieuDai = 0;
  }
  Cho(string ten, int tuoi, double canNang, double cao, double dai)
      : Animal(ten, tuoi, canNang) {
    chieuCao = cao;
    chieuDai = dai;
  }

  void Nhap() override {
    Animal::Nhap();
    cout << "Chieu cao (cm): ";
    cin >> chieuCao;
    cout << "Chieu dai (cm): ";
    cin >> chieuDai;
    cin.ignore();
  }

  void Xuat() override {
    cout << "[Cho] ";
    Animal::Xuat();
    cout << ", Cao: " << chieuCao << " cm, Dai: " << chieuDai << " cm";
    cout << ", Tien an/ngay: " << TinhTien();
  }

  double TinhTien() override { return canNang * 0.05; }
};

class Meo : public Animal {
private:
  string loaiMeo;

public:
  Meo() : Animal() { loaiMeo = ""; }
  Meo(string ten, int tuoi, double canNang, string loai)
      : Animal(ten, tuoi, canNang) {
    loaiMeo = loai;
  }

  void Nhap() override {
    Animal::Nhap();
    cout << "Loai meo: ";
    getline(cin, loaiMeo);
  }

  void Xuat() override {
    cout << "[Meo] ";
    Animal::Xuat();
    cout << ", Loai: " << loaiMeo;
    cout << ", Tien an/ngay: " << TinhTien();
  }

  double TinhTien() override { return (canNang - 1) * 0.04; }
};

class NgoiNha {
private:
  Animal *ds[100];
  int n;

public:
  NgoiNha() { n = 0; }
  ~NgoiNha() {
    for (int i = 0; i < n; i++) delete ds[i];
  }

  void nhapCho() {
    Cho *c = new Cho();
    c->Nhap();
    ds[n++] = c;
  }

  void nhapMeo() {
    Meo *m = new Meo();
    m->Nhap();
    ds[n++] = m;
  }

  // Them san doi tuong (dung cho demo khong nhap ban phim)
  void them(Animal *a) { ds[n++] = a; }

  void xuatDanhSach() {
    cout << "===== DANH SACH THU CUNG TRONG NHA =====\n";
    for (int i = 0; i < n; i++) {
      cout << i + 1 << ". ";
      ds[i]->Xuat();
      cout << endl;
    }
  }

  double tongTienAn() {
    double tong = 0;
    for (int i = 0; i < n; i++) tong += ds[i]->TinhTien();
    return tong;
  }
};

int main() {
  NgoiNha nha;

  // Dung du lieu mau de in ket qua ngay (co the thay bang nha.nhapCho()/nhapMeo())
  nha.them(new Cho("Lucky", 3, 12, 45, 70));
  nha.them(new Meo("Kitty", 2, 4, "Meo Anh"));
  nha.them(new Cho("Max", 5, 20, 55, 90));

  nha.xuatDanhSach();
  cout << fixed << setprecision(2);
  cout << "\nTong tien an cua ca nha/ngay: " << nha.tongTienAn() << endl;

  return 0;
}
