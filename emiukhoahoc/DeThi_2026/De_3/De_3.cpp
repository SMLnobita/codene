/*
============================================================
 DE 3 (2026): SINH VIEN (ho ten, MSSV, 5 diem)  [KHONG co ngay sinh]
   1. Doc danh sach sinh vien tu input.txt
   2. QUICK SORT xep TANG theo DIEM TRUNG BINH -> ghi output.txt
   3. Tim SV theo MSSV bang TIM KIEM NHI PHAN de cap nhat ho va ten
 Format input.txt: Ho ten, MSSV, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstring>

#define MAX 100

struct SINHVIEN {
    char hoten[21];
    char mssv[11];
    float diem[5];
};

float DTB(const SINHVIEN &sv) {
    float t = 0;
    for (int i = 0; i < 5; i++) t += sv.diem[i];
    return t / 5;
}

int DocFile(const char *tenFile, SINHVIEN a[]) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return 0; }
    int n = 0;
    while (n < MAX &&
           fscanf(fi, " %20[^,], %10[^,], %f, %f, %f, %f, %f",
                  a[n].hoten, a[n].mssv,
                  &a[n].diem[0], &a[n].diem[1], &a[n].diem[2],
                  &a[n].diem[3], &a[n].diem[4]) == 7)
        n++;
    fclose(fi);
    return n;
}

void GhiFile(const char *tenFile, SINHVIEN a[], int n) {
    FILE *fo = fopen(tenFile, "wt");
    if (fo == NULL) { printf("Khong mo duoc %s de ghi!\n", tenFile); return; }
    for (int i = 0; i < n; i++)
        fprintf(fo, "%s - %s - DTB %.2f\n", a[i].mssv, a[i].hoten, DTB(a[i]));
    fclose(fo);
}

void InDS(SINHVIEN a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s - %-18s - DTB %.2f\n", a[i].mssv, a[i].hoten, DTB(a[i]));
}

/* ============ 2. QUICK SORT theo DTB (tang dan) ============ */
void hoanvi(SINHVIEN &a, SINHVIEN &b) { SINHVIEN t = a; a = b; b = t; }

void QuickSortDTB(SINHVIEN a[], int left, int right) {
    if (left >= right) return;
    float x = DTB(a[(left + right) / 2]);
    int i = left, j = right;
    while (i <= j) {
        while (DTB(a[i]) < x) i++;
        while (DTB(a[j]) > x) j--;
        if (i <= j) { hoanvi(a[i], a[j]); i++; j--; }
    }
    QuickSortDTB(a, left, j);
    QuickSortDTB(a, i, right);
}

/* ============ 3. Tim kiem nhi phan theo MSSV ============ */
void SapXepTheoMSSV(SINHVIEN a[], int n) {
    for (int i = 1; i < n; i++) {
        SINHVIEN x = a[i];
        int j = i - 1;
        while (j >= 0 && strcmp(a[j].mssv, x.mssv) > 0) { a[j + 1] = a[j]; j--; }
        a[j + 1] = x;
    }
}

int TimNhiPhanMSSV(SINHVIEN a[], int n, const char *mssv) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        int c = strcmp(a[m].mssv, mssv);
        if (c == 0) return m;
        if (c < 0) l = m + 1;
        else       r = m - 1;
    }
    return -1;
}

void CapNhatTen(SINHVIEN &sv, const char *tenMoi) {
    strncpy(sv.hoten, tenMoi, 20);
    sv.hoten[20] = '\0';
}

int main() {
    SINHVIEN a[MAX];
    int n = DocFile("input.txt", a);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt:\n"); InDS(a, n);

    SapXepTheoMSSV(a, n);
    const char *timMSSV = "2320000101";
    int vt = TimNhiPhanMSSV(a, n, timMSSV);
    if (vt != -1) {
        printf("\nTim nhi phan thay %s -> cap nhat ten thanh \"Tran Van Dung\"\n", timMSSV);
        CapNhatTen(a[vt], "Tran Van Dung");
    } else printf("\nKhong tim thay %s\n", timMSSV);

    QuickSortDTB(a, 0, n - 1);
    printf("\nSAU QUICK SORT theo DTB (tang dan):\n"); InDS(a, n);

    GhiFile("output.txt", a, n);
    printf("\nDa ghi ket qua vao output.txt\n");
    return 0;
}
