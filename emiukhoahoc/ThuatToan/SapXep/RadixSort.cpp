/*
============================================================
 RADIX SORT (sap xep theo co so) - sap tang dan
 - Khong so sanh truc tiep: phan lo theo tung CHU SO
   tu hang don vi -> hang chuc -> ... (LSD).
 - Moi vong dung 10 lo (0..9), gom lai theo thu tu lo.
 - Ap dung cho so nguyen khong am.
 - Do phuc tap: O(n * d) voi d la so chu so cua so lon nhat.
============================================================
*/
#include <cstdio>
#include <cstring>

void RadixSort(int a[], int n) {
    int max = a[0];                        // tim so lon nhat de biet so chu so
    for (int i = 1; i < n; i++)
        if (a[i] > max) max = a[i];

    int **B = new int*[10];                // 10 lo B0..B9
    for (int t = 0; t < 10; t++) B[t] = new int[n];
    int count[10];

    for (int exp = 1; max / exp > 0; exp *= 10) {  // tung hang: 1, 10, 100...
        memset(count, 0, sizeof(count));
        for (int i = 0; i < n; i++) {      // phan lo theo chu so hang exp
            int t = (a[i] / exp) % 10;
            B[t][count[t]++] = a[i];
        }
        int k = 0;                         // gom cac lo lai vao a
        for (int t = 0; t < 10; t++)
            for (int i = 0; i < count[t]; i++)
                a[k++] = B[t][i];
    }
    for (int t = 0; t < 10; t++) delete[] B[t];
    delete[] B;
}

void inMang(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

int main() {
    int a[] = {52, 8, 91, 23, 5, 77, 14, 60, 3, 38};
    int n = sizeof(a) / sizeof(int);

    printf("Truoc: "); inMang(a, n);
    RadixSort(a, n);
    printf("Sau  : "); inMang(a, n);
    return 0;
}
