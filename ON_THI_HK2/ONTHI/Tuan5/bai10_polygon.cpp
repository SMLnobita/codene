// Tuan 5 - Bai 10: Multipoint, Polyline, Polygon
// - Multipoint: tap cac diem {x,y}, them/xoa diem, hien thi
// - Polyline  : tap cac diem {x,y}, hien thi
// - Chuyen kieu Multipoint -> Polyline
// - Polygon   : tap diem voi dieu kien diem dau trung diem cuoi
// - Chuyen kieu Multipoint -> Polygon
#include <iostream>

using namespace std;

struct Diem {
  double x, y;
};

const int MAX = 100;

// Khai bao truoc de dung trong toan tu chuyen kieu cua Multipoint
class Polyline;
class Polygon;

class Multipoint {
private:
  Diem ds[MAX];
  int n;

public:
  Multipoint() { n = 0; }
  Multipoint(Diem a[], int soDiem) {
    n = soDiem;
    for (int i = 0; i < n; i++) ds[i] = a[i];
  }

  int soDiem() const { return n; }
  Diem layDiem(int i) const { return ds[i]; }

  // Them mot diem
  void themDiem(double x, double y) {
    if (n < MAX) {
      ds[n].x = x;
      ds[n].y = y;
      n++;
    }
  }

  // Xoa diem tai vi tri idx
  void xoaDiem(int idx) {
    if (idx < 0 || idx >= n) return;
    for (int i = idx; i < n - 1; i++) ds[i] = ds[i + 1];
    n--;
  }

  void hienThi() const {
    cout << "Multipoint: ";
    for (int i = 0; i < n; i++)
      cout << "{" << ds[i].x << "," << ds[i].y << "} ";
    cout << endl;
  }

  // Chuyen kieu Multipoint -> Polyline va -> Polygon (dinh nghia sau)
  operator Polyline() const;
  operator Polygon() const;
};

class Polyline {
private:
  Diem ds[MAX];
  int n;

public:
  Polyline() { n = 0; }
  Polyline(Diem a[], int soDiem) {
    n = soDiem;
    for (int i = 0; i < n; i++) ds[i] = a[i];
  }
  void hienThi() const {
    cout << "Polyline: ";
    for (int i = 0; i < n; i++)
      cout << "{" << ds[i].x << "," << ds[i].y << "} ";
    cout << endl;
  }
};

class Polygon {
private:
  Diem ds[MAX];
  int n;

public:
  Polygon() { n = 0; }
  // Dieu kien: diem dau trung diem cuoi. Neu chua trung thi tu them diem dau vao cuoi.
  Polygon(Diem a[], int soDiem) {
    n = soDiem;
    for (int i = 0; i < n; i++) ds[i] = a[i];
    if (n > 0 && (ds[0].x != ds[n - 1].x || ds[0].y != ds[n - 1].y)) {
      ds[n] = ds[0];
      n++;
    }
  }
  void hienThi() const {
    cout << "Polygon: ";
    for (int i = 0; i < n; i++)
      cout << "{" << ds[i].x << "," << ds[i].y << "} ";
    cout << endl;
  }
};

// Dinh nghia cac toan tu chuyen kieu cua Multipoint (sau khi co dinh nghia day du)
Multipoint::operator Polyline() const { return Polyline((Diem *)ds, n); }
Multipoint::operator Polygon() const { return Polygon((Diem *)ds, n); }

int main() {
  Diem a[] = {{0, 0}, {2, 0}, {2, 2}, {0, 2}};
  Multipoint mp(a, 4);
  mp.hienThi();

  mp.themDiem(5, 5);
  cout << "Sau khi them diem (5,5):\n";
  mp.hienThi();

  mp.xoaDiem(0);
  cout << "Sau khi xoa diem dau:\n";
  mp.hienThi();

  // Chuyen kieu
  Polyline pl = mp;
  cout << "\nChuyen Multipoint -> Polyline:\n";
  pl.hienThi();

  Polygon pg = mp;
  cout << "\nChuyen Multipoint -> Polygon (tu dong dong kin):\n";
  pg.hienThi();

  return 0;
}
