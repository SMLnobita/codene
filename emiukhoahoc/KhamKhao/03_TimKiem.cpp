/*
============================================================
 ON TAP 3: THUAT TOAN TIM KIEM
============================================================
 1. Tim kiem TUYEN TINH (Linear Search)
    - Duyet tu dau den cuoi, so sanh tung phan tu voi x.
    - Khong can mang co thu tu.
    - Do phuc tap: tot nhat O(1), xau nhat / trung binh O(n).
    - Cai tien "linh canh" (sentinel): dat x vao cuoi mang
      => bo duoc dieu kien i < n trong vong lap.

 2. Tim kiem NHI PHAN (Binary Search)
    - DIEU KIEN: mang DA SAP XEP.
    - Moi buoc so sanh voi phan tu giua (mid):
        a[mid] == x -> thay
        a[mid] >  x -> tim nua trai  (right = mid - 1)
        a[mid] <  x -> tim nua phai  (left  = mid + 1)
    - Do phuc tap: O(log n).
============================================================
*/
#include <cstdio>

// ---- Tim tuyen tinh: tra ve vi tri x, -1 neu khong thay ----
int LinearSearch(int a[], int n, int x) {
    for (int i = 0; i < n; i++)
        if (a[i] == x) return i;
    return -1;
}

// ---- Tim tuyen tinh dung linh canh ----
int LinearSearchSentinel(int a[], int n, int x) {
    a[n] = x;                 // dat linh canh cuoi mang (mang phai du cho)
    int i = 0;
    while (a[i] != x) i++;    // chac chan dung nho linh canh
    if (i == n) return -1;    // chi gap linh canh -> khong co
    return i;
}

// ---- Tim nhi phan (lap) ----
int BinarySearch(int a[], int n, int x) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (a[mid] == x) return mid;
        if (a[mid] > x)  right = mid - 1;  // tim ben trai
        else             left  = mid + 1;  // tim ben phai
    }
    return -1;
}

// ---- Tim nhi phan (de quy) ----
int BinarySearchRec(int a[], int left, int right, int x) {
    if (left > right) return -1;           // dieu kien dung
    int mid = (left + right) / 2;
    if (a[mid] == x) return mid;
    if (a[mid] > x)  return BinarySearchRec(a, left, mid - 1, x);
    return BinarySearchRec(a, mid + 1, right, x);
}

int main() {
    int a[20] = {2, 8, 5, 1, 9, 4};           // mang chua sap
    int n = 6;
    printf("Mang: 2 8 5 1 9 4\n");
    printf("LinearSearch(9)          -> vi tri %d\n", LinearSearch(a, n, 9));
    printf("LinearSearch(7)          -> %d (khong thay)\n", LinearSearch(a, n, 7));
    printf("LinearSearchSentinel(5)  -> vi tri %d\n", LinearSearchSentinel(a, n, 5));

    int b[] = {1, 3, 5, 7, 9, 11, 13};        // mang DA sap xep
    int m = 7;
    printf("\nMang sap xep: 1 3 5 7 9 11 13\n");
    printf("BinarySearch(7)    -> vi tri %d\n", BinarySearch(b, m, 7));
    printf("BinarySearch(2)    -> %d (khong thay)\n", BinarySearch(b, m, 2));
    printf("BinarySearchRec(11)-> vi tri %d\n", BinarySearchRec(b, 0, m - 1, 11));
    return 0;
}
