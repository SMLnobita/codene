/*
============================================================
 DE 2 (C++) + FILE I/O: KIEU DU LIEU SINH VIEN
   1. Doc tu input.txt, tim theo MSSV, cap nhat ho ten.
   2. MERGE SORT de xep TANG diem trung binh, ghi ra output.txt.
 Format file: Ho ten, MSSV, d1, d2, d3, d4, d5
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

/* ================= MERGE SORT (tang dan theo DTB) ================= */
void Merge(SINHVIEN a[], int left, int mid, int right) {
    int nb = mid - left + 1, nc = right - mid;
    SINHVIEN *b = new SINHVIEN[nb], *c = new SINHVIEN[nc];
    for (int i = 0; i < nb; i++) b[i] = a[left + i];
    for (int i = 0; i < nc; i++) c[i] = a[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < nb && j < nc)
        a[k++] = (DTB(b[i]) <= DTB(c[j])) ? b[i++] : c[j++];
    while (i < nb) a[k++] = b[i++];
    while (j < nc) a[k++] = c[j++];
    delete[] b; delete[] c;
}

void MergeSort(SINHVIEN a[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);
    MergeSort(a, mid + 1, right);
    Merge(a, left, mid, right);
}

int main() {
    SINHVIEN a[MAX_SV];
    int n = DocFile("input.txt", a);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt:\n"); InDS(a, n);

    int vt = TimSV(a, n, "2020000023");
    if (vt != -1) {
        printf("\nTim thay MSSV 2020000023 -> cap nhat ten \"Nguyen Van Bich\"\n");
        CapNhatTen(a, vt, "Nguyen Van Bich");
    }

    MergeSort(a, 0, n - 1);
    printf("\nSAU MERGE SORT (tang theo DTB):\n"); InDS(a, n);

    GhiFile("output.txt", a, n);
    printf("\nDa ghi ket qua vao output.txt\n");
    return 0;
}
