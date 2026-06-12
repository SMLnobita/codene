#include <stdio.h>

int tinhTongDeQuy(int n) {
  if (n == 0) {
    return 0;
  }
  return n + tinhTongDeQuy(n - 1);
}

int tinhFibonacci(int n) {
  if (n <= 1)
    return n;
  return tinhFibonacci(n - 1) + tinhFibonacci(n - 2);
}

int main() {
  int n;
  scanf("%d", &n);
  printf("De quy tong: %d\n", tinhTongDeQuy(n));
  printf("Fibonacci: %d\n", tinhFibonacci(n));
  return 0;
}