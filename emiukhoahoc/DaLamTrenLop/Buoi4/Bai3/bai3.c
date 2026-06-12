#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int ngay;
  int thang;
  int nam;
} ngaySinh;

typedef struct {
  char mssv[20];
  char name[50];
  float diemTB;
  ngaySinh ngaysinh;
} sinhVien;

int demPhanTu(const char *tenfile) {
  FILE *f = fopen(tenfile, "rt");
  char mssv[20], name[40];
  float diemTB;
  int ngay, thang, nam;
  int dem = 0;
  while (fscanf(f, " %19[^,],%49[^,],%f,%d,%d,%d", mssv, name, &diemTB, &ngay,
                &thang, &nam) == 6) {
    dem++;
  }
  fclose(f);
  return dem;
}

void readFile(const char *tenfile, sinhVien *arr) {
  FILE *fi = fopen(tenfile, "rt");
  int dem = 0;
  while (fscanf(fi, " %19[^,],%49[^,],%f,%d,%d,%d", arr[dem].mssv,
                arr[dem].name, &arr[dem].diemTB, &arr[dem].ngaysinh.ngay,
                &arr[dem].ngaysinh.thang, &arr[dem].ngaysinh.nam) == 6) {
    dem++;
  }
  fclose(fi);
}

void inMangHinh(sinhVien *arr, int n) {
  printf("%-14s %-30s %-14s %s", "MSSV", "Ten", "DiemTB", "NgayThangNam");
  printf("\n---------------------------------------------------------------\n");
  for (int i = 0; i < n; i++) {
    printf("%-14s %-30s %-14.2f %02d/%02d/%02d\n", arr[i].mssv, arr[i].name,
           arr[i].diemTB, arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang,
           arr[i].ngaysinh.nam);
  }
  printf("---------------------------------------------------------------\n");
}

void writeFile(const char *tenfile, sinhVien *arr, int n) {
  FILE *fo = fopen(tenfile, "wt");
  for (int i = 0; i < n; i++) {
    fprintf(fo, "%s,%s,%.2f,%d,%d,%d\n", arr[i].mssv, arr[i].name,
            arr[i].diemTB, arr[i].ngaysinh.ngay, arr[i].ngaysinh.thang,
            arr[i].ngaysinh.nam);
  }
  fclose(fo);
}

// ==================== Heap Sort giam theo MSSV ====================
void hoanvi(sinhVien *a, sinhVien *b) {
  sinhVien temp = *a;
  *a = *b;
  *b = temp;
}

void heapify(sinhVien *arr, int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  if (left < n && strcmp(arr[left].mssv, arr[largest].mssv) < 0)
    largest = left;
  if (right < n && strcmp(arr[right].mssv, arr[largest].mssv) < 0)
    largest = right;
  if (largest != i) {
    hoanvi(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}

void buildHeap(sinhVien *arr, int n) {
  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify(arr, n, i);
  }
}

void heapSort(sinhVien *arr, int n) {
  buildHeap(arr, n);
  for (int i = n - 1; i > 0; i--) {
    hoanvi(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }
}

// ==================== Shell Sort tang theo DiemTB ====================
void ShellSort(sinhVien *arr, int n, int *h, int k) {
  int step, i, pos;
  sinhVien x;
  int len;

  for (step = k - 1; step >= 0; step--) {
    len = h[step];
    for (i = len; i < n; i++) {
      x = arr[i];
      pos = i - len;
      while (pos >= 0 && x.diemTB < arr[pos].diemTB) {
        arr[pos + len] = arr[pos];
        pos = pos - len;
      }
      arr[pos + len] = x;
    }
  }
}

// ==================== Radix Sort tang theo DiemTB ====================
int getMaxInt(int arr[], int n) {
  int mx = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > mx)
      mx = arr[i];
  return mx;
}

void countSortDiem(sinhVien arr[], int keys[], int n, int exp) {
  // ket qua mang
  sinhVien *output = (sinhVien *)malloc(n * sizeof(sinhVien));
  // key tuong ung
  int *outKeys = (int *)malloc(n * sizeof(int));
  // dem so lan digital 0-9
  int count[10] = {0};

  for (int i = 0; i < n; i++)
    count[(keys[i] / exp) % 10]++;
  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];
  for (int i = n - 1; i >= 0; i--) {
    int idx = count[(keys[i] / exp) % 10] - 1;
    output[idx] = arr[i];
    outKeys[idx] = keys[i];
    count[(keys[i] / exp) % 10]--;
  }
  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
    keys[i] = outKeys[i];
  }
  free(output);
  free(outKeys);
}

void RadixSortDiem(sinhVien arr[], int n) {
  int *keys = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++)
    keys[i] = (int)(arr[i].diemTB * 100 + 0.5f);
  int m = getMaxInt(keys, n);
  for (int exp = 1; m / exp > 0; exp *= 10)
    countSortDiem(arr, keys, n, exp);
  free(keys);
}

// ==================== Radix Sort tang theo MSSV ====================
void countSortMSSV(sinhVien arr[], int n, int pos) {
  sinhVien *output = (sinhVien *)malloc(n * sizeof(sinhVien));
  int count[10] = {0};

  for (int i = 0; i < n; i++) {
    int len = strlen(arr[i].mssv);
    int idx = (pos < len) ? (arr[i].mssv[len - 1 - pos] - '0') : 0;
    count[idx]++;
  }
  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];
  for (int i = n - 1; i >= 0; i--) {
    int len = strlen(arr[i].mssv);
    int idx = (pos < len) ? (arr[i].mssv[len - 1 - pos] - '0') : 0;
    output[count[idx] - 1] = arr[i];
    count[idx]--;
  }
  for (int i = 0; i < n; i++)
    arr[i] = output[i];
  free(output);
}

void RadixSortMSSV(sinhVien arr[], int n) {
  int maxLen = 0;
  for (int i = 0; i < n; i++) {
    int len = strlen(arr[i].mssv);
    if (len > maxLen)
      maxLen = len;
  }
  for (int pos = 0; pos < maxLen; pos++)
    countSortMSSV(arr, n, pos);
}

// ==================== Xac dinh duong chay tang theo DiemTB
// ====================
void xacDinhDuongChay(sinhVien *arr, int n) {
  printf("Cac duong chay tang theo DiemTB:\n");
  printf("---------------------------------------------------------------\n");
  int i = 0, run = 1;
  while (i < n) {
    int j = i;
    while (j + 1 < n && arr[j + 1].diemTB >= arr[j].diemTB)
      j++;
    printf("Duong chay %d [%d -> %d]: ", run++, i + 1, j + 1);
    for (int k = i; k <= j; k++)
      printf("%.2f ", arr[k].diemTB);
    printf("\n");
    i = j + 1;
  }
  printf("---------------------------------------------------------------\n");
}

// ==================== Natural Merge Sort tang theo DiemTB ====================
void mergeRuns(sinhVien *arr, sinhVien *temp, int left, int mid, int right) {
  int i = left, j = mid + 1, k = left;
  while (i <= mid && j <= right) {
    if (arr[i].diemTB <= arr[j].diemTB)
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

void naturalMergeSort(sinhVien *arr, int n) {
  sinhVien *temp = (sinhVien *)malloc(n * sizeof(sinhVien));
  int sorted = 0;
  while (!sorted) {
    sorted = 1;
    int i = 0;
    while (i < n) {
      int mid = i;
      while (mid + 1 < n && arr[mid + 1].diemTB >= arr[mid].diemTB)
        mid++;
      if (mid >= n - 1) {
        i = mid + 1;
        continue;
      }
      int right = mid + 1;
      while (right + 1 < n && arr[right + 1].diemTB >= arr[right].diemTB)
        right++;
      mergeRuns(arr, temp, i, mid, right);
      sorted = 0;
      i = right + 1;
    }
  }
  free(temp);
}

// ==================== Main ====================
int main() {
  char choice;
  int n = demPhanTu("data.txt");
  if (n < 5) {
    printf("Vui long them du thong tin >= 5");
    return 0;
  }

  sinhVien *arr = (sinhVien *)malloc(n * sizeof(sinhVien));
  readFile("data.txt", arr);

  int k = 0;
  int temp = n;
  while (temp > 1) {
    temp = (temp - 1) / 2;
    k++;
  }

  int *h = (int *)malloc(k * sizeof(int));
  h[0] = 1;
  for (int i = 1; i < k; i++)
    h[i] = h[i - 1] * 2 + 1;

  while (1) {
    do {
      printf("1: Heap Sort       - sap xep giam theo MSSV\n");
      printf("2: Shell Sort      - sap xep tang theo Diem Trung Binh\n");
      printf("3: Radix Sort      - sap xep tang theo Diem Trung Binh\n");
      printf("4: Radix Sort      - sap xep tang theo MSSV\n");
      printf("5: Duong chay tang - xac dinh theo Diem Trung Binh\n");
      printf("6: Natural Merge   - sap xep tang theo Diem Trung Binh\n");
      printf("q: Nhan q de thoat\n");
      printf("Nhap lua chon: ");
      scanf(" %c", &choice);
      system("cls");
    } while (!strchr("123456q", choice));

    if (choice == '1') {
      printf("--------------------------Heap Sort--------------------------\n");
      heapSort(arr, n);
      inMangHinh(arr, n);
      writeFile("data.txt", arr, n);
    } else if (choice == '2') {
      printf("-------------------------Shell Sort--------------------------\n");
      ShellSort(arr, n, h, k);
      inMangHinh(arr, n);
      writeFile("data.txt", arr, n);
    } else if (choice == '3') {
      printf("----------------------Radix Sort DiemTB---------------------\n");
      RadixSortDiem(arr, n);
      inMangHinh(arr, n);
      writeFile("data.txt", arr, n);
    } else if (choice == '4') {
      printf("----------------------Radix Sort MSSV-----------------------\n");
      RadixSortMSSV(arr, n);
      inMangHinh(arr, n);
      writeFile("data.txt", arr, n);
    } else if (choice == '5') {
      printf("---------------------Duong chay tang------------------------\n");
      xacDinhDuongChay(arr, n);
    } else if (choice == '6') {
      printf("--------------------Natural Merge Sort-----------------------\n");
      naturalMergeSort(arr, n);
      inMangHinh(arr, n);
      writeFile("data.txt", arr, n);
    } else if (choice == 'q') {
      break;
    }
  }

  free(h);
  free(arr);
  return 0;
}