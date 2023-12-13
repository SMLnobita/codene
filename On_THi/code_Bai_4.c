#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

typedef struct {
    int tuSo;
    int mauSo;
} PhanSo;

// Hàm tìm ước số chung lớn nhất
int UCLN(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Hàm nhập phân số
void nhapPhanSo(PhanSo* ps) {
    printf("Nhap tu so: ");
    scanf("%d", &ps->tuSo);
    printf("Nhap mau so (khac 0): ");
    scanf("%d", &ps->mauSo);
    while (ps->mauSo == 0) {
        printf("Mau so phai khac 0. Nhap lai mau so: ");
        scanf("%d", &ps->mauSo);
    }
}

// Hàm rút gọn phân số
void rutGon(PhanSo* ps) {
    int ucln = UCLN(abs(ps->tuSo), abs(ps->mauSo));
    ps->tuSo /= ucln;
    ps->mauSo /= ucln;
}

// Hàm cộng hai phân số
PhanSo cong(PhanSo ps1, PhanSo ps2) {
    PhanSo tong;
    tong.tuSo = ps1.tuSo * ps2.mauSo + ps2.tuSo * ps1.mauSo;
    tong.mauSo = ps1.mauSo * ps2.mauSo;
    rutGon(&tong);
    return tong;
}

// Hàm trừ hai phân số
PhanSo tru(PhanSo ps1, PhanSo ps2) {
    PhanSo hieu;
    hieu.tuSo = ps1.tuSo * ps2.mauSo - ps2.tuSo * ps1.mauSo;
    hieu.mauSo = ps1.mauSo * ps2.mauSo;
    rutGon(&hieu);
    return hieu;
}

// Hàm nhân hai phân số
PhanSo nhan(PhanSo ps1, PhanSo ps2) {
    PhanSo tich;
    tich.tuSo = ps1.tuSo * ps2.tuSo;
    tich.mauSo = ps1.mauSo * ps2.mauSo;
    rutGon(&tich);
    return tich;
}

// Hàm chia hai phân số
PhanSo chia(PhanSo ps1, PhanSo ps2) {
    PhanSo thuong;
    thuong.tuSo = ps1.tuSo * ps2.mauSo;
    thuong.mauSo = ps1.mauSo * ps2.tuSo;
    rutGon(&thuong);
    return thuong;
}

// Hàm in phân số
void inPhanSo(PhanSo ps) {
    printf("%d/%d\n", ps.tuSo, ps.mauSo);
}

// Hàm so sánh hai phân số
void soSanh(PhanSo ps1, PhanSo ps2) {
    double gt1 = (double)ps1.tuSo / ps1.mauSo;
    double gt2 = (double)ps2.tuSo / ps2.mauSo;
    if (gt1 < gt2) {
        printf("Phan so %d/%d nho hon phan so %d/%d\n", ps1.tuSo, ps1.mauSo, ps2.tuSo, ps2.mauSo);
    }
    else if (gt1 > gt2) {
        printf("Phan so %d/%d lon hon phan so %d/%d\n", ps1.tuSo, ps1.mauSo, ps2.tuSo, ps2.mauSo);
    }
    else {
        printf("Hai phan so bang nhau\n");
    }
}

int main() {
    PhanSo ps1, ps2;

    printf("Nhap phan so 1:\n");
    nhapPhanSo(&ps1);
    printf("Nhap phan so 2:\n");
    nhapPhanSo(&ps2);

    // Rút gọn phân số
    rutGon(&ps1);
    rutGon(&ps2);
    printf("Phan so 1 sau khi rut gon: ");
    inPhanSo(ps1);
    printf("Phan so 2 sau khi rut gon: ");
    inPhanSo(ps2);

    // Các phép toán
    PhanSo tong = cong(ps1, ps2);
    printf("Tong hai phan so: ");
    inPhanSo(tong);

    PhanSo hieu = tru(ps1, ps2);
    printf("Hieu hai phan so: ");
    inPhanSo(hieu);

    PhanSo tich = nhan(ps1, ps2);
    printf("Tich hai phan so: ");
    inPhanSo(tich);

    PhanSo thuong = chia(ps1, ps2);
    printf("Thuong hai phan so: ");
    inPhanSo(thuong);

    // So sánh hai phân số
    soSanh(ps1, ps2);

    return 0;
}
