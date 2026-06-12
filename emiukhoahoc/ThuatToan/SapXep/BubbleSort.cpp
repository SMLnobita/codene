/*
============================================================
 BUBBLE SORT (noi bot) - sap tang dan
 - Duyet nhieu luot, doi cho 2 phan tu ke nhau neu sai thu tu,
   phan tu nho "noi" dan ve dau.
 - Co cai tien: neu mot luot khong co hoan vi nao -> da sap, dung som.
 - Do phuc tap: tot nhat O(n), xau nhat O(n^2).
============================================================
*/
#include <cstdio>

void hoanvi(int &a, int &b) { int t = a; a = b; b = t; }

void BubbleSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool coHoanVi = false;
        for (int j = n - 1; j > i; j--)
            if (a[j] < a[j - 1]) {
                hoanvi(a[j], a[j - 1]);
                coHoanVi = true;
            }
        if (!coHoanVi) break;          // khong doi cho -> da sap xong
    }
}

void inMang(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {52, 8, 91, 23, 5, 77, 14, 60, 3, 38};
    int n = sizeof(a) / sizeof(int);

    printf("Truoc: "); inMang(a, n);
    BubbleSort(a, n);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
