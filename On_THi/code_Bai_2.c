#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

// Hàm nhập mảng hai chiều
void nhapMang(int arr[MAX_ROWS][MAX_COLS], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Nhap phan tu [%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
}

// Hàm xuất mảng hai chiều
void xuatMang(int arr[MAX_ROWS][MAX_COLS], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// Hàm tính tổng các phần tử trên mỗi cột và ghi vào file
void tinhTongCotVaGhiFile(int arr[MAX_ROWS][MAX_COLS], int n, int m) {
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

    int arr[MAX_ROWS][MAX_COLS];

    // Nhập và xuất mảng
    nhapMang(arr, n, m);
    printf("Mang da nhap la:\n");
    xuatMang(arr, n, m);

    // Tính tổng từng cột và ghi vào file
    tinhTongCotVaGhiFile(arr, n, m);

    return 0;
}
