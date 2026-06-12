/*
============================================================
 QUICK SORT (sap xep nhanh) - sap tang dan
 - Chia de tri: chon 1 phan tu lam moc (pivot, lay o giua),
   chia mang thanh 2 phan (< moc va > moc) roi de quy moi phan.
 - Do phuc tap: trung binh O(n log n), xau nhat O(n^2).
============================================================
*/
#include <cstdio>

void hoanvi(int &a, int &b) { int t = a; a = b; b = t; }

void QuickSort(int a[], int left, int right) {
    if (left >= right) return;
    int x = a[(left + right) / 2];     // chon moc o giua
    int i = left, j = right;
    while (i <= j) {
        while (a[i] < x) i++;          // tim phan tu >= moc ben trai
        while (a[j] > x) j--;          // tim phan tu <= moc ben phai
        if (i <= j) {
            hoanvi(a[i], a[j]);
            i++; j--;
        }
    }
    QuickSort(a, left, j);             // sap nua trai
    QuickSort(a, i, right);            // sap nua phai
}

void inMang(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {52, 8, 91, 23, 5, 77, 14, 60, 3, 38};
    int n = sizeof(a) / sizeof(int);

    printf("Truoc: "); inMang(a, n);
    QuickSort(a, 0, n - 1);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
