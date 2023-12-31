#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void nhapMaTran(int** maTran, int soHang, int soCot) {
    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            printf("Nhap phan tu [%d][%d]: ", i, j);
            scanf("%d", &maTran[i][j]);
        }
    }
}

void inMaTran(int** maTran, int soHang, int soCot) {
    for (int i = 0; i < soHang; i++) {
        for (int j = 0; j < soCot; j++) {
            printf("%d ", maTran[i][j]);
        }
        printf("\n");
    }
}

void sapXepHang(int* hang, int soCot) {
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

void sapXepMaTranTheoHang(int** maTran, int soHang, int soCot) {
    for (int i = 0; i < soHang; i++) {
        sapXepHang(maTran[i], soCot);
    }
}

void ghiMaTranVaoFile(int** maTran, int soHang, int soCot, const char* tenFile) {
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
    printf("Nhap so hang: ");
    scanf("%d", &soHang);
    printf("Nhap so cot: ");
    scanf("%d", &soCot);

    // Cấp phát động cho mảng hai chiều
    int** maTran = (int**)malloc(soHang * sizeof(int*));
    for (int i = 0; i < soHang; i++) {
        maTran[i] = (int*)malloc(soCot * sizeof(int));
    }

    nhapMaTran(maTran, soHang, soCot);
    printf("Ma tran ban dau:\n");
    inMaTran(maTran, soHang, soCot);

    sapXepMaTranTheoHang(maTran, soHang, soCot);
    printf("Ma tran sau khi sap xep tang dan theo hang:\n");
    inMaTran(maTran, soHang, soCot);

    ghiMaTranVaoFile(maTran, soHang, soCot, "output7.txt");
    printf("Noi dung da duoc ghi vao file output7.txt\n");

    // Giải phóng bộ nhớ
    for (int i = 0; i < soHang; i++) {
        free(maTran[i]);
    }
    free(maTran);

    return 0;
}
