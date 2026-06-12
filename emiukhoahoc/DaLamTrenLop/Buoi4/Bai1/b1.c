#include <stdio.h>
#include <stdlib.h>

int demPhanTu(const char *tenfile) {
  FILE *f = fopen(tenfile, "rt");
  int temp;
  int dem = 0;
  while (fscanf(f, "%d", &temp) == 1) {
    dem++;
  }
  fclose(f);
  return dem;
}

void readfile(int *arr, const char *tenfile) {
  FILE *fi = fopen(tenfile, "rt");
  int i = 0;
  printf("Du lieu tu file: ");
  while (fscanf(fi, "%d", &arr[i]) == 1) {
    printf("%d ", arr[i]);
    i++;
  }
  fclose(fi);
}

void writefile(int *arr, int n, const char *tenfile) {
  FILE *fo = fopen(tenfile, "wt");
  printf("\nDu lieu luu file: ");
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
    fprintf(fo, "%d ", arr[i]);
  }
  fclose(fo);
}

void hoanvi(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(int *arr, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && arr[left] > arr[largest])
    largest = left;
  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    hoanvi(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}

void buildHeap(int *arr, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i);
  }
}

void heapSort(int *arr, int n) {
  buildHeap(arr, n);
  for (int i = n - 1; i > 0; i--) {
    hoanvi(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}

void ShellSort(int a[], int N, int h[], int k) {
  int step, i, pos;
  int x;
  int len;

  for (step = k - 1; step >= 0; step--) {
    len = h[step];

    for (i = len; i < N; i++) {
      x = a[i];
      pos = i - len;

      while (pos >= 0 && x < a[pos]) {
        a[pos + len] = a[pos];
        pos = pos - len;
      }

      a[pos + len] = x;
    }
  }
}

int main() {
  char choice;
  int n = demPhanTu("data.txt");
  int *arr = (int *)malloc(n * sizeof(int));
  readfile(arr, "data.txt");
  while (1) {
    do {
      printf("\n1: Heap Sort\n");
      printf("2: Shell Sort\n");
      printf("q: thoat chuong trinh\n");
      printf("Nhap luu chon: ");
      scanf(" %c", &choice);
      system("cls");
    } while (choice != '1' && choice != '2' && choice != 'q');

    if (choice == '1') {
      heapSort(arr, n);
    } else if (choice == '2') {
      int h[] = {1, 3};
      int k = 2;
      ShellSort(arr, n, h, k);
    } else if (choice == 'q') {
      break;
    }
    writefile(arr, n, "ketqua.txt");
  }
  free(arr);
  return 0;
}
