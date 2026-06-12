/*
============================================================
 DE 1 (2026): SINH VIEN (ho ten, MSSV, ngay sinh, 5 diem)
   1. Doc danh sach sinh vien tu input.txt
   2. BUBBLE SORT xep TANG theo ngay/thang/nam sinh -> ghi output.txt
   3. Tim SV theo MSSV bang TIM KIEM NHI PHAN de cap nhat ngay sinh
 Format input.txt:
   Ho ten, MSSV, dd/mm/yyyy, d1, d2, d3, d4, d5
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

// Khoa so sanh ngay sinh: nam*10000 + thang*100 + ngay (cang nho cang truoc)
long KeyNgay(const SINHVIEN &sv) {
    return (long)sv.ns.nam * 10000 + sv.ns.thang * 100 + sv.ns.ngay;
}

// ---- 1. Doc input.txt bang fscanf, tra ve so luong ----
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

// ---- Ghi output.txt: MSSV - Ho ten - dd-mm-yyyy (theo VD de) ----
void GhiFile(const char *tenFile, SINHVIEN a[], int n) {
    FILE *fo = fopen(tenFile, "wt");
    if (fo == NULL) { printf("Khong mo duoc %s de ghi!\n", tenFile); return; }
    for (int i = 0; i < n; i++)
        fprintf(fo, "%s - %s - %02d-%02d-%04d\n",
                a[i].mssv, a[i].hoten, a[i].ns.ngay, a[i].ns.thang, a[i].ns.nam);
    fclose(fo);
}

void InDS(SINHVIEN a[], int n) {
    for (int i = 0; i < n; i++)
        printf("%s - %-18s - %02d/%02d/%04d - DTB %.2f\n",
               a[i].mssv, a[i].hoten, a[i].ns.ngay, a[i].ns.thang, a[i].ns.nam, DTB(a[i]));
}

/* ============ 2. BUBBLE SORT theo ngay sinh (tang dan) ============ */
void hoanvi(SINHVIEN &a, SINHVIEN &b) { SINHVIEN t = a; a = b; b = t; }

void BubbleSortNgay(SINHVIEN a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool doi = false;
        for (int j = n - 1; j > i; j--)
            if (KeyNgay(a[j]) < KeyNgay(a[j - 1])) {
                hoanvi(a[j], a[j - 1]);
                doi = true;
            }
        if (!doi) break;
    }
}

/* ============ 3. Tim kiem nhi phan theo MSSV ============
   Dieu kien: mang phai sap xep TANG theo MSSV truoc khi tim. */
void SapXepTheoMSSV(SINHVIEN a[], int n) {     // insertion sort theo MSSV
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

int main() {
    SINHVIEN a[MAX];
    int n = DocFile("input.txt", a);
    if (n == 0) { printf("Khong co du lieu.\n"); return 1; }

    printf("DANH SACH DOC TU input.txt:\n"); InDS(a, n);

    // --- 3. Tim nhi phan theo MSSV roi cap nhat ngay sinh ---
    SapXepTheoMSSV(a, n);                          // can sap theo MSSV de tim nhi phan
    const char *timMSSV = "2320000001";
    int vt = TimNhiPhanMSSV(a, n, timMSSV);
    if (vt != -1) {
        printf("\nTim nhi phan thay %s -> cap nhat ngay sinh thanh 09/09/2005\n", timMSSV);
        a[vt].ns.ngay = 9; a[vt].ns.thang = 9; a[vt].ns.nam = 2005;
    } else printf("\nKhong tim thay %s\n", timMSSV);

    // --- 2. Bubble sort theo ngay sinh + ghi output.txt ---
    BubbleSortNgay(a, n);
    printf("\nSAU BUBBLE SORT theo ngay sinh (tang dan):\n"); InDS(a, n);

    GhiFile("output.txt", a, n);
    printf("\nDa ghi ket qua vao output.txt\n");
    return 0;
}
