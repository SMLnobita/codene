/*
============================================================
 ON TAP 1: CON TRO - QUAN LY VUNG NHO (cap phat & giai phong)
============================================================
 Kien thuc can nho:
 - Con tro la bien chua DIA CHI cua o nho khac.
 - Toan tu &  : lay dia chi cua bien.
 - Toan tu *  : truy xuat gia tri tai dia chi (deference).
 - Voi struct : dung -> de truy xuat thanh phan qua con tro.
 - Cap phat dong:
     C   : malloc / calloc  -> giai phong bang free
     C++ : new / new[]      -> giai phong bang delete / delete[]
 - Luon kiem tra NULL sau khi cap phat, gan NULL sau khi free.
 - Truyen tham tri: ham nhan BAN SAO, bien ngoai khong doi.
 - Truyen tham bien (int &a): ham thao tac TRUC TIEP tren bien.
============================================================
*/
#include <cstdio>
#include <cstdlib>

struct DIEM {
    int x, y;
};

// ----- 1. Truyen tham tri vs tham bien -----
void TruyenThamTri(int a)    { a = a * 10; }   // khong doi ben ngoai
void TruyenThamBien(int &a)  { a = a * 10; }   // doi ben ngoai

// con tro truyen tham tri: doi DUOC noi dung *d tro toi,
// nhung khong doi duoc ban than con tro ben ngoai
void ThamTriConTro(DIEM *d) {
    d->x *= 10;
    d->y *= 10;
    d = NULL; // chi doi ban sao, ben ngoai d2 van giu dia chi cu
}

// con tro truyen tham bien (DIEM*&): doi duoc ca con tro ben ngoai
void ThamBienConTro(DIEM *&d, DIEM *p) {
    d->x *= 10;
    d->y *= 10;
    d = p;    // ben ngoai d2 se tro sang p
}

int main() {
    // ----- 2. Khai bao + lay dia chi -----
    int a = 1;
    int *pa = &a;                  // pa giu dia chi cua a
    printf("Dia chi cua a : %p\n", (void*)&a);
    printf("Gia tri *pa   : %d\n", *pa);

    // ----- 3. Con tro voi struct -----
    DIEM O; O.x = 2; O.y = 3;
    DIEM *pd = &O;
    printf("Diem O: (%d, %d)\n", pd->x, pd->y);  // dung ->

    // ----- 4. Cap phat dong kieu C: malloc / calloc -----
    int n = 5;
    int *arr = (int*)malloc(n * sizeof(int));    // cap phat n int
    if (arr == NULL) {                           // LUON kiem tra
        printf("Cap phat khong thanh cong!\n");
        return 1;
    }
    for (int i = 0; i < n; i++) arr[i] = i * i;  // dung nhu mang
    printf("Mang malloc : ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    free(arr);                                   // giai phong
    arr = NULL;                                  // tranh dangling pointer

    // calloc: cap phat + khoi tao 0
    int *arr2 = (int*)calloc(n, sizeof(int));
    printf("Mang calloc : ");
    for (int i = 0; i < n; i++) printf("%d ", arr2[i]); // toan 0
    printf("\n");
    free(arr2); arr2 = NULL;

    // ----- 5. Cap phat dong kieu C++: new / delete -----
    DIEM *pDiem = new DIEM;        // 1 phan tu
    pDiem->x = 7; pDiem->y = 8;
    printf("new DIEM    : (%d, %d)\n", pDiem->x, pDiem->y);
    delete pDiem; pDiem = NULL;

    int *mang = new int[n];        // mang dong
    for (int i = 0; i < n; i++) mang[i] = i + 1;
    delete[] mang; mang = NULL;    // mang -> delete[]

    // ----- 6. Demo tham tri / tham bien -----
    int x = 1;
    TruyenThamTri(x);
    printf("x sau TruyenThamTri  = %d (khong doi)\n", x);
    TruyenThamBien(x);
    printf("x sau TruyenThamBien = %d (x10)\n", x);

    DIEM *d1 = new DIEM; d1->x = 1; d1->y = 1;
    DIEM *d2 = new DIEM; d2->x = 5; d2->y = 5;
    ThamTriConTro(d2);
    printf("d2 sau ThamTriConTro : (%d, %d)\n", d2->x, d2->y); // (50,50)
    ThamBienConTro(d2, d1);   // d2 gio tro sang d1
    printf("d2 sau ThamBienConTro: (%d, %d)\n", d2->x, d2->y); // (1,1)

    delete d1;   // d2 dang tro vao d1 nen chi delete 1 lan
    return 0;
}
