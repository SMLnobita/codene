#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Nhap va Xuat Mang
void nhapMang(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("arr[%d]: ", i + 1);
    scanf("%d", &arr[i]);
  }
}
void xuatMang(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}
// Thua toan sap xep
void insertionSort_up(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int x = arr[i];
    int pos = i - 1;
    while (pos >= 0 && arr[pos] > x) {
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = x;
  }
}
void insertionSort_down(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int x = arr[i];
    int pos = i - 1;
    while (pos >= 0 && arr[pos] < x) {
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = x;
  }
}

int main() {
  int n;
  do {
    printf("Nhap n (n>=5): ");
    scanf("%d", &n);
  } while (n < 5);
  int *arr = (int *)malloc(n * sizeof(int));

  nhapMang(arr, n);
  // srand(time(NULL));
  // for (int i = 0; i < n; i++)
  //   arr[i] = rand() % 1000;

  clock_t start = clock();
  insertionSort_up(arr, n);
  //    insertionSort_down(arr, n);
  clock_t end = clock();

  double thoiGian = (double)(end - start) / CLOCKS_PER_SEC;

  xuatMang(arr, n);
  printf("\nThoi gian: %.6lf giay \n", thoiGian);
  free(arr);
  return 0;
}