/*
============================================================
 HEAP SORT (sap xep vun dong) - sap tang dan
 - Dung MAX-HEAP (nut cha >= nut con).
   Giai doan 1: xay max-heap tu mang.
   Giai doan 2: doi dinh (max) ve cuoi, thu nho heap, hieu chinh lai.
 - Do phuc tap: O(n log n) moi truong hop.
============================================================
*/
#include <cstdio>

void hoanvi(int &a, int &b) { int t = a; a = b; b = t; }

// Hieu chinh doan a[l..r] thanh max-heap (lan truyen tu nut l xuong)
void heapify(int a[], int l, int r) {
    int i = l, j = 2 * i + 1;          // j: con trai cua i
    int x = a[l];
    while (j <= r) {
        if (j < r && a[j] < a[j + 1]) j++;   // chon con LON hon
        if (a[j] <= x) break;          // da thoa dieu kien heap
        a[i] = a[j];                   // keo con len
        i = j;
        j = 2 * i + 1;
    }
    a[i] = x;
}

void HeapSort(int a[], int n) {
    for (int l = n / 2 - 1; l >= 0; l--)   // giai doan 1: xay max-heap
        heapify(a, l, n - 1);
    for (int r = n - 1; r > 0; r--) {      // giai doan 2
        hoanvi(a[0], a[r]);                // dua max ve cuoi
        heapify(a, 0, r - 1);              // hieu chinh lai heap
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
    HeapSort(a, n);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
