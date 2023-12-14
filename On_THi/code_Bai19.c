#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
    int tuSo;   // Tử số
    int mauSo; // Mẫu số
} PhanSo;

typedef struct {
    int phanNguyen;    // Phần nguyên
    PhanSo phanPhanSo;  // Phần phân số
} HonSo;

// Hàm tối giản phân số
PhanSo toiGianPhanSo(PhanSo f) {
    int gcd = 1;
    int min = f.tuSo < f.mauSo ? f.tuSo : f.mauSo;

    for (int i = 2; i <= min; i++) {
        if (f.tuSo % i == 0 && f.mauSo % i == 0) {
            gcd = i;
        }
    }

    f.tuSo /= gcd;
    f.mauSo /= gcd;
    return f;
}

// Hàm chuyển hỗn số sang phân số
PhanSo honSoSangPhanSo(HonSo hs) {
    PhanSo result;
    result.tuSo = hs.phanNguyen * hs.phanPhanSo.mauSo + hs.phanPhanSo.tuSo;
    result.mauSo = hs.phanPhanSo.mauSo;
    return toiGianPhanSo(result);
}

// Hàm cộng hai phân số
PhanSo congPhanSo(PhanSo f1, PhanSo f2) {
    PhanSo result;
    result.tuSo = f1.tuSo * f2.mauSo + f2.tuSo * f1.mauSo;
    result.mauSo = f1.mauSo * f2.mauSo;
    return toiGianPhanSo(result);
}

// Hàm nhân hai phân số
PhanSo nhanPhanSo(PhanSo f1, PhanSo f2) {
    PhanSo result;
    result.tuSo = f1.tuSo * f2.tuSo;
    result.mauSo = f1.mauSo * f2.mauSo;
    return toiGianPhanSo(result);
}

// Hàm in phân số
void inPhanSo(PhanSo f) {
    printf("%d/%d\n", f.tuSo, f.mauSo);
}

// Hàm nhập hỗn số từ người dùng
HonSo nhapHonSo() {
    HonSo hs;
    printf("Nhap phan nguyen cua hon so: ");
    scanf("%d", &hs.phanNguyen);
    printf("Nhap tu so cua phan phan so: ");
    scanf("%d", &hs.phanPhanSo.tuSo);
    printf("Nhap mau so cua phan phan so: ");
    scanf("%d", &hs.phanPhanSo.mauSo);
    return hs;
}

int main() {
    printf("Nhap hon so thu nhat:\n");
    HonSo hs1 = nhapHonSo(); // Nhập hỗn số thứ nhất

    printf("Nhap hon so thu hai:\n");
    HonSo hs2 = nhapHonSo(); // Nhập hỗn số thứ hai

    PhanSo f1 = honSoSangPhanSo(hs1);
    PhanSo f2 = honSoSangPhanSo(hs2);

    printf("Phan so thu nhat sau khi chuyen doi: ");
    inPhanSo(f1);
    printf("Phan so thu hai sau khi chuyen doi: ");
    inPhanSo(f2);

    PhanSo tong = congPhanSo(f1, f2);
    PhanSo tich = nhanPhanSo(f1, f2);

    printf("Tong hai hon so: ");
    inPhanSo(tong);
    printf("Tich hai hon so: ");
    inPhanSo(tich);

    return 0;
}
