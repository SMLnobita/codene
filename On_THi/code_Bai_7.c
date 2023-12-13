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

void sapXepHang(int hang[MAX_COLS], int soCot) {
    for (int i = 0; i < soCot - 1; i++) {
        for (int j = i + 1; j < soCot; j++) {
            if (hang[i] > hang[j]) {
                int temp = hang[i];
                hang[i] = hang[j];
                hang[j] = temp;
            }
        }
    }
}

void sapXepMaTranTheoHang(int maTran[MAX_ROWS][MAX_COLS], int soHang, int soCot) {
    for (int i = 0; i < soHang; i++) {
        sapXepHang(maTran[i], soCot);
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

    sapXepMaTranTheoHang(maTran, soHang, soCot);
    printf("Ma tran sau khi sap xep tang dan theo hang:\n");
    inMaTran(maTran, soHang, soCot);

    ghiMaTranVaoFile(maTran, soHang, soCot, "output7.txt");
    printf("Noi dung da duoc ghi vao file output7.txt\n");

    return 0;
}
