#include <stdio.h>
#include <stdlib.h>
int IsPrime(int n) {
  if (n < 2)
    return 0;
  if (n == 2)
    return 1;
  if (n % 2 == 0)
    return 0;
  for (int i = 3; i * i <= n; i += 2) {
    if (n % i == 0)
      return 0;
  }
  return 1;
}

int demSoPhanTuFile(const char *tenfile) {
  FILE *f = fopen(tenfile, "rt");
  int temp;
  int count = 0;
  while (!feof(f)) {
    if (fscanf(f, "%d", &temp) == 1)
      count++;
  }
  fclose(f);
  return count;
}

int timSoNuyenTo(int *arr, int n, int *primes) {
  printf("Cac so nguyen to: ");
  int pn = 0;
  for (int i = 0; i < n; i++) {
    if (IsPrime(arr[i])) {
      printf("%d ", arr[i]);
      primes[pn++] = arr[i];
    }
  }
  if (pn == 0)
    printf("\nKhong co so nguyen to");
  printf("\n");
  return pn;
}

int *docFile(const char *tenfile, int *n) {
  *n = demSoPhanTuFile(tenfile);
  if (*n <= 0)
    return NULL;

  FILE *fi = fopen(tenfile, "rt");
  if (fi == NULL)
    return NULL;

  int *arr = (int *)malloc(*n * sizeof(int));
  if (arr == NULL) {
    fclose(fi);
    return NULL;
  }

  for (int i = 0; i < *n; i++) {
    fscanf(fi, "%d", &arr[i]);
  }

  fclose(fi);
  return arr;
}

void ghiFile(const char *tenfile, int *arr, int n) {
  FILE *fo = fopen(tenfile, "wt");
  if (fo == NULL)
    return;
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
    fprintf(fo, "%d ", arr[i]);
  }
  fclose(fo);
}
int main() {
  int n, pn;
  int *arr = docFile("input.txt", &n);
  if (arr == NULL) {
    printf("Khong the doc du lieu tu file.\n");
    return 1;
  }
  pn = timSoNuyenTo(arr, n, arr); // Tim so nguyen to va luu vao arr
  if (pn > 0) {
    ghiFile("output.txt", arr, pn); // Ghi cac so nguyen to vao file
  } else {
    printf("Khong co so nguyen to nao duoc tim thay.\n");
  }
  free(arr); // Giai phong bo nho
  return 0;
}