/*
============================================================
 DE 6 (2026): SINH VIEN (ho ten, MSSV, ngay sinh, 5 diem)
   1. Doc danh sach sinh vien tu input.txt
   2. Tim SV theo MSSV (tim tuyen tinh) de cap nhat NAM SINH
   3. MERGE SORT xep TANG theo DIEM TRUNG BINH -> ghi output.txt
 Format input.txt: Ho ten, MSSV, dd/mm/yyyy, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstring>

#define MAX 100

struct NGAYSINH { int ngay, thang, nam; };
struct SINHVIEN {
    char hoten[21];
    char mssv[11];
    NGAYSINH ns;
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
           fscanf(fi, " %20[^,], %10[^,], %d/%d/%d, %f, %f, %f, %f, %f",
                  a[n].hoten, a[n].mssv,
                  &a[n].ns.ngay, &a[n].ns.thang, &a[n].ns.nam,
                  &a[n].diem[0], &a[n].diem[1], &a[n].diem[2],
                  &a[n].diem[3], &a[n].diem[4]) == 10)
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
        printf("%s - %-18s - %02d/%02d/%04d - DTB %.2f\n",
               a[i].mssv, a[i].hoten, a[i].ns.ngay, a[i].ns.thang, a[i].ns.nam, DTB(a[i]));
}

/* ============ 2. Tim tuyen tinh theo MSSV ============ */
int TimMSSV(SINHVIEN a[], int n, const char *mssv) {
    for (int i = 0; i < n; i++)
        if (strcmp(a[i].mssv, mssv) == 0) return i;
    return -1;
}

/* ============ 3. MERGE SORT theo DTB (tang dan) ============ */
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

void MergeSortDTB(SINHVIEN a[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    MergeSortDTB(a, left, mid);
    MergeSortDTB(a, mid + 1, right);
    Merge(a, left, mid, right);
}

int main() {
    SINHVIEN a[MAX];
    int n = DocFile("input.txt", a);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt:\n"); InDS(a, n);

    const char *timMSSV = "2320000101";
    int vt = TimMSSV(a, n, timMSSV);
    if (vt != -1) {
        printf("\nTim thay %s -> cap nhat nam sinh thanh 2006\n", timMSSV);
        a[vt].ns.nam = 2006;
    } else printf("\nKhong tim thay %s\n", timMSSV);

    MergeSortDTB(a, 0, n - 1);
    printf("\nSAU MERGE SORT theo DTB (tang dan):\n"); InDS(a, n);

    GhiFile("output.txt", a, n);
    printf("\nDa ghi ket qua vao output.txt\n");
    return 0;
}
