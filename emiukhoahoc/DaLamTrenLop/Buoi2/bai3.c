#include <math.h>
#include <stdio.h>

int chinhPhuong(int n) {
  if (n < 0)
    return 0;
  int canbac2 = (int)sqrt(n);
  return canbac2 * canbac2 == n;
}

void suLySCP(int *arr, int n) {
  int temp = 0;
  printf("Cac so chinh phuong: ");
  for (int i = 0; i < n; i++) {
    if (chinhPhuong(arr[i])) {
      printf("%d ", arr[i]);
      temp++;
    }
  }
  printf("\nSo luong so chinh phuong: %d", temp);
  printf("\n");
}

int main() {
  int arr[] = {1, 2, 4, 7, 9, 16, 18, 25, -4};
  int size = sizeof(arr) / sizeof(arr[0]);
  suLySCP(arr, size);
  return 0;
}