// De 5 - Cau 2: Lop ma tran
// Toan tu == so sanh 2 ma tran co bang nhau khong
#include <iostream>

using namespace std;

class matrix {
private:
  int m, n;
  int a[20][20];

public:
  void nhap();
  void xuat();
  bool operator==(const matrix &b) const;
};

void matrix::nhap() {
  cout << "Nhap so dong: ";
  cin >> m;
  cout << "Nhap so cot: ";
  cin >> n;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++) {
      cout << "a[" << i << "][" << j << "] = ";
      cin >> a[i][j];
    }
}

void matrix::xuat() {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      cout << a[i][j] << "\t";
    cout << endl;
  }
}

// 2 ma tran bang nhau khi cung kich thuoc va tat ca phan tu bang nhau
bool matrix::operator==(const matrix &b) const {
  if (m != b.m || n != b.n) return false;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      if (a[i][j] != b.a[i][j]) return false;
  return true;
}

int main() {
  matrix a, b;

  cout << "--- Nhap ma tran A ---\n";
  a.nhap();
  cout << "--- Nhap ma tran B ---\n";
  b.nhap();

  cout << "\nMa tran A:\n"; a.xuat();
  cout << "Ma tran B:\n"; b.xuat();

  cout << "\n2 ma tran "
       << (a == b ? "BANG NHAU" : "KHAC NHAU") << endl;

  return 0;
}
