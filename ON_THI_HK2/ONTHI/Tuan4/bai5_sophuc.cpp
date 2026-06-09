// Tuan 4 - Bai 5: Lop so phuc
// Toan tu: +, -, * tren lop so phuc
// Chuyen doi: so phuc -> so thuc (lay phan thuc), so thuc -> so phuc
#include <iostream>

using namespace std;

class SoPhuc {
private:
  double thuc;  // phan thuc
  double ao;    // phan ao

public:
  SoPhuc(double t = 0, double a = 0) {
    thuc = t;
    ao = a;
  }

  // Chuyen so thuc sang so phuc (constructor 1 tham so dong vai tro chuyen kieu)
  // Da co o constructor tren: SoPhuc x = 5.0;  -> 5 + 0i

  // Chuyen so phuc sang so thuc: ep kieu (double)
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
  out << p.thuc;
  if (p.ao >= 0)
    out << " + " << p.ao << "i";
  else
    out << " - " << -p.ao << "i";
  return out;
}

int main() {
  SoPhuc a(3, 4), b(1, -2);

  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "a + b = " << a + b << endl;
  cout << "a - b = " << a - b << endl;
  cout << "a * b = " << a * b << endl;

  // So thuc -> so phuc
  SoPhuc c = 5.0;
  cout << "\nSo thuc 5.0 -> so phuc: " << c << endl;

  // So phuc -> so thuc (lay phan thuc)
  double d = (double)a;
  cout << "So phuc a -> so thuc (phan thuc): " << d << endl;

  return 0;
}
