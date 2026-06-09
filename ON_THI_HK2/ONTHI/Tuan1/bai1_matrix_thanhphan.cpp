// Tuan 1 - Bai 1: Lop matrix
// Cac phuong thuc: nhap, xuat, cong 2 ma tran
// Ham cong la HAM THANH PHAN cua lop matrix
#include <iostream>

using namespace std;

class matrix {
private:
  int m, n;          // so dong, so cot
  int a[20][20];     // du lieu ma tran

public:
  void nhap();
  void xuat();
  matrix cong(matrix b);  // ham thanh phan: cong 2 ma tran
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

matrix matrix::cong(matrix b) {
  matrix kq;
  kq.m = m;
  kq.n = n;
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
      kq.a[i][j] = a[i][j] + b.a[i][j];
  return kq;
}

int main() {
  matrix a, b, c;

  cout << "--- Nhap ma tran A ---\n";
  a.nhap();
  cout << "--- Nhap ma tran B (cung kich thuoc voi A) ---\n";
  b.nhap();

  c = a.cong(b);

  cout << "\nMa tran A:\n";
  a.xuat();
  cout << "\nMa tran B:\n";
  b.xuat();
  cout << "\nTong A + B:\n";
  c.xuat();

  return 0;
}
