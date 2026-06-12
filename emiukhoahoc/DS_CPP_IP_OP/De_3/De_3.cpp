/*
============================================================
 DE 3 (C++) + FILE I/O: KIEU DU LIEU SINH VIEN
   1. Doc tu input.txt, tim theo MSSV, cap nhat ho ten.
   2. RADIX SORT de xep TANG ma sinh vien (10 chu so), ghi output.txt.
 Format file: Ho ten, MSSV, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_SV 100
#define LEN_MSSV 10

struct SINHVIEN {
    char hoten[21];
    char mssv[11];
    float diem[5];
};

float DTB(const SINHVIEN &sv) {
    float tong = 0;
    for (int i = 0; i < 5; i++) tong += sv.diem[i];
    return tong / 5;
}

// ---- 1. Doc sinh vien tu input.txt bang fscanf, tra ve so luong ----
//   %[^,] : doc ky tu den khi gap dau phay (ho ten co the co khoang trang)
//   dau cach dau format tu dong bo qua khoang trang/xuong dong
//   moi dong khop du 7 truong (ho ten, MSSV, 5 diem) thi fscanf tra ve 7
int DocFile(const char *tenFile, SINHVIEN a[]) {
    FILE *fi = fopen(tenFile, "rt");
    if (fi == NULL) { printf("Khong mo duoc %s!\n", tenFile); return 0; }
    int n = 0;
    while (n < MAX_SV &&
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
    for (int i = 0; i < n; i++) {
        fprintf(fo, "%s, %s", a[i].hoten, a[i].mssv);
        for (int j = 0; j < 5; j++) fprintf(fo, ", %g", a[i].diem[j]);
        fprintf(fo, "\n");
    }
    fclose(fo);
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
    printf("%-22s %-12s %s\n", "Ho ten", "MSSV", "DTB");
    for (int i = 0; i < n; i++)
        printf("%-22s %-12s %.2f\n", a[i].hoten, a[i].mssv, DTB(a[i]));
}

/* ================= RADIX SORT theo MSSV (chuoi 10 chu so) ================= */
void RadixSort(SINHVIEN a[], int n) {
    SINHVIEN *tmp = new SINHVIEN[n];
    int count[10];
    for (int pos = LEN_MSSV - 1; pos >= 0; pos--) {
        for (int d = 0; d < 10; d++) count[d] = 0;
        for (int i = 0; i < n; i++)
            count[a[i].mssv[pos] - '0']++;
        for (int d = 1; d < 10; d++)
            count[d] += count[d - 1];
        for (int i = n - 1; i >= 0; i--) {
            int d = a[i].mssv[pos] - '0';
            tmp[--count[d]] = a[i];
        }
        for (int i = 0; i < n; i++) a[i] = tmp[i];
    }
    delete[] tmp;
}

int main() {
    SINHVIEN a[MAX_SV];
    int n = DocFile("input.txt", a);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt:\n"); InDS(a, n);

    int vt = TimSV(a, n, "2020000305");
    if (vt != -1) {
        printf("\nTim thay MSSV 2020000305 -> cap nhat ten \"Le Van Cuong\"\n");
        CapNhatTen(a, vt, "Le Van Cuong");
    }

    RadixSort(a, n);
    printf("\nSAU RADIX SORT (tang theo MSSV):\n"); InDS(a, n);

    GhiFile("output.txt", a, n);
    printf("\nDa ghi ket qua vao output.txt\n");
    return 0;
}
