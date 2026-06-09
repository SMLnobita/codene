// Tuan 1 - Bai 2: Lop matrix
// Cac phuong thuc: nhap, xuat
// Ham cong 2 ma tran cai dat la HAM TU DO va la BAN (friend) cua lop matrix
#include <iostream>

using namespace std;

class matrix {
private:
  int m, n;
  int a[20][20];

public:
  void nhap();
  void xuat();
  // ham tu do, la ban cua lop matrix
  friend matrix cong(matrix x, matrix y);
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

// Ham tu do (khong thuoc lop) nhung la friend nen truy cap duoc thuoc tinh private
matrix cong(matrix x, matrix y) {
  matrix kq;
  kq.m = x.m;
  kq.n = x.n;
  for (int i = 0; i < x.m; i++)
    for (int j = 0; j < x.n; j++)
      kq.a[i][j] = x.a[i][j] + y.a[i][j];
  return kq;
}

int main() {
  matrix a, b, c;

  cout << "--- Nhap ma tran A ---\n";
  a.nhap();
  cout << "--- Nhap ma tran B (cung kich thuoc voi A) ---\n";
  b.nhap();

  c = cong(a, b);  // goi ham tu do

  cout << "\nMa tran A:\n";
  a.xuat();
  cout << "\nMa tran B:\n";
  b.xuat();
  cout << "\nTong A + B:\n";
  c.xuat();

  return 0;
}
