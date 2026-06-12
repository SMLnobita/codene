#include <stdio.h>
#include <stdlib.h>

// Hoan vi
void hoanvi(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
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
// Thuat toan xap sep
void selectionSort_up(int *arr, int n, int *dem) {
  for (int i = 0; i < n - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++) {
      (*dem)++;
      if (arr[min] > arr[j]) {
        min = j;
      }
    }
    hoanvi(&arr[i], &arr[min]);
  }
}
void selectionSort_down(int *arr, int n, int *dem) {
  for (int i = 0; i < n - 1; i++) {
    int max = i;
    for (int j = i + 1; j < n; j++) {
      (*dem)++;
      if (arr[max] < arr[j]) {
        max = j;
      }
    }
    hoanvi(&arr[i], &arr[max]);
  }
}
int main() {
  int n;
  int dem = 0;
  do {
    printf("Nhap n (n>=5): ");
    scanf("%d", &n);
  } while (n < 5);
  int *arr = (int *)malloc(n * sizeof(int));
  nhapMang(arr, n);
  // Chieu tang
  selectionSort_up(arr, n, &dem);
  //   //Chieu giam
  //   selectionSort_down(arr, n, &dem);
  xuatMang(arr, n);
  printf("\n%d", dem);
  return 0;
}