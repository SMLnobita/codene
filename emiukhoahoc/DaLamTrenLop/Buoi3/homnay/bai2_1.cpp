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

  nhapMang(arr, n);
  for (int i = 0; i < n; i++)
    arr2[i] = arr[i];

  insertionSort_up(arr, n);
  insertionSort_down(arr2, n);

  printf("Mang tang dan: ");
  xuatMang(arr, n);
  printf("\nMang giam dan: ");
  xuatMang(arr2, n);

  free(arr);
  free(arr2);
  return 0;
}