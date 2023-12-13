#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_ROWS 100  // Giả sử số hàng tối đa là 100
#define MAX_COLS 100  // Giả sử số cột tối đa là 100

void nhapMaTran(int maTran[MAX_ROWS][MAX_COLS], int soHang, int soCot) {
    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            printf("Nhap phan tu [%d][%d]: ", i, j);
            scanf("%d", &maTran[i][j]);
        }
    }
}

void inMaTran(int maTran[MAX_ROWS][MAX_COLS], int soHang, int soCot) {
    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            printf("%d ", maTran[i][j]);
        }
        printf("\n");
    }
}

void sapXepCotGiamDan(int maTran[MAX_ROWS][MAX_COLS], int soHang, int soCot) {
    for (int j = 0; j < soCot; j++) {
        for (int i = 0; i < soHang - 1; i++) {
            for (int k = i + 1; k < soHang; k++) {
                if (maTran[i][j] < maTran[k][j]) {
                    int temp = maTran[i][j];
                    maTran[i][j] = maTran[k][j];
                    maTran[k][j] = temp;
                }
            }
        }
    }
}

void ghiMaTranVaoFile(int maTran[MAX_ROWS][MAX_COLS], int soHang, int soCot, const char* tenFile) {
    FILE* file = fopen(tenFile, "w");
    if (file == NULL) {
        perror("Khong the mo file");
        return;
    }

    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            fprintf(file, "%d ", maTran[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    int soHang, soCot;
    int maTran[MAX_ROWS][MAX_COLS];

    printf("Nhap so hang: ");
    scanf("%d", &soHang);
    printf("Nhap so cot: ");
    scanf("%d", &soCot);

    nhapMaTran(maTran, soHang, soCot);
    printf("Ma tran ban dau:\n");
    inMaTran(maTran, soHang, soCot);

    sapXepCotGiamDan(maTran, soHang, soCot);
    printf("Ma tran sau khi sap xep giam dan theo cot:\n");
    inMaTran(maTran, soHang, soCot);

    ghiMaTranVaoFile(maTran, soHang, soCot, "output8.txt");
    printf("Noi dung da duoc ghi vao file output8.txt\n");

    return 0;
}
