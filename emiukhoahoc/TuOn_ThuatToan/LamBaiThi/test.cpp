#include <cstdio>
#include <iostream>

#define MAX 100

using namespace std;

struct SINHVIEN {
  char hoten[21];
  char mssv[11];
  float diem[5];
};

void nhap(SINHVIEN &sv) {
  printf("Nhap ten: ");
  scanf(" %20[^\n]", sv.hoten);
  printf("Nhap MSSV: ");
  scanf(" %10s", sv.mssv);
  printf("Ngay Sinh (dd/mm/yyyy): ");
  printf("Nhap 5 diem (cach nhau khoang cach): ");
  for (int i = 0; i < 5; i++) {
    scanf("%f", &sv.diem[i]);
  }
}

int NhapDS(SINHVIEN *arr) {
  int n;
  printf("So sinh vien: ");
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    printf("\nSinh Vien %d ", i + 1);
    nhap(arr[i]);
  }
  return n;
}
void SapXepTheoMSSV(SINHVIEN a[], int n) {
  for (int i = 1; i < n; i++) {
    SINHVIEN x = a[i];
    int j = i - 1;
    while (j >= 0 && strcmp(a[j].mssv, x.mssv) > 0) {
      a[j + 1] = a[j];
      j--;
    }
    a[j + 1] = x;
  }
}

int TimNhiPhanMSSV(SINHVIEN a[], int n, const char *mssv) {
  int l = 0, r = n - 1;
  while (l <= r) {
    int m = (l + r) / 2;
    int c = strcmp(a[m].mssv, mssv);
    if (c == 0)
      return m;
    if (c < 0)
      l = m + 1;
    else
      r = m - 1;
  }
  return -1;
}
int main() {}
