#include <stdio.h>
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

int timSoNuyenTo(int *arr, int n, int *primes) {
  printf("\nCac so nguyen to: ");
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

void docFile(const char *tenfile, int *arr, int *n) {
  FILE *fi = fopen(tenfile, "rt");
  if (fi == NULL)
    return;

  int temp;
  *n = 0;

  while (!feof(fi)) {
    if (fscanf(fi, "%d", &temp) == 1) {
      printf("%d ", temp);
      arr[(*n)++] = temp;
    }
  }

  fclose(fi);
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
  int arr[100], primes[100];
  int n = 0, pn = 0;
  docFile("input.txt", arr, &n);
  pn = timSoNuyenTo(arr, n, primes);
  ghiFile("output.txt", primes, pn);
  return 0;
}