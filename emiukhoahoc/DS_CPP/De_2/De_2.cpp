/*
============================================================
 DE 2: KIEU DU LIEU SINH VIEN
   - Ho ten: toi da 20 ki tu | MSSV: 10 ki tu | 5 diem so thuc
 Yeu cau:
   1. Nhap, tim theo MSSV, cap nhat ho ten.
   2. MERGE SORT de xep TANG diem trung binh.
============================================================
*/
#include <cstdio>
#include <cstring>

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

void NhapSV(SINHVIEN &sv) {
    printf("  Ho ten: "); fgets(sv.hoten, 21, stdin);
    sv.hoten[strcspn(sv.hoten, "\n")] = '\0';
    printf("  MSSV  : "); scanf("%10s", sv.mssv);
    printf("  5 diem: ");
    for (int i = 0; i < 5; i++) scanf("%f", &sv.diem[i]);
    getchar();
}

void NhapDS(SINHVIEN a[], int &n) {
    printf("So luong sinh vien: "); scanf("%d", &n); getchar();
    for (int i = 0; i < n; i++) { printf("SV %d:\n", i + 1); NhapSV(a[i]); }
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

/* ================= MERGE SORT (tang dan theo DTB) ================= */
void Merge(SINHVIEN a[], int left, int mid, int right) {
    int nb = mid - left + 1, nc = right - mid;
    SINHVIEN *b = new SINHVIEN[nb], *c = new SINHVIEN[nc];
    for (int i = 0; i < nb; i++) b[i] = a[left + i];
    for (int i = 0; i < nc; i++) c[i] = a[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < nb && j < nc)                       // tron: nho hon truoc
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
    SINHVIEN a[100] = {
        {"Nguyen Van A", "2020000001", {7, 8, 6, 9, 5}},
        {"Tran Thi B",   "2020000002", {9, 9, 8, 10, 9}},
        {"Le Van C",     "2020000003", {5, 6, 4, 7, 5}},
        {"Pham Thi D",   "2020000004", {8, 7, 9, 6, 8}},
    };
    int n = 4;

    printf("DANH SACH BAN DAU:\n"); InDS(a, n);

    int vt = TimSV(a, n, "2020000002");
    if (vt != -1) {
        printf("\nTim thay MSSV 2020000002 -> cap nhat ten \"Tran Thi Bich\"\n");
        CapNhatTen(a, vt, "Tran Thi Bich");
    }

    MergeSort(a, 0, n - 1);
    printf("\nSAU MERGE SORT (tang theo DTB):\n"); InDS(a, n);
    return 0;
}
