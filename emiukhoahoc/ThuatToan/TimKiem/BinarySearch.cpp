/*
============================================================
 TIM KIEM NHI PHAN (Binary Search)
 - DIEU KIEN: mang DA SAP XEP (tang dan).
 - Moi buoc so sanh voi phan tu giua (mid):
     a[mid] == x -> tim thay
     a[mid] >  x -> tim nua TRAI  (right = mid - 1)
     a[mid] <  x -> tim nua PHAI  (left  = mid + 1)
 - Do phuc tap: O(log n).
============================================================
*/
#include <cstdio>

// Cach 1: lap (khu de quy)
int BinarySearch(int a[], int n, int x) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] > x)  right = mid - 1;
        else             left  = mid + 1;
    }
    return -1;
}

// Cach 2: de quy
int BinarySearchRec(int a[], int left, int right, int x) {
    if (left > right) return -1;            // dieu kien dung
    int mid = (left + right) / 2;
    if (a[mid] == x) return mid;
    if (a[mid] > x)  return BinarySearchRec(a, left, mid - 1, x);
    return BinarySearchRec(a, mid + 1, right, x);
}

void inMang(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {1, 3, 5, 7, 9, 11, 13, 15};   // PHAI sap xep tang dan
    int n = sizeof(a) / sizeof(int);

    printf("Mang da sap: "); inMang(a, n);

    printf("BinarySearch(9)     -> vi tri %d\n", BinarySearch(a, n, 9));
    printf("BinarySearch(2)     -> %d (khong thay)\n", BinarySearch(a, n, 2));
    printf("BinarySearchRec(13) -> vi tri %d\n", BinarySearchRec(a, 0, n - 1, 13));
    return 0;
}
