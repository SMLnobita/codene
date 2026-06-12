#include <stdio.h>
#include <stdlib.h>
// Hoan vi
void hoanvi(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
// Doc file va ghi file
int demPhanTu(const char *tenfile) {
  FILE *f = fopen(tenfile, "rt");
  int dem = 0;
  int temp;
  while (fscanf(f, "%d", &temp) == 1) {
    dem++;
  }
  fclose(f);
  return dem;
}
void readfile(int *arr, int *n, const char *filename) {
  FILE *fi = fopen(filename, "rt");
  int temp;
  *n = 0;
  while (fscanf(fi, "%d", &temp) == 1) {
    printf("%d ", temp);
    arr[(*n)++] = temp;
  }
  fclose(fi);
}
void writefile(int *arr, int n, const char *filename) {
  FILE *fo = fopen(filename, "wt");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
    fprintf(fo, "%d ", arr[i]);
  }
  fclose(fo);
}
// Cac thua toan sap xep
void interchangesort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i] > arr[j]) {
        hoanvi(&arr[i], &arr[j]);
      }
    }
  }
}

void selectionsort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[min_idx] > arr[j]) {
        min_idx = j;
      }
    }
    hoanvi(&arr[i], &arr[min_idx]);
  }
}

void insertsort(int *arr, int n) {
  int pos, x;
  for (int i = 1; i < n; i++) {
    x = arr[i];
    pos = i - 1;
    while (pos >= 0 && arr[pos] > x) {
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = x;
  }
}

void bubblesort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (arr[j] < arr[j - 1]) {
        hoanvi(&arr[j], &arr[j - 1]);
      }
    }
  }
}

void quicksort(int a[], int left, int right) {
  int i = left, j = right;
  int x = a[(left + right) / 2];

  if (left >= right)
    return;

  while (i <= j) {
    while (a[i] < x)
      i++;
    while (a[j] > x)
      j--;
    if (i <= j) {
      hoanvi(&a[i], &a[j]);
      i++;
      j--;
    }
  }

  if (left < j)
    quicksort(a, left, j);
  if (i < right)
    quicksort(a, i, right);
}

int main() {
  int n = demPhanTu("input.txt");
  int *arr = (int *)malloc(n * sizeof(int));
  // doc file
  readfile(arr, &n, "input.txt");
  // Phan thuat toan sap xep

  interchangesort(arr, n);
  //   selectionsort(arr, n);
  //   insertsort(arr, n);
  //   bubblesort(arr, n);
  //   quicksort(arr, 0, n - 1);

  // ghi ra file
  printf("\n");
  writefile(arr, n, "output.txt");
  free(arr);
  return 0;
}