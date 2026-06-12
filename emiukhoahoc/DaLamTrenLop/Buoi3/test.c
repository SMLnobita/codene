#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void nhapMang(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("arr[%d]: ", i + 1);
    scanf("%d", &arr[i]);
  }
}

void xuatMang(int *arr, int n) {
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void insertionSort_up(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int x = arr[i], pos = i - 1;
    while (pos >= 0 && arr[pos] > x) {
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = x;
  }
}

void insertionSort_down(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int x = arr[i], pos = i - 1;
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
    printf("Enter n (n >= 5): ");
    scanf("%d", &n);
  } while (n < 5);

  int *arr = (int *)malloc(n * sizeof(int));
  int *arr2 = (int *)malloc(n * sizeof(int));

  nhapMang(arr, n);
  for (int i = 0; i < n; i++)
    arr2[i] = arr[i];

  printf("\nOriginal array: ");
  xuatMang(arr, n);

  LARGE_INTEGER freq, start, end;
  QueryPerformanceFrequency(&freq);

  // ===== Ascending =====
  QueryPerformanceCounter(&start);
  insertionSort_up(arr, n);
  QueryPerformanceCounter(&end);

  printf("\n[Ascending]  Result: ");
  xuatMang(arr, n);
  printf("[Ascending]  Time: %.2f ns\n",
         (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1e9);

  // ===== Descending =====
  QueryPerformanceCounter(&start);
  insertionSort_down(arr2, n);
  QueryPerformanceCounter(&end);

  printf("\n[Descending] Result: ");
  xuatMang(arr2, n);
  printf("[Descending] Time: %.2f ns\n",
         (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1e9);

  free(arr);
  free(arr2);
  return 0;
}