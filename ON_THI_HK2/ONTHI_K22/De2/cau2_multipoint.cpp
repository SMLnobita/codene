// De 2 - Cau 2: Lop MultiPoint quan ly mang n cac Point
// - Calculate: khoang cach Point toi goc toa do (0,0)
// - Toan tu > so sanh 2 Point (theo khoang cach toi goc)
// - Display: hien thi toa do cac Point
// - Insert: them mot Point vao cuoi danh sach
// - Destructor: huy bo cac Point
#include <cmath>
#include <iostream>

using namespace std;

class Point {
private:
  double x, y;

public:
  Point(double x = 0, double y = 0) {
    this->x = x;
    this->y = y;
  }

  // Khoang cach toi goc toa do (0,0)
  double Calculate() const { return sqrt(x * x + y * y); }

  // So sanh 2 Point: Point nao xa goc hon thi lon hon
  bool operator>(const Point &b) const { return Calculate() > b.Calculate(); }

  void Display() const {
    cout << "(" << x << ", " << y << ") - khoang cach toi goc = " << Calculate()
         << endl;
  }
};

class MultiPoint {
private:
  Point *ds;   // mang dong cac Point
  int n;       // so luong hien tai
  int dungLuong;

public:
  MultiPoint() {
    n = 0;
    dungLuong = 4;
    ds = new Point[dungLuong];
  }

  // Them mot Point vao cuoi danh sach
  void Insert(const Point &p) {
    if (n == dungLuong) {
      dungLuong *= 2;
      Point *moi = new Point[dungLuong];
      for (int i = 0; i < n; i++) moi[i] = ds[i];
      delete[] ds;
      ds = moi;
    }
    ds[n++] = p;
  }

  void Display() const {
    cout << "Danh sach " << n << " Point:\n";
    for (int i = 0; i < n; i++) {
      cout << "  ";
      ds[i].Display();
    }
  }

  // Tim Point xa goc nhat (vi du su dung toan tu >)
  void PointLonNhat() const {
    if (n == 0) return;
    Point max = ds[0];
    for (int i = 1; i < n; i++)
      if (ds[i] > max) max = ds[i];
    cout << "Point xa goc toa do nhat: ";
    max.Display();
  }

  // Huy bo cac Point trong lop
  ~MultiPoint() {
    delete[] ds;
    cout << "Da huy bo MultiPoint\n";
  }
};

int main() {
  MultiPoint mp;
  mp.Insert(Point(1, 2));
  mp.Insert(Point(3, 4));
  mp.Insert(Point(0, 1));
  mp.Insert(Point(5, 5));

  mp.Display();
  cout << endl;
  mp.PointLonNhat();
  cout << endl;

  return 0;
}
