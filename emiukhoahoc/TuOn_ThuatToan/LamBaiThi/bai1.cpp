#include <cstdio>
#include <cstring>
#include <iostream>

#define MAX 100

using namespace std;

struct NGAYSINH {
  int ngay, thang, nam;
};

struct SINHVIEN {
  char hoten[21];
  char mssv[11];
  NGAYSINH ns;
  float diem[5];
};

int DocFile(const char *tenFile, SINHVIEN *arr) {
  FILE *fi = fopen(tenFile, "rt");
  int n = 0;
  while (fscanf(fi, " %10[^,], %20[^,], %d/%d/%d, %f, %f, %f, %f, %f",
                arr[n].mssv, arr[n].hoten, &arr[n].ns.ngay, &arr[n].ns.thang,
                &arr[n].ns.nam, &arr[n].diem[0], &arr[n].diem[1],
                &arr[n].diem[2], &arr[n].diem[3], &arr[n].diem[4]) == 10) {
    n++;
  }
  fclose(fi);
  return n;
}

void GhiFile(const char *tenFile, SINHVIEN *arr, int n) {
  FILE *fo = fopen(tenFile, "wt");
  for (int i = 0; i < n; i++) {
    fprintf(fo, " %s, %s, %02d/%02d/%02d, %.2f, %.2f, %.2f, %.2f, %.2f\n",
            arr[i].mssv, arr[i].hoten, arr[i].ns.ngay, arr[i].ns.thang,
            arr[i].ns.nam, arr[i].diem[0], arr[i].diem[1], arr[i].diem[2],
            arr[i].diem[3], arr[i].diem[4]);
  }
  fclose(fo);
}

void inDS(SINHVIEN *arr, int n) {
  for (int i = 0; i < n; i++) {
    printf(" %s - %s - %02d/%02d/%02d - %.2f, %.2f, %.2f, %.2f, %.2f\n",
           arr[i].mssv, arr[i].hoten, arr[i].ns.ngay, arr[i].ns.thang,
           arr[i].ns.nam, arr[i].diem[0], arr[i].diem[1], arr[i].diem[2],
           arr[i].diem[3], arr[i].diem[4]);
  }
}

long NgayThangNamSinh(SINHVIEN &sv) {
  return (long)sv.ns.nam * 10000 + sv.ns.thang * 100 + sv.ns.ngay;
}

void BubbleSort_Day(SINHVIEN *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    bool doi = false;
    for (int j = n - 1; j > 0; j--) {
      if (NgayThangNamSinh(arr[j]) > NgayThangNamSinh(arr[j - 1])) {
        swap(arr[j], arr[j - 1]);
        doi = true;
      }
    }
    if (!doi)
      break;
  }
}

void InterchangeSort(SINHVIEN *arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = i + 1; j < n; j++) {
      if (strcmp(arr[i].mssv, arr[j].mssv) > 0) {
        swap(arr[i], arr[j]);
      }
    }
  }
}

int BinarySearch(SINHVIEN *arr, int n, const char *mssv) {
  int left = 0, right = n - 1;
  while (left <= right) {
    int mid = (left + right) / 2;
    int c = strcmp(arr[mid].mssv, mssv);
    if (c == 0)
      return mid;
    if (c > 0)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return -1;
}

int main() {
  SINHVIEN arr[MAX];
  int choicee;
  int n = DocFile("input.txt", arr);
  printf("Danh sach Sinh Vien\n");
  inDS(arr, n);

  printf("\nDanh sach sau khi sap xep\n");
  BubbleSort_Day(arr, n);
  inDS(arr, n);
  GhiFile("output.txt", arr, n);

  InterchangeSort(arr, n);
  const char *timKiem = "23200000";
  choicee = BinarySearch(arr, n, timKiem);

  if (choicee != -1) {
    printf("\nDa tiem so %s -> tai vi tri %d da cap nhap NS 24/06/2005\n",
           timKiem, choicee);
    arr[choicee].ns.ngay = 24, arr[choicee].ns.thang = 6,
    arr[choicee].ns.nam = 2005;
  } else {
    printf("\n Khong tim thay\n");
  }

  inDS(arr, n);

  return 0;
}