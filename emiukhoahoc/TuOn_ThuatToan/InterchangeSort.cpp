#include <cstdio>
#include <iostream>

void inMang(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}

void InterchangeSort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (arr[i] > arr[j]) {
        std::swap(arr[i], arr[j]);
      }
    }
  }
}

void SelectionSort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int min = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[min] > arr[j]) {
        min = j;
      }
    }
    std::swap(arr[i], arr[min]);
  }
}

void BubbleSort(int *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    bool doi = false;
    for (int j = n - 1; j > i; j--) {
      if (arr[j] < arr[j - 1]) {
        std::swap(arr[j], arr[j - 1]);
        doi = true;
      }
    }
    if (!doi)
      break;
  }
}

void InsertionSort(int *arr, int n) {
  for (int i = 1; i < n; i++) {
    int x = arr[i];
    int pos = i - 1;
    while (pos >= 0 && arr[pos] > x) {
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = x;
  }
}

void QuickSort(int *arr, int left, int right) {
  if (left >= right)
    return;
  int x = arr[(left + right) / 2];
  int i = left, j = right;
  while (i <= j) {
    while (arr[i] < x)
      i++;
    while (arr[j] > x)
      j--;
    if (i <= j) {
      std::swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }
  QuickSort(arr, left, j);
  QuickSort(arr, i, right);
}

int TimKiem(int *arr, int n, int x) {
  for (int i = 0; i < n; i++) {
    if (arr[i] == x) {
      return i;
    }
  }
  return -1;
}

void ShellSort(int *arr, int n) {
  for (int h = n / 2; h > 0; h /= 2) {
    for (int i = h; i < n; i++) {
      int x = arr[i];
      int j = i - h;
      while (j >= 0 && arr[j] > x) {
        arr[j + h] = arr[j];
        j -= h;
      }
      arr[j + h] = x;
    }
  }
}

void Merge(int *arr, int left, int mid, int right) {
  int nb = mid - left + 1, nc = right - mid;
  int *b = new int[nb], *c = new int[nc];
  for (int i = 0; i < nb; i++)
    b[i] = arr[left + i];
  for (int i = 0; i < nc; i++)
    c[i] = arr[mid + 1 + i];
  int i = 0, j = 0, k = left;
  while (i < nb && j < nc)
    arr[k++] = (b[i] < c[j]) ? b[i++] : c[j++];
  while (i < nb)
    arr[k++] = b[i++];
  while (j < nc)
    arr[k++] = c[j++];
  delete[] b;
  delete[] c;
}

void MergeSort(int *arr, int left, int right) {
  if (left >= right)
    return;
  int mid = (left + right) / 2;
  MergeSort(arr, left, mid);
  MergeSort(arr, mid + 1, right);
  Merge(arr, left, mid, right);
}

int TimKiemNhiPhan(int *arr, int n, int x) {
  int left = 0;
  int right = n - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[mid] == x)
      return mid;
    if (arr[mid] > x)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return -1;
}

int main() {
  int arr[] = {23, 19, 24, 2, 1, 4, 240, 120, 999, 22000, 436};
  int arr2[] = {23, 19, 24, 2, 1, 4, 240, 120, 999, 22000, 436};
  int arr3[] = {23, 19, 24, 2, 1, 4, 240, 120, 999, 22000, 436};
  int arr4[] = {23, 19, 24, 2, 1, 4, 240, 120, 999, 22000, 436};
  int arr5[] = {23, 19, 24, 2, 1, 4, 240, 120, 999, 22000, 436};
  int arr6[] = {23, 19, 24, 2, 1, 4, 240, 120, 999, 22000, 436};
  int arr7[] = {23, 19, 24, 2, 1, 4, 240, 120, 999, 22000, 436};

  int n = sizeof(arr) / sizeof(int);
  InterchangeSort(arr, n);
  inMang(arr, n);

  printf("\n");
  SelectionSort(arr2, n);
  inMang(arr2, n);

  printf("\n");
  BubbleSort(arr3, n);
  inMang(arr3, n);

  printf("\n");
  InsertionSort(arr4, n);
  inMang(arr4, n);

  printf("\n");
  QuickSort(arr5, 0, n - 1);
  inMang(arr5, n);

  printf("\n");
  ShellSort(arr6, n);
  inMang(arr6, n);

  printf("\n");
  MergeSort(arr7, 0, n - 1);
  inMang(arr7, n);

  printf("\nDa tiem thay %d o vi tri %d", 2, TimKiem(arr, n, 2));
  printf("\nDa tiem thay %d o vi tri %d", 2, TimKiemNhiPhan(arr, n, 2));
  return 0;
}