/*
============================================================
 SELECTION SORT (chon truc tiep) - sap tang dan
 - Moi luot tim phan tu NHO NHAT trong doan chua sap,
   dua ve dau doan.
 - Do phuc tap: O(n^2) moi truong hop (it phep hoan vi).
============================================================
*/
#include <cstdio>

void hoanvi(int &a, int &b) { int t = a; a = b; b = t; }

void SelectionSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;                       // gia su a[i] nho nhat
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min]) min = j;     // tim vi tri nho nhat
        if (min != i) hoanvi(a[i], a[min]);
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
    SelectionSort(a, n);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
