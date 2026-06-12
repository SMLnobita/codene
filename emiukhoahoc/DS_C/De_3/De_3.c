/*
============================================================
 DE 3 (C): KIEU DU LIEU SINH VIEN
   - Ho ten: toi da 20 ki tu | MSSV: 10 ki tu SO | 5 diem so thuc
 Yeu cau:
   1. Nhap, tim theo MSSV, cap nhat ho ten.
   2. RADIX SORT de xep TANG ma sinh vien (10 chu so).
============================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN_MSSV 10

typedef struct {
    char hoten[21];
    char mssv[11];      /* 10 chu so + '\0' */
    float diem[5];
} SINHVIEN;

float DTB(SINHVIEN sv) {
    float tong = 0;
    for (int i = 0; i < 5; i++) tong += sv.diem[i];
    return tong / 5;
}

void NhapSV(SINHVIEN *sv) {
    printf("  Ho ten: "); fgets(sv->hoten, 21, stdin);
    sv->hoten[strcspn(sv->hoten, "\n")] = '\0';
    printf("  MSSV (10 chu so): "); scanf("%10s", sv->mssv);
    printf("  5 diem: ");
    for (int i = 0; i < 5; i++) scanf("%f", &sv->diem[i]);
    getchar();
}

void NhapDS(SINHVIEN a[], int *n) {
    printf("So luong sinh vien: "); scanf("%d", n); getchar();
    for (int i = 0; i < *n; i++) { printf("SV %d:\n", i + 1); NhapSV(&a[i]); }
}

int TimSV(SINHVIEN a[], int n, const char *mssv) {
    for (int i = 0; i < n; i++)
        if (strcmp(a[i].mssv, mssv) == 0) return i;
    return -1;
}

void CapNhatTen(SINHVIEN a[], int i, const char *tenMoi) {
    strncpy(a[i].hoten, tenMoi, 20);
    a[i].hoten[20] = '\0';
}

void InDS(SINHVIEN a[], int n) {
    printf("%-12s %-22s %s\n", "MSSV", "Ho ten", "DTB");
    for (int i = 0; i < n; i++)
        printf("%-12s %-22s %.2f\n", a[i].mssv, a[i].hoten, DTB(a[i]));
}

/* ================= RADIX SORT theo MSSV (chuoi 10 chu so) =================
   Xu ly tung vi tri ki tu tu PHAI sang TRAI (LSD), on dinh -> tang dan. */
void RadixSort(SINHVIEN a[], int n) {
    SINHVIEN *tmp = (SINHVIEN*)malloc(n * sizeof(SINHVIEN));
    int count[10];
    for (int pos = LEN_MSSV - 1; pos >= 0; pos--) {
        for (int d = 0; d < 10; d++) count[d] = 0;
        for (int i = 0; i < n; i++)
            count[a[i].mssv[pos] - '0']++;
        for (int d = 1; d < 10; d++)
            count[d] += count[d - 1];
        for (int i = n - 1; i >= 0; i--) {     /* duyet nguoc -> on dinh */
            int d = a[i].mssv[pos] - '0';
            tmp[--count[d]] = a[i];
        }
        for (int i = 0; i < n; i++) a[i] = tmp[i];
    }
    free(tmp);
}

int main(void) {
    SINHVIEN a[100] = {
        {"Nguyen Van A", "2020000089", {7, 8, 6, 9, 5}},
        {"Tran Thi B",   "2020000012", {9, 9, 8, 10, 9}},
        {"Le Van C",     "2020000305", {5, 6, 4, 7, 5}},
        {"Pham Thi D",   "2020000004", {8, 7, 9, 6, 8}},
    };
    int n = 4;

    printf("DANH SACH BAN DAU:\n"); InDS(a, n);

    int vt = TimSV(a, n, "2020000305");
    if (vt != -1) {
        printf("\nTim thay MSSV 2020000305 -> cap nhat ten \"Le Van Cuong\"\n");
        CapNhatTen(a, vt, "Le Van Cuong");
    }

    RadixSort(a, n);
    printf("\nSAU RADIX SORT (tang theo MSSV):\n"); InDS(a, n);
    return 0;
}
