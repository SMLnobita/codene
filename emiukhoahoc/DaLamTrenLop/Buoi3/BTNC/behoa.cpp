#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int ngay, thang, nam;
} NgaySinh;

typedef struct {
  char maSV[20];
  char tenSV[50];
  double diemTB;
  NgaySinh ngaySinh;
} sinhVien;

void docFile(const char *tenfile, sinhVien *arr, int n) {

  FILE *fi = fopen(tenfile, "rt");

  int dem = 0;

  // printf("%-10s %-20s %-10s %-15s\n", "Ma SV", "Ten SV", "Diem TB",
  //        "Ngay Sinh");
  // printf("------------------------------------------------------------\n");

  while (dem < n &&
         fscanf(fi, " %19[^,],%49[^,],%lf,%d,%d,%d", arr[dem].maSV,
                arr[dem].tenSV, &arr[dem].diemTB, &arr[dem].ngaySinh.ngay,
                &arr[dem].ngaySinh.thang, &arr[dem].ngaySinh.nam) == 6) {
    // printf("%-10s %-20s %-10.2f %02d/%02d/%d\n", arr[dem].maSV,
    // arr[dem].tenSV,
    //        arr[dem].diemTB, arr[dem].ngaySinh.ngay, arr[dem].ngaySinh.thang,
    //        arr[dem].ngaySinh.nam);
    dem++;
  }
  fclose(fi);
}

void ghiFile(const char *tenfile, sinhVien *arr, int n) {
  FILE *fo = fopen(tenfile, "wt");
  // printf("%-10s %-20s %-10s %-15s\n", "Ma SV", "Ten SV", "Diem TB",
  //        "Ngay Sinh");
  // printf("------------------------------------------------------------\n");
  for (int i = 0; i < n; i++) {
    fprintf(fo, "%s,%s,%.2lf,%d,%d,%d\n", arr[i].maSV, arr[i].tenSV,
            arr[i].diemTB, arr[i].ngaySinh.ngay, arr[i].ngaySinh.thang,
            arr[i].ngaySinh.nam);
  }
  fclose(fo);
}

void inDanhSach(sinhVien *arr, int n) {
  printf("%-10s %-20s %-10s %-15s\n", "Ma SV", "Ten SV", "Diem TB",
         "Ngay Sinh");
  printf("-----------------------------------------------------\n");
  for (int i = 0; i < n; i++) {
    printf("%-10s %-20s %-10.2f %02d/%02d/%d\n", arr[i].maSV, arr[i].tenSV,
           arr[i].diemTB, arr[i].ngaySinh.ngay, arr[i].ngaySinh.thang,
           arr[i].ngaySinh.nam);
  }
}

void hoanvi(sinhVien *a, sinhVien *b) {
  sinhVien temp = *a;
  *a = *b;
  *b = temp;
}

void bubblesort(sinhVien *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (arr[j].diemTB < arr[j - 1].diemTB) {
        hoanvi(&arr[j], &arr[j - 1]);
      }
    }
  }
}

void bubblesort_MSSV(sinhVien *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (strcmp(arr[j].maSV, arr[j - 1].maSV) < 0) {
        hoanvi(&arr[j], &arr[j - 1]);
      }
    }
  }
}

const char *layTen(const char *hoTen) {
  const char *ten = strrchr(hoTen, ' ');
  return ten ? ten + 1 : hoTen;
}

void bubblesort_Ten(sinhVien *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = n - 1; j > i; j--) {
      if (strcmp(layTen(arr[j].tenSV), layTen(arr[j - 1].tenSV)) < 0) {
        hoanvi(&arr[j], &arr[j - 1]);
      }
    }
  }
}

int soSanhNgaySinh(sinhVien a, sinhVien b) {
  if (a.ngaySinh.nam != b.ngaySinh.nam)
    return a.ngaySinh.nam - b.ngaySinh.nam;
  if (a.ngaySinh.thang != b.ngaySinh.thang) {
    return a.ngaySinh.thang - b.ngaySinh.thang;
  }
  return a.ngaySinh.ngay - b.ngaySinh.ngay;
}

void quicksort(sinhVien *arr, int left, int right) {
  int i = left, j = right;
  sinhVien x = arr[(left + right) / 2];

  if (left >= right)
    return;

  while (i <= j) {
    while (soSanhNgaySinh(arr[i], x) > 0)
      i++;
    while (soSanhNgaySinh(arr[j], x) < 0)
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

void sort(sinhVien *arr, int n) { quicksort(arr, 0, n - 1); }

int main() {
  int n, choice;
  do {
    printf("Nhap n (n>=5): ");
    scanf("%d", &n);
    system("cls");
  } while (n < 5);

  do {
    printf("1: Bubble Sort sap xep danh sach theo theo diemTB\n");
    printf("2: Quick Sort sap xep danh sach theo ngay thang sinh\n");
    printf("3: sap xep danh sach theo MSSV\n");
    printf("4: sap xep danh sach theo Ten\n");
    printf("Nhap lua chon: ");
    scanf("%d", &choice);
    system("cls");
  } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

  sinhVien *danhSach = (sinhVien *)malloc(n * sizeof(sinhVien));

  docFile("data.txt", danhSach, n);

  if (choice == 1) {
    printf("--------------------Bubble Sort----------------------\n");
    bubblesort(danhSach, n);
  } else if (choice == 2) {
    printf("--------------------Quick Sort-----------------------\n");
    sort(danhSach, n);
  } else if (choice == 3) {
    printf("--------------------Sap xep MSSV----------------------\n");
    bubblesort_MSSV(danhSach, n);
  } else if (choice == 4) {
    printf("--------------------Sap xep Ten----------------------\n");
    bubblesort_Ten(danhSach, n);
  }

  inDanhSach(danhSach, n);
  ghiFile("data.txt", danhSach, n);

  free(danhSach);
  return 0;
}