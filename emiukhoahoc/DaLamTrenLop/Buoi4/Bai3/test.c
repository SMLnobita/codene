#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int ngay, thang, nam;
} ngaySinh;

typedef struct {
  int mssv;
  char name[50];
  float diemTB;
  ngaySinh ngaysinh;
} sinhVien;

// Đếm số sinh viên trong file
int demPhanTu(const char *tenfile) {
  FILE *f = fopen(tenfile, "rt");

  int mssv;
  char name[50];
  float diemTB;
  int ngay, thang, nam;
  int dem = 0;

  while (fscanf(f, "%d,%49[^,],%f,%d,%d,%d", &mssv, name, &diemTB, &ngay,
                &thang, &nam) == 6) {
    dem++;
  }

  fclose(f);
  return dem;
}

void readFile(const char *tenfile, sinhVien *arr) {
  FILE *fi = fopen(tenfile, "rt");

  int i = 0;
  while (fscanf(fi, "%d,%49[^,],%f,%d,%d,%d", &arr[i].mssv, arr[i].name,
                &arr[i].diemTB, &arr[i].ngaysinh.ngay, &arr[i].ngaysinh.thang,
                &arr[i].ngaysinh.nam) == 6) {
    i++;
  }

  fclose(fi);
}

void inMangHinh(sinhVien *arr, int n) {
  printf("%-12s %-30s %-10s %s\n", "MSSV", "Ten", "DiemTB", "Ngay sinh");
  printf(
      "-------------------------------------------------------------------\n");

  for (int i = 0; i < n; i++) {
    printf("%-12d %-30s %-10.2f %02d/%02d/%04d\n", arr[i].mssv, arr[i].name,
           arr[i].diemTB, arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang,
           arr[i].ngaysinh.nam);
  }
}

int getMaxMSSV(sinhVien arr[], int n) {
  int max = arr[0].mssv;
  for (int i = 1; i < n; i++) {
    if (arr[i].mssv > max) {
      max = arr[i].mssv;
    }
  }
  return max;
}

void countSortMSSV(sinhVien arr[], int n, int exp) {
  sinhVien *output = (sinhVien *)malloc(n * sizeof(sinhVien));
  int count[10] = {0};

  for (int i = 0; i < n; i++) {
    int digit = (arr[i].mssv / exp) % 10;
    count[digit]++;
  }

  for (int i = 1; i < 10; i++) {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    int digit = (arr[i].mssv / exp) % 10;
    output[count[digit] - 1] = arr[i];
    count[digit]--;
  }

  // Chép lại vào mảng arr
  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
  }

  free(output);
}

// Radix Sort theo MSSV
void radixSortMSSV(sinhVien arr[], int n) {
  int max = getMaxMSSV(arr, n);

  for (int exp = 1; max / exp > 0; exp *= 10) {
    countSortMSSV(arr, n, exp);
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

  printf("Danh sach truoc khi sap xep:\n");
  inMangHinh(arr, n);

  radixSortMSSV(arr, n);

  printf("\nDanh sach sau khi sap xep tang dan theo MSSV:\n");
  inMangHinh(arr, n);

  free(arr);
  return 0;
}