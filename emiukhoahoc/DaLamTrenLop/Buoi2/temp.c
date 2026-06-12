#include <stdio.h>

void bai2(int a[], int n) {
  int len1 = 1;   // do dai day con 1
  int maxlen = 1; // do dai day cao nhat
  int vitri = 0;

  for (int i = 1; i < n; i++) {
    if (a[i] > a[i - 1])
      len1++;
    else {
      if (len1 > maxlen) {
        maxlen = len1;
        vitri = i; // su dung de xuat ra day con can tim
      }
      len1 = 1;
    }
  }
  if (len1 > maxlen) {
    maxlen = len1;
    vitri = n;
  }
  printf("Day con dai nhat trong mang la: %d\n", maxlen);
  printf("Cac phan tu cua day la:");
  for (int i = vitri - maxlen; i < vitri; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}
int main() {
  int a[] = {1};
  int n = sizeof(a) / sizeof(int);
  bai2(a, n);
  return 0;
}