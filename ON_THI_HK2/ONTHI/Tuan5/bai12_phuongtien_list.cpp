// Tuan 5 - Bai 12: PhuongTienGiaoThong va lop List quan ly danh sach moc noi
// PhuongTienGiaoThong: hang san xuat, ten phuong tien, nam san xuat, van toc toi da
// Oto ke thua PhuongTienGiaoThong, them: so cho ngoi, kieu dong co
// Co constructor (thiet lap), destructor (huy bo), nhap, xuat
// Lop List: danh sach moc noi cac PhuongTienGiaoThong
#include <iostream>
#include <string>

using namespace std;

class PhuongTienGiaoThong {
protected:
  string hangSanXuat;
  string tenPhuongTien;
  int namSanXuat;
  double vanTocToiDa;

public:
  PhuongTienGiaoThong(string hang = "", string ten = "", int nam = 0,
                      double vt = 0) {
    hangSanXuat = hang;
    tenPhuongTien = ten;
    namSanXuat = nam;
    vanTocToiDa = vt;
  }
  virtual ~PhuongTienGiaoThong() {}

  virtual void nhap() {
    cout << "Hang san xuat: ";
    getline(cin, hangSanXuat);
    cout << "Ten phuong tien: ";
    getline(cin, tenPhuongTien);
    cout << "Nam san xuat: ";
    cin >> namSanXuat;
    cout << "Van toc toi da: ";
    cin >> vanTocToiDa;
    cin.ignore();
  }

  virtual void xuat() {
    cout << "Hang: " << hangSanXuat << ", Ten: " << tenPhuongTien
         << ", Nam SX: " << namSanXuat << ", Van toc toi da: " << vanTocToiDa
         << " km/h";
  }
};

class Oto : public PhuongTienGiaoThong {
private:
  int soChoNgoi;
  string kieuDongCo;

public:
  Oto(string hang = "", string ten = "", int nam = 0, double vt = 0,
      int cho = 0, string dongCo = "")
      : PhuongTienGiaoThong(hang, ten, nam, vt) {
    soChoNgoi = cho;
    kieuDongCo = dongCo;
  }
  ~Oto() {}

  void nhap() override {
    PhuongTienGiaoThong::nhap();
    cout << "So cho ngoi: ";
    cin >> soChoNgoi;
    cin.ignore();
    cout << "Kieu dong co: ";
    getline(cin, kieuDongCo);
  }

  void xuat() override {
    PhuongTienGiaoThong::xuat();
    cout << ", So cho: " << soChoNgoi << ", Dong co: " << kieuDongCo;
  }
};

// Nut cua danh sach moc noi
struct Node {
  PhuongTienGiaoThong *pt;
  Node *next;
  Node(PhuongTienGiaoThong *p) : pt(p), next(nullptr) {}
};

class List {
private:
  Node *dau;

public:
  List() { dau = nullptr; }
  ~List() {
    while (dau != nullptr) {
      Node *t = dau;
      dau = dau->next;
      delete t->pt;  // huy doi tuong phuong tien
      delete t;
    }
  }

  // Them vao cuoi danh sach
  void them(PhuongTienGiaoThong *p) {
    Node *moi = new Node(p);
    if (dau == nullptr) {
      dau = moi;
      return;
    }
    Node *t = dau;
    while (t->next != nullptr) t = t->next;
    t->next = moi;
  }

  void xuatTatCa() {
    Node *t = dau;
    int i = 1;
    while (t != nullptr) {
      cout << i++ << ". ";
      t->pt->xuat();
      cout << endl;
      t = t->next;
    }
  }
};

int main() {
  List ds;

  // Tao san mot vai phuong tien (co the doi sang nhap() neu can)
  ds.them(new Oto("Toyota", "Vios", 2022, 180, 5, "Xang"));
  ds.them(new Oto("Honda", "CRV", 2023, 200, 7, "Xang"));
  ds.them(new PhuongTienGiaoThong("Yamaha", "Exciter", 2021, 120));

  cout << "===== DANH SACH PHUONG TIEN GIAO THONG =====\n";
  ds.xuatTatCa();

  return 0;
}
