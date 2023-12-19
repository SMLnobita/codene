#define  _CRT_SECURE_NO_WARNINGS
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

// Hàm tính và ghi giá trị trung bình từng hàng vào file
void tinhTrungBinhHangVaGhiFile(int** arr, int n, int m) {
    FILE* file = fopen("output3.txt", "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    printf("Gia tri trung binh tung hang: ");
    for (int i = 0; i < n; i++) {
        double tong = 0;
        for (int j = 0; j < m; j++) {
            tong += arr[i][j];
        }
        double trungBinh = tong / m;
        printf("%.2f ", trungBinh);
        fprintf(file, "%.2f ", trungBinh);
    }
    fclose(file);
    printf("\nDa ghi gia tri trung binh vao file output3.txt\n");
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

    // Tính trung bình từng hàng và ghi vào file
    tinhTrungBinhHangVaGhiFile(arr, n, m);

    // Giải phóng bộ nhớ
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}
