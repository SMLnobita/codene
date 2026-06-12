#include <stdio.h>
#include <stdlib.h>

int laysoPhanTu(char *tenFile) {
  FILE *fi = fopen(tenFile, "rt");
  if (!fi)
    return 0;
  int n = 0, temp;
  while (fscanf(fi, "%d", &temp) == 1)
    n++;
  fclose(fi);
  return n;
}

void DocFile(char *tenFile, int *arr) {
  FILE *fi = fopen(tenFile, "rt");
  if (!fi)
    return;
  int temp, n = 0;
  while (fscanf(fi, "%d", &temp) == 1) {
    printf("%d ", temp);
    arr[n++] = temp;
  }
  fclose(fi);
}

void GhiFile(char *tenFile, int *arr, int n) {
  FILE *fo = fopen(tenFile, "wt"); // mo file, wt = ghi dang
  for (int i = 0; i < n; i++) {
    fprintf(fo, "%d ", arr[i]);
    printf("%d ", arr[i]);
  }
  fclose(fo); // dong file
}

void SapXep(int *arr, int n) {
  int temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[i]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}

int main() {
  int *mang = NULL;
  int n = laysoPhanTu((char *)"input.txt");
  printf("So phan tu trong file: %d\n", n);
  mang = (int *)malloc(n * sizeof(int));
  printf("Du lieu doc tu file:\n");
  DocFile((char *)"input.txt", mang);
  SapXep(mang, n);

  printf("\nMang sau khi sap xep:\n");
  GhiFile((char *)"output.txt", mang, n);

  free(mang);
  return 0;
}