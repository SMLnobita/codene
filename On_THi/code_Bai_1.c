#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 100  // Kích thước tối đa cho mảng

// Hàm nhập mảng hai chiều
void nhapMang(int arr[MAX_SIZE][MAX_SIZE], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("Nhap phan tu [%d][%d]: ", i, j);
            scanf("%d", &arr[i][j]);
        }
    }
}

// Hàm xuất mảng hai chiều
void xuatMang(int arr[MAX_SIZE][MAX_SIZE], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// Hàm xuất các phần tử lẻ và ghi vào file
void xuatSoLeVaGhiFile(int arr[MAX_SIZE][MAX_SIZE], int n, int m) {
    FILE* file = fopen("output1.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    printf("Cac phan tu le trong mang: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] % 2 != 0) {
                printf("%d ", arr[i][j]);
                fprintf(file, "%d ", arr[i][j]);
            }
        }
    }
    fclose(file);
    printf("\nDa ghi cac so le vao file output1.txt\n");
}

int main() {
    int n, m;
    printf("Nhap so hang n: ");
    scanf("%d", &n);
    printf("Nhap so cot m: ");
    scanf("%d", &m);

    // Khai báo mảng 2 chiều cố định
    int arr[MAX_SIZE][MAX_SIZE];

    // Nhập và xuất mảng
    nhapMang(arr, n, m);
    printf("Mang da nhap la:\n");
    xuatMang(arr, n, m);

    // Xuất số lẻ và ghi vào file
    xuatSoLeVaGhiFile(arr, n, m);

    return 0;
}
