#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Hàm nhập mảng hai chiều
void nhapMang(int** arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Nhap phan tu arr[%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
}

// Hàm xuất mảng hai chiều
void xuatMang(int** arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// Hàm xuất các số lẻ và lưu vào tập tin
void xuatSoLeVaLuuFile(int** arr, int n, int m) {
    FILE* file = fopen("output1.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }
    printf("So le trong mang: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] % 2 != 0) {
                printf("%d ", arr[i][j]);
                fprintf(file, "%d ", arr[i][j]);
            }
        }
    }
    fclose(file);
}

int main() {
    int n, m;
    printf("Nhap so hang n: ");
    scanf("%d", &n);
    printf("Nhap so cot m: ");
    scanf("%d", &m);

    // Cấp phát động cho mảng hai chiều
    int** arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(m * sizeof(int));
    }

    // Nhập và xuất mảng
    nhapMang(arr, n, m);
    printf("Mang da nhap:\n");
    xuatMang(arr, n, m);

    // Xuất số lẻ và lưu vào tập tin
    xuatSoLeVaLuuFile(arr, n, m);

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
