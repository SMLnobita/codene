// De 6 - Cau 2: Lop tam giac
// Toan tu == so sanh 2 tam giac bang nhau theo truong hop 3 canh bang nhau
#include <iostream>

using namespace std;

class TamGiac {
private:
  double a, b, c;

  // Sap xep 3 canh tang dan de so sanh khong phu thuoc thu tu nhap
  void sapXep(double &x, double &y, double &z) const {
    double m[3] = {x, y, z};
    for (int i = 0; i < 2; i++)
      for (int j = i + 1; j < 3; j++)
        if (m[i] > m[j]) {
          double t = m[i];
          m[i] = m[j];
          m[j] = t;
        }
    x = m[0]; y = m[1]; z = m[2];
  }

public:
  TamGiac(double a = 0, double b = 0, double c = 0) {
    this->a = a;
    this->b = b;
    this->c = c;
  }

  void nhap() {
    cout << "Nhap 3 canh: ";
    cin >> a >> b >> c;
  }

  void xuat() const { cout << "(" << a << ", " << b << ", " << c << ")"; }

  // 2 tam giac bang nhau khi co 3 canh bang nhau (khong ke thu tu)
  bool operator==(const TamGiac &t) const {
    double a1 = a, b1 = b, c1 = c;
    double a2 = t.a, b2 = t.b, c2 = t.c;
    sapXep(a1, b1, c1);
    sapXep(a2, b2, c2);
    return a1 == a2 && b1 == b2 && c1 == c2;
  }
};

int main() {
  TamGiac t1(3, 4, 5);
  TamGiac t2(5, 3, 4);  // cung 3 canh, khac thu tu
  TamGiac t3(3, 4, 6);

  cout << "t1 = "; t1.xuat(); cout << endl;
  cout << "t2 = "; t2.xuat(); cout << endl;
  cout << "t3 = "; t3.xuat(); cout << endl;

  cout << "\nt1 == t2 ? " << (t1 == t2 ? "Bang nhau" : "Khac nhau") << endl;
  cout << "t1 == t3 ? " << (t1 == t3 ? "Bang nhau" : "Khac nhau") << endl;

  return 0;
}
