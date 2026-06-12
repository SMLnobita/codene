#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int ngay;
  int thang;
  int nam;
} NgaySinh;

typedef struct {
  char mssv[20];
  char name[50];
  float diemTB;
  NgaySinh ngaySinh;
} sinhVien;

int demPhanTu(const char *tenfile) {
  FILE *fi = fopen(tenfile, "rt");
  char mssv[20], name[50];
  float diemTB;
  int ngay, thang, nam;
  int dem = 0;
  while (fscanf(fi, " %[^,],%[^,],%f,%d,%d,%d", mssv, name, &diemTB, &ngay,
                &thang, &nam) == 6) {
    dem++;
  }
  fclose(fi);
  return dem;
}

void docFile(const char *tenfile, sinhVien *arr) {
  FILE *fi = fopen(tenfile, "rt");
  int i = 0;
  while (fscanf(fi, " %19[^,],%49[^,],%f,%d,%d,%d", arr[i].mssv, arr[i].name,
                &arr[i].diemTB, &arr[i].ngaySinh.ngay, &arr[i].ngaySinh.thang,
                &arr[i].ngaySinh.nam) == 6) {
    i++;
  }
  fclose(fi);
}

void ghiFile(const char *tenfile, sinhVien *arr, int n) {
  FILE *fo = fopen(tenfile, "wt");
  for (int i = 0; i < n; i++) {
    fprintf(fo, "%s,%s,%.2f,%d,%d,%d\n", arr[i].mssv, arr[i].name,
            arr[i].diemTB, arr[i].ngaySinh.ngay, arr[i].ngaySinh.thang,
            arr[i].ngaySinh.nam);
  }
}

void inMangHinh(sinhVien *arr, int n) {
  printf("%-14s %-30s %-14s %s", "MSSV", "Ten", "DiemTB", "NgayThangNam");
  printf("\n---------------------------------------------------------------\n");
  for (int i = 0; i < n; i++) {
    printf("%-14s %-30s %-14.2f %02d/%02d/%02d\n", arr[i].mssv, arr[i].name,
           arr[i].diemTB, arr[i].ngaySinh.ngay, arr[i].ngaySinh.thang,
           arr[i].ngaySinh.nam);
  }
  printf("---------------------------------------------------------------\n");
}
// Xu ly
void hoanvi(sinhVien *a, sinhVien *b) {
  sinhVien temp = *a;
  *a = *b;
  *b = temp;
}

int soSanhNgaySinh(sinhVien a, sinhVien b) {
  if (a.ngaySinh.nam != b.ngaySinh.nam)
    return a.ngaySinh.nam - b.ngaySinh.nam;
  if (a.ngaySinh.thang != b.ngaySinh.thang)
    return a.ngaySinh.thang - b.ngaySinh.thang;
  return a.ngaySinh.ngay - b.ngaySinh.ngay;
}

const char *layTen(const char *hoTen) {
  const char *ten = strrchr(hoTen, ' ');
  return ten ? ten + 1 : hoTen;
}

// Thuat toan
void bubbleSort(sinhVien *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (arr[j].diemTB < arr[j - 1].diemTB) {
        hoanvi(&arr[j], &arr[j - 1]);
      }
    }
  }
}

void bubbleSort_MSSV(sinhVien *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (strcmp(arr[j].mssv, arr[j - 1].mssv) < 0) {
        hoanvi(&arr[j], &arr[j - 1]);
      }
    }
  }
}

void bubbleSort_Ten(sinhVien *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (strcmp(layTen(arr[j].name), layTen(arr[j - 1].name)) < 0) {
        hoanvi(&arr[j], &arr[j - 1]);
      }
    }
  }
}

void quicksort(sinhVien *arr, int left, int right) {
  int i = left, j = right;
  sinhVien x = arr[(left + right) / 2];

  if (left >= right)
    return;

  while (i <= j) {
    while (soSanhNgaySinh(arr[i], x) < 0)
      i++;
    while (soSanhNgaySinh(arr[j], x) > 0)
      j--;
    if (i <= j) {
      hoanvi(&arr[i], &arr[j]);
      i++;
      j--;
    }
  }

  if (left < j)
    quicksort(arr, left, j);
  if (i < right)
    quicksort(arr, i, right);
}

void quickSort(sinhVien *arr, int n) { quicksort(arr, 0, n - 1); }

int main() {
  char choice;
  int n = demPhanTu("data.txt");
  if (n < 5) {
    printf("Vui long them du thong tin >= 5");
    return 0;
  }
  sinhVien *danhSach = (sinhVien *)malloc(n * sizeof(sinhVien));
  docFile("data.txt", danhSach);
  while (1) {
    do {
      printf("1: Bubble Sort sap xep danh sach theo theo diemTB\n");
      printf("2: Quick Sort sap xep danh sach theo ngay thang sinh\n");
      printf("3: sap xep danh sach theo MSSV\n");
      printf("4: sap xep danh sach theo Ten\n");
      printf("q: Nhan q de thoat\n");
      printf("Nhap lua chon: ");
      scanf(" %c", &choice);
      system("cls");
    } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' &&
             choice != 'q');

    if (choice == '1') {
      printf(
          "--------------------------Bubble Sort--------------------------\n");
      bubbleSort(danhSach, n);
    } else if (choice == '2') {
      printf(
          "--------------------------Quick Sort---------------------------\n");
      quickSort(danhSach, n);
    } else if (choice == '3') {
      printf(
          "------------------------Sap xep MSSV---------------------------\n");
      bubbleSort_MSSV(danhSach, n);
    } else if (choice == '4') {
      printf(
          "------------------------Sap xep Ten-----------------------------\n");
      bubbleSort_Ten(danhSach, n);
    } else if (choice == 'q') {
      break;
    }
    inMangHinh(danhSach, n);
    ghiFile("data.txt", danhSach, n);
  }

  // ghiFile("data.txt", danhSach, n);
  free(danhSach);
  return 0;
}