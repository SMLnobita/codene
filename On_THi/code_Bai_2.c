#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Hàm nhập mảng hai chiều
void nhapMang(int** arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Nhap phan tu [%d][%d]: ", i, j);
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

// Hàm tính tổng các phần tử trên mỗi cột và ghi vào file
void tinhTongCotVaGhiFile(int** arr, int n, int m) {
    FILE* file = fopen("output2.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    printf("Tong cac phan tu tren tung cot: ");
    for (int j = 0; j < m; j++) {
        int tongCot = 0;
        for (int i = 0; i < n; i++) {
            tongCot += arr[i][j];
        }
        printf("%d ", tongCot);
        fprintf(file, "%d ", tongCot);
    }
    fclose(file);
    printf("\nDa ghi tong cac cot vao file output2.txt\n");
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
    printf("Mang da nhap la:\n");
    xuatMang(arr, n, m);

    // Tính tổng từng cột và ghi vào file
    tinhTongCotVaGhiFile(arr, n, m);

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
