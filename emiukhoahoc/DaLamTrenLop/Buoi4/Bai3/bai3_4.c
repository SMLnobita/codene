#include <stdio.h>
#include <stdlib.h>

void mergeRuns(int arr[], int temp[], int left, int mid, int right) {
  int i = left, j = mid + 1, k = left;
  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j])
      temp[k++] = arr[i++];
    else
      temp[k++] = arr[j++];
  }
  while (i <= mid)
    temp[k++] = arr[i++];
  while (j <= right)
    temp[k++] = arr[j++];
  for (int l = left; l <= right; l++)
    arr[l] = temp[l];
}

void naturalMergeSort(int arr[], int n) {
  int *temp = (int *)malloc(n * sizeof(int));
  int sorted = 0;

  while (!sorted) {
    sorted = 1;
    int i = 0;
    while (i < n) {
      // Tim cuoi duong chay thu nhat
      int mid = i;
      while (mid + 1 < n && arr[mid + 1] >= arr[mid])
        mid++;

      if (mid >= n - 1) {
        i = mid + 1;
        continue;
      }

      // Tim cuoi duong chay thu hai
      int right = mid + 1;
      while (right + 1 < n && arr[right + 1] >= arr[right])
        right++;

      mergeRuns(arr, temp, i, mid, right);
      sorted = 0;
      i = right + 1;
    }
  }
  free(temp);
}

int main() {
  int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
  int n = sizeof(arr) / sizeof(arr[0]);

  printf("Truoc khi sort: ");
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);

  naturalMergeSort(arr, n);

  printf("\nSau khi sort:  ");
  for (int i = 0; i < n; i++)
    printf("%d ", arr[i]);

  return 0;
}