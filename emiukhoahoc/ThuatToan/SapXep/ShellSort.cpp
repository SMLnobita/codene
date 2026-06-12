/*
============================================================
 SHELL SORT - sap tang dan
 - Cai tien cua Insertion sort: so sanh/chen cac phan tu cach nhau
   khoang h, h giam dan ve 1 (vd n/2, n/4, ..., 1).
 - Khi h = 1 thi chinh la insertion sort nhung mang da gan sap.
 - Do phuc tap: phu thuoc day h, khoang O(n^1.2) ~ O(n^1.5).
============================================================
*/
#include <cstdio>

void ShellSort(int a[], int n) {
    for (int h = n / 2; h > 0; h /= 2) {       // khoang cach giam dan
        for (int i = h; i < n; i++) {          // insertion sort buoc h
            int x = a[i];
            int j = i - h;
            while (j >= 0 && a[j] > x) {
                a[j + h] = a[j];
                j -= h;
            }
            a[j + h] = x;
        }
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
    ShellSort(a, n);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
