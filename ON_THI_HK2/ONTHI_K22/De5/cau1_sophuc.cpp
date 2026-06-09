// De 5 - Cau 1: Lop so phuc
// Toan tu +, -, * tren lop so phuc
// Chuyen doi: so phuc -> so thuc, so thuc -> so phuc
#include <iostream>

using namespace std;

class SoPhuc {
private:
  double thuc, ao;

public:
  // So thuc -> so phuc (constructor 1 tham so dong vai tro chuyen kieu)
  SoPhuc(double t = 0, double a = 0) {
    thuc = t;
    ao = a;
  }

  // So phuc -> so thuc (lay phan thuc)
  operator double() const { return thuc; }

  SoPhuc operator+(const SoPhuc &b) const {
    return SoPhuc(thuc + b.thuc, ao + b.ao);
  }
  SoPhuc operator-(const SoPhuc &b) const {
    return SoPhuc(thuc - b.thuc, ao - b.ao);
  }
  SoPhuc operator*(const SoPhuc &b) const {
    return SoPhuc(thuc * b.thuc - ao * b.ao, thuc * b.ao + ao * b.thuc);
  }

  friend ostream &operator<<(ostream &out, const SoPhuc &p);
};

ostream &operator<<(ostream &out, const SoPhuc &p) {
  if (p.ao >= 0)
    out << p.thuc << " + " << p.ao << "i";
  else
    out << p.thuc << " - " << -p.ao << "i";
  return out;
}

int main() {
  SoPhuc a(3, 4), b(1, -2);

  cout << "a = " << a << "\nb = " << b << endl;
  cout << "a + b = " << a + b << endl;
  cout << "a - b = " << a - b << endl;
  cout << "a * b = " << a * b << endl;

  SoPhuc c = 5.0;  // so thuc -> so phuc
  cout << "\n5.0 -> so phuc: " << c << endl;

  double d = (double)a;  // so phuc -> so thuc
  cout << "so phuc a -> so thuc: " << d << endl;

  return 0;
}
