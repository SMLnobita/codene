/*
============================================================
 DE 1 (C++) + FILE I/O: KIEU DU LIEU SINH VIEN
   - Ho ten: toi da 20 ki tu | MSSV: 10 ki tu | 5 diem so thuc
 Yeu cau:
   1. Nhap (DOC TU input.txt), tim theo MSSV, cap nhat ho ten.
   2. HEAP SORT MAX de xep TANG diem trung binh, ghi ra output.txt.
 Format file (moi dong 1 sinh vien):
   Ho ten, MSSV, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAX_SV 100

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
//   dau cach dau format ( "% ..." ) tu dong bo qua khoang trang/xuong dong
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

// ---- Ghi danh sach ra output.txt (dung format input) ----
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

/* ================= HEAP SORT MAX (tang dan theo DTB) ================= */
void hoanvi(SINHVIEN &a, SINHVIEN &b) { SINHVIEN t = a; a = b; b = t; }

void heapify(SINHVIEN a[], int l, int r) {
    int i = l, j = 2 * i + 1;
    SINHVIEN x = a[l];
    while (j <= r) {
        if (j < r && DTB(a[j]) < DTB(a[j + 1])) j++;
        if (DTB(a[j]) <= DTB(x)) break;
        a[i] = a[j];
        i = j;
        j = 2 * i + 1;
    }
    a[i] = x;
}

void HeapSort(SINHVIEN a[], int n) {
    for (int l = n / 2 - 1; l >= 0; l--)
        heapify(a, l, n - 1);
    for (int r = n - 1; r > 0; r--) {
        hoanvi(a[0], a[r]);
        heapify(a, 0, r - 1);
    }
}

int main() {
    SINHVIEN a[MAX_SV];
    int n = DocFile("input.txt", a);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt:\n"); InDS(a, n);

    int vt = TimSV(a, n, "2020000003");
    if (vt != -1) {
        printf("\nTim thay MSSV 2020000003 -> cap nhat ten \"Le Van Cuong\"\n");
        CapNhatTen(a, vt, "Le Van Cuong");
    }

    HeapSort(a, n);
    printf("\nSAU HEAP SORT MAX (tang theo DTB):\n"); InDS(a, n);

    GhiFile("output.txt", a, n);
    printf("\nDa ghi ket qua vao output.txt\n");
    return 0;
}
