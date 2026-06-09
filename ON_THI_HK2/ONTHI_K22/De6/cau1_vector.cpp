// De 6 - Cau 1: Lop vector co 3 ham thiet lap
// - Ham thiet lap khong tham so: nhap kich thuoc n va cac toa do
// - Ham thiet lap 1 tham so: tham so la kich thuoc vector
// - Ham thiet lap 2 tham so: kich thuoc va mang a
// Phuong thuc: tinh tong 2 vector, toan tu == so sanh 2 vector
#include <iostream>

using namespace std;

class Vector {
private:
  int n;
  double *a;

public:
  // Ham thiet lap khong tham so: nhap n va cac toa do
  Vector() {
    cout << "Nhap kich thuoc vector: ";
    cin >> n;
    a = new double[n];
    for (int i = 0; i < n; i++) {
      cout << "a[" << i << "] = ";
      cin >> a[i];
    }
  }

  // Ham thiet lap 1 tham so: kich thuoc, cac toa do = 0
  Vector(int n) {
    this->n = n;
    a = new double[n];
    for (int i = 0; i < n; i++) a[i] = 0;
  }

  // Ham thiet lap 2 tham so: kich thuoc va mang a
  Vector(int n, double arr[]) {
    this->n = n;
    a = new double[n];
    for (int i = 0; i < n; i++) a[i] = arr[i];
  }

  // Ham thiet lap sao chep (can vi co cap phat dong)
  Vector(const Vector &v) {
    n = v.n;
    a = new double[n];
    for (int i = 0; i < n; i++) a[i] = v.a[i];
  }

  ~Vector() { delete[] a; }

  // Tong 2 vector
  Vector tong(const Vector &v) const {
    Vector kq(n);
    for (int i = 0; i < n && i < v.n; i++) kq.a[i] = a[i] + v.a[i];
    return kq;
  }

  // So sanh 2 vector
  bool operator==(const Vector &v) const {
    if (n != v.n) return false;
    for (int i = 0; i < n; i++)
      if (a[i] != v.a[i]) return false;
    return true;
  }

  void xuat() const {
    cout << "(";
    for (int i = 0; i < n; i++) cout << a[i] << (i < n - 1 ? ", " : "");
    cout << ")";
  }
};

int main() {
  double m1[] = {1, 2, 3};
  double m2[] = {4, 5, 6};
  Vector a(3, m1), b(3, m2);

  cout << "a = "; a.xuat(); cout << endl;
  cout << "b = "; b.xuat(); cout << endl;

  Vector c = a.tong(b);
  cout << "a + b = "; c.xuat(); cout << endl;

  cout << "a == b ? " << (a == b ? "Bang nhau" : "Khac nhau") << endl;
  Vector d(3, m1);
  cout << "a == d ? " << (a == d ? "Bang nhau" : "Khac nhau") << endl;

  return 0;
}
