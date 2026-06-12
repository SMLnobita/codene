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

int main() {
  int n = demPhanTu("data.txt");
  int *arr = (int *)malloc(n * sizeof(int));

  readfile(arr, "data.txt");
}