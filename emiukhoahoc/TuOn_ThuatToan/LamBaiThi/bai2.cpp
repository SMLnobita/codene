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
float diemTB(SINHVIEN &sv);

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
    printf(" %s - %s - %02d/%02d/%02d - %.2f\n", arr[i].mssv, arr[i].hoten,
           arr[i].ns.ngay, arr[i].ns.thang, arr[i].ns.nam, diemTB(arr[i]));
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

float diemTB(SINHVIEN &sv) {
  float sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += sv.diem[0];
  }
  return sum / 5;
}

void InsertionSort(SINHVIEN *arr, int n) {
  for (int i = 1; i < n; i++) {
    SINHVIEN x = arr[i];
    int pos = i - 1;
    while (pos >= 0 && diemTB(arr[pos]) > diemTB(x)) {
      arr[pos + 1] = arr[pos];
      pos--;
    }
    arr[pos + 1] = x;
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
  SINHVIEN arr[100];
  int n = DocFile("input.txt", arr);
  InsertionSort(arr, n);
  inDS(arr, n);

  return 0;
}