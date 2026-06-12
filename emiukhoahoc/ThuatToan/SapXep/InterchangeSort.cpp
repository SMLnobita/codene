/*
============================================================
 INTERCHANGE SORT (doi cho truc tiep) - sap tang dan
 - Voi moi vi tri i, so sanh voi tat ca phan tu phia sau j,
   neu a[j] < a[i] thi doi cho ngay.
 - Do phuc tap: O(n^2) moi truong hop.
============================================================
*/
#include <cstdio>

void hoanvi(int &a, int &b) { int t = a; a = b; b = t; }

void InterchangeSort(int a[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[j] < a[i])
                hoanvi(a[i], a[j]);
}

void inMang(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {52, 8, 91, 23, 5, 77, 14, 60, 3, 38};
    int n = sizeof(a) / sizeof(int);

    printf("Truoc: "); inMang(a, n);
    InterchangeSort(a, n);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
