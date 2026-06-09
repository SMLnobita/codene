// De 1 - Cau 1: Lop so phuc z = a + bi
// Toan tu cong so phuc voi so thuc u: z + u = (a + u) + bi
// Toan tu nhan so phuc voi so thuc u: z * u = au + ubi
#include <iostream>

using namespace std;

class SoPhuc {
private:
  double a;  // phan thuc
  double b;  // phan ao

public:
  SoPhuc(double a = 0, double b = 0) {
    this->a = a;
    this->b = b;
  }

  // z + u = (a + u) + bi
  SoPhuc operator+(double u) const { return SoPhuc(a + u, b); }

  // z * u = au + ubi
  SoPhuc operator*(double u) const { return SoPhuc(a * u, b * u); }

  void xuat() const {
    if (b >= 0)
      cout << a << " + " << b << "i";
    else
      cout << a << " - " << -b << "i";
  }
};

int main() {
  SoPhuc z(3, 4);
  double u = 2;

  cout << "z = ";
  z.xuat();
  cout << "\nu = " << u << endl;

  cout << "z + u = ";
  (z + u).xuat();
  cout << endl;

  cout << "z * u = ";
  (z * u).xuat();
  cout << endl;

  return 0;
}
