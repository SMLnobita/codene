/*
============================================================
 DE 1: KIEU DU LIEU SINH VIEN
   - Ho ten   : toi da 20 ki tu
   - MSSV     : 10 ki tu
   - Diem     : mang 5 phan tu kieu so thuc (5 mon)
 Yeu cau:
   1. Nhap thong tin sinh vien, tim sinh vien theo MSSV,
      cap nhat lai ho ten sinh vien.
   2. Heap sort MAX de xep TANG diem trung binh.
============================================================
*/
#include <cstdio>
#include <cstring>

struct SINHVIEN {
    char hoten[21];     // 20 ki tu + '\0'
    char mssv[11];      // 10 ki tu + '\0'
    float diem[5];      // 5 mon
};

// ---- Diem trung binh 5 mon ----
float DTB(const SINHVIEN &sv) {
    float tong = 0;
    for (int i = 0; i < 5; i++) tong += sv.diem[i];
    return tong / 5;
}

// ---- Nhap 1 sinh vien tu ban phim ----
void NhapSV(SINHVIEN &sv) {
    printf("  Ho ten (toi da 20 ki tu): ");
    fgets(sv.hoten, 21, stdin);
    sv.hoten[strcspn(sv.hoten, "\n")] = '\0';   // bo ky tu xuong dong
    printf("  MSSV (10 ki tu)         : ");
    scanf("%10s", sv.mssv);
    printf("  Nhap 5 diem             : ");
    for (int i = 0; i < 5; i++) scanf("%f", &sv.diem[i]);
    getchar();                                   // bo '\n' con lai
}

// ---- Nhap danh sach n sinh vien ----
void NhapDS(SINHVIEN a[], int &n) {
    printf("So luong sinh vien: ");
    scanf("%d", &n); getchar();
    for (int i = 0; i < n; i++) {
        printf("Sinh vien thu %d:\n", i + 1);
        NhapSV(a[i]);
    }
}

// ---- Tim sinh vien theo MSSV, tra ve vi tri (-1 neu khong co) ----
int TimSV(SINHVIEN a[], int n, const char *mssv) {
    for (int i = 0; i < n; i++)
        if (strcmp(a[i].mssv, mssv) == 0) return i;
    return -1;
}

// ---- Cap nhat ho ten sinh vien tai vi tri i ----
void CapNhatTen(SINHVIEN a[], int i, const char *tenMoi) {
    strncpy(a[i].hoten, tenMoi, 20);
    a[i].hoten[20] = '\0';
}

// ---- In danh sach ----
void InDS(SINHVIEN a[], int n) {
    printf("%-12s %-22s %s\n", "MSSV", "Ho ten", "DTB");
    for (int i = 0; i < n; i++)
        printf("%-12s %-22s %.2f\n", a[i].mssv, a[i].hoten, DTB(a[i]));
}

/* ================= HEAP SORT MAX (tang dan theo DTB) ================= */
void hoanvi(SINHVIEN &a, SINHVIEN &b) { SINHVIEN t = a; a = b; b = t; }

// Hieu chinh doan a[l..r] thanh max-heap theo DTB
void heapify(SINHVIEN a[], int l, int r) {
    int i = l, j = 2 * i + 1;
    SINHVIEN x = a[l];
    while (j <= r) {
        if (j < r && DTB(a[j]) < DTB(a[j + 1])) j++;   // chon con lon hon
        if (DTB(a[j]) <= DTB(x)) break;                // da thoa heap
        a[i] = a[j];
        i = j;
        j = 2 * i + 1;
    }
    a[i] = x;
}

void HeapSort(SINHVIEN a[], int n) {
    for (int l = n / 2 - 1; l >= 0; l--)   // xay max-heap
        heapify(a, l, n - 1);
    for (int r = n - 1; r > 0; r--) {      // dua max ve cuoi -> tang dan
        hoanvi(a[0], a[r]);
        heapify(a, 0, r - 1);
    }
}

int main() {
    // Du lieu mau de chuong trinh chay duoc ngay (co the dung NhapDS de nhap tay)
    SINHVIEN a[100] = {
        {"Nguyen Van A", "2020000001", {7, 8, 6, 9, 5}},
        {"Tran Thi B",   "2020000002", {9, 9, 8, 10, 9}},
        {"Le Van C",     "2020000003", {5, 6, 4, 7, 5}},
        {"Pham Thi D",   "2020000004", {8, 7, 9, 6, 8}},
    };
    int n = 4;

    printf("DANH SACH BAN DAU:\n"); InDS(a, n);

    // Tim & cap nhat ten
    int vt = TimSV(a, n, "2020000003");
    if (vt != -1) {
        printf("\nTim thay MSSV 2020000003 -> cap nhat ten thanh \"Le Van Cuong\"\n");
        CapNhatTen(a, vt, "Le Van Cuong");
    }

    HeapSort(a, n);
    printf("\nSAU HEAP SORT MAX (tang theo DTB):\n"); InDS(a, n);
    return 0;
}
