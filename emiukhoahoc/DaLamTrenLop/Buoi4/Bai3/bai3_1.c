#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int ngay, thang, nam;
} ngaySinh;

typedef struct {
  char mssv[20];
  char name[50];
  float diemTB;
  ngaySinh ngaysinh;
} sinhVien;

// 1.1 - Doc file
int demPhanTu(const char *tenfile) {
  FILE *f = fopen(tenfile, "rt");
  char mssv[20], name[40];
  float diemTB;
  int ngay, thang, nam, dem = 0;
  while (fscanf(f, " %19[^,],%49[^,],%f,%d,%d,%d", mssv, name, &diemTB, &ngay,
                &thang, &nam) == 6)
    dem++;
  fclose(f);
  return dem;
}

void readFile(const char *tenfile, sinhVien *arr) {
  FILE *fi = fopen(tenfile, "rt");
  int dem = 0;
  while (fscanf(fi, " %19[^,],%49[^,],%f,%d,%d,%d", arr[dem].mssv,
                arr[dem].name, &arr[dem].diemTB, &arr[dem].ngaysinh.ngay,
                &arr[dem].ngaysinh.thang, &arr[dem].ngaysinh.nam) == 6)
    dem++;
  fclose(fi);
}

void inMangHinh(sinhVien *arr, int n) {
  printf("%-14s %-30s %-14s %s\n", "MSSV", "Ten", "DiemTB", "NgayThangNam");
  printf("---------------------------------------------------------------\n");
  for (int i = 0; i < n; i++)
    printf("%-14s %-30s %-14.2f %02d/%02d/%02d\n", arr[i].mssv, arr[i].name,
           arr[i].diemTB, arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang,
           arr[i].ngaysinh.nam);
}

// 1.2 - Heap Sort giam theo MSSV
void hoanvi(sinhVien *a, sinhVien *b) {
  sinhVien temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(sinhVien *arr, int n, int i) {
  int largest = i, left = 2 * i + 1, right = 2 * i + 2;
  if (left < n && strcmp(arr[left].mssv, arr[largest].mssv) < 0)
    largest = left;
  if (right < n && strcmp(arr[right].mssv, arr[largest].mssv) < 0)
    largest = right;
  if (largest != i) {
    hoanvi(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}

void heapSort(sinhVien *arr, int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);
  for (int i = n - 1; i > 0; i--) {
    hoanvi(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}

// 1.3 - Shell Sort tang theo DiemTB
void shellSort(sinhVien *arr, int n, int *h, int k) {
  for (int step = k - 1; step >= 0; step--) {
    int len = h[step];
    for (int i = len; i < n; i++) {
      sinhVien x = arr[i];
      int pos = i - len;
      while (pos >= 0 && x.diemTB < arr[pos].diemTB) {
        arr[pos + len] = arr[pos];
        pos -= len;
      }
      arr[pos + len] = x;
    }
  }
}

int main() {
  int n = demPhanTu("data.txt");
  if (n < 5) {
    printf("Can >= 5 sinh vien\n");
    return 0;
  }

  sinhVien *arr = (sinhVien *)malloc(n * sizeof(sinhVien));
  readFile("data.txt", arr);

  // Tinh day h: h_k = 1, h_i = (h_{i-1} - 1) / 2, k = log2(n) - 1
  int k = 0, temp = n;
  while (temp > 1) {
    temp = (temp - 1) / 2;
    k++;
  }
  int *h = (int *)malloc(k * sizeof(int));
  h[0] = 1;
  for (int i = 1; i < k; i++)
    h[i] = h[i - 1] * 2 + 1;

  char choice;
  while (1) {
    printf("1: Heap Sort  - giam theo MSSV\n");
    printf("2: Shell Sort - tang theo DiemTB\n");
    printf("q: Thoat\n");
    printf("Nhap: ");
    scanf(" %c", &choice);
    system("cls");
    if (choice == '1') {
      heapSort(arr, n);
      inMangHinh(arr, n);
    } else if (choice == '2') {
      shellSort(arr, n, h, k);
      inMangHinh(arr, n);
    } else if (choice == 'q')
      break;
  }

  free(h);
  free(arr);
  return 0;
}