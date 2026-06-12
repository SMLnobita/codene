/*
============================================================
 TIM KIEM TUYEN TINH (Linear Search)
 - Duyet tuan tu tu dau den cuoi, so sanh tung phan tu voi x.
 - KHONG can mang sap xep truoc.
 - Do phuc tap: tot nhat O(1), trung binh / xau nhat O(n).
============================================================
*/
#include <cstdio>

// Tra ve vi tri (chi so) cua x, -1 neu khong tim thay
int LinearSearch(int a[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (a[i] == x) return i;
    return -1;
}

// Cai tien "linh canh" (sentinel): dat x vao cuoi mang de bo bot dieu kien
// Luu y: mang phai du cho chua them 1 phan tu (a[n])
int LinearSearchSentinel(int a[], int n, int x) {
    int last = a[n - 1];
    a[n - 1] = x;                 // dat linh canh tam thoi
    int i = 0;
    while (a[i] != x) i++;
    a[n - 1] = last;              // tra lai gia tri cu
    if (i < n - 1 || a[n - 1] == x) return i;
    return -1;
}

void inMang(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {5, 2, 9, 1, 7, 3, 8};
    int n = sizeof(a) / sizeof(int);

    printf("Mang: "); inMang(a, n);

    printf("LinearSearch(9) -> vi tri %d\n", LinearSearch(a, n, 9));
    printf("LinearSearch(4) -> %d (khong thay)\n", LinearSearch(a, n, 4));
    printf("LinearSearchSentinel(7) -> vi tri %d\n", LinearSearchSentinel(a, n, 7));
    return 0;
}
