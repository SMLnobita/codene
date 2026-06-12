/*
============================================================
 MERGE SORT (sap xep tron) - sap tang dan
 - Chia de tri: chia doi mang, de quy sap moi nua,
   roi TRON (merge) 2 nua da sap thanh 1 mang sap.
 - Can bo nho phu de tron.
 - Do phuc tap: O(n log n) moi truong hop (on dinh).
============================================================
*/
#include <cstdio>

// Tron 2 doan da sap a[left..mid] va a[mid+1..right]
void Merge(int a[], int left, int mid, int right) {
    int nb = mid - left + 1, nc = right - mid;
    int *b = new int[nb], *c = new int[nc];
    for (int i = 0; i < nb; i++) b[i] = a[left + i];
    for (int i = 0; i < nc; i++) c[i] = a[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < nb && j < nc)               // lay phan tu nho hon truoc
        a[k++] = (b[i] <= c[j]) ? b[i++] : c[j++];
    while (i < nb) a[k++] = b[i++];        // phan con lai cua b
    while (j < nc) a[k++] = c[j++];        // phan con lai cua c
    delete[] b; delete[] c;
}

void MergeSort(int a[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    MergeSort(a, left, mid);               // sap nua trai
    MergeSort(a, mid + 1, right);          // sap nua phai
    Merge(a, left, mid, right);            // tron 2 nua
}

void inMang(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {52, 8, 91, 23, 5, 77, 14, 60, 3, 38};
    int n = sizeof(a) / sizeof(int);

    printf("Truoc: "); inMang(a, n);
    MergeSort(a, 0, n - 1);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
