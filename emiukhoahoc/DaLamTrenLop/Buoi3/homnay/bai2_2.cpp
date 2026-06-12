#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void hoanvi(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void nhapMang(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("nhap arr[%d]: ", i);
    scanf("%d", &arr[i]);
  }
}

void xuatMang(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}

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
  int *arr2 = (int *)malloc(n * sizeof(int));

  // nhapMang(arr, n);
  srand(time(NULL));
  for (int i = 0; i < n; i++)
    arr[i] = rand() % 1000;
  for (int i = 0; i < n; i++)
    arr2[i] = arr[i];

  printf("Insertion Sort tang dan\n");
  clock_t start = clock();
  insertionSort_up(arr, n);
  clock_t end = clock();
  double thoiGian = (double)(end - start) / CLOCKS_PER_SEC;
  xuatMang(arr, n);

  printf("Insertion Sort giam dan\n");
  start = clock();
  insertionSort_down(arr2, n);
  end = clock();
  double thoiGian2 = (double)(end - start) / CLOCKS_PER_SEC;
  xuatMang(arr2, n);

  printf("\n");
  printf("\nThoi gian insertion sort tang dan: %.6lf giay \n", thoiGian);
  printf("\nThoi gian insertion sort giam dan: %.6lf giay \n", thoiGian2);

  free(arr);
  free(arr2);
  return 0;
}