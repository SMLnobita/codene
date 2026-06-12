#include <stdio.h>
#include <stdlib.h>

void DocFile(char *tenFile, int *arr) {
  FILE *fi = fopen(tenFile, "rt"); // mo file rt = doc dang
  int temp;
  int n = 0;
  while (!feof(fi)) // khi chua ket thuc file
  {
    fscanf(fi, "%d", &temp); // doc so thuc vao bien temp
    printf("%d ", temp);
    arr[n] = temp;
    n++;
  }
  fclose(fi); // dong file
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
  int n = 10;
  mang = (int *)malloc(n * sizeof(int));
  printf("Du lieu doc tu file:\n");
  DocFile((char *)"input.txt", mang);
  SapXep(mang, n);

  printf("\nMang sau khi sap xep:\n");
  GhiFile((char *)"output.txt", mang, n);
  return 0;
}