/*
============================================================
 INSERTION SORT (chen truc tiep) - sap tang dan
 - Coi a[0] da sap. Lan luot lay a[i] chen vao dung vi tri
   trong doan da sap a[0..i-1] (doi cac phan tu lon hon sang phai).
 - Do phuc tap: tot nhat O(n) (mang gan sap), xau nhat O(n^2).
============================================================
*/
#include <cstdio>

void InsertionSort(int a[], int n) {
    for (int i = 1; i < n; i++) {
        int x = a[i];                  // phan tu can chen
        int pos = i - 1;
        while (pos >= 0 && a[pos] > x) {
            a[pos + 1] = a[pos];       // doi cho sang phai
            pos--;
        }
        a[pos + 1] = x;                // chen x vao vi tri thich hop
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
    InsertionSort(a, n);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
