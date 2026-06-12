/*
============================================================
 DE 7 (2026): SINH VIEN (ho ten, MSSV, ngay sinh, 5 diem)
   1. Doc danh sach sinh vien tu input.txt
   2. Tim SV theo MSSV (tim tuyen tinh) de cap nhat HO VA TEN
   3. RADIX SORT xep TANG theo MA SO SINH VIEN -> ghi output.txt
 Format input.txt: Ho ten, MSSV, dd/mm/yyyy, d1, d2, d3, d4, d5
============================================================
*/
#include <cstdio>
#include <cstring>

#define MAX 100
#define LEN_MSSV 10

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
        fprintf(fo, "%s - %s\n", a[i].mssv, a[i].hoten);
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

void CapNhatTen(SINHVIEN &sv, const char *tenMoi) {
    strncpy(sv.hoten, tenMoi, 20);
    sv.hoten[20] = '\0';
}

/* ============ 3. RADIX SORT theo MSSV (chuoi 10 chu so) ============
   Xu ly tung vi tri ki tu tu PHAI sang TRAI, on dinh -> tang dan. */
void RadixSortMSSV(SINHVIEN a[], int n) {
    SINHVIEN *tmp = new SINHVIEN[n];
    int count[10];
    for (int pos = LEN_MSSV - 1; pos >= 0; pos--) {
        for (int d = 0; d < 10; d++) count[d] = 0;
        for (int i = 0; i < n; i++) count[a[i].mssv[pos] - '0']++;
        for (int d = 1; d < 10; d++) count[d] += count[d - 1];
        for (int i = n - 1; i >= 0; i--) {
            int d = a[i].mssv[pos] - '0';
            tmp[--count[d]] = a[i];
        }
        for (int i = 0; i < n; i++) a[i] = tmp[i];
    }
    delete[] tmp;
}

int main() {
    SINHVIEN a[MAX];
    int n = DocFile("input.txt", a);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt:\n"); InDS(a, n);

    const char *timMSSV = "2320000009";
    int vt = TimMSSV(a, n, timMSSV);
    if (vt != -1) {
        printf("\nTim thay %s -> cap nhat ten thanh \"Nguyen Van Bao\"\n", timMSSV);
        CapNhatTen(a[vt], "Nguyen Van Bao");
    } else printf("\nKhong tim thay %s\n", timMSSV);

    RadixSortMSSV(a, n);
    printf("\nSAU RADIX SORT theo MSSV (tang dan):\n"); InDS(a, n);

    GhiFile("output.txt", a, n);
    printf("\nDa ghi ket qua vao output.txt\n");
    return 0;
}
