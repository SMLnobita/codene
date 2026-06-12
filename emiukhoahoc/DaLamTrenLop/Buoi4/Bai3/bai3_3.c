#include <stdio.h>

void xacDinhDuongChay(int arr[], int n) {
  printf("Cac duong chay tang:\n");
  int i = 0, run = 1;
  while (i < n) {
    int j = i;
    while (j + 1 < n && arr[j + 1] >= arr[j])
      j++;
    printf("Duong chay %d [%d -> %d]: ", run++, i + 1, j + 1);
    for (int k = i; k <= j; k++)
      printf("%d ", arr[k]);
    printf("\n");
    i = j + 1;
  }
}

int main() {
  int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Mang ban dau: ");
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);
  printf("\n\n");

  xacDinhDuongChay(arr, n);
  return 0;
}