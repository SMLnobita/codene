#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Ham nhap ma tran
void enterMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Nhap phan tu [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

// Ham in ma tran
void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Ham sap xep cac cot theo thu tu giam dan
void sortColumnsDescending(int** matrix, int rows, int cols) {
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            for (int k = i + 1; k < rows; k++) {
                if (matrix[i][j] < matrix[k][j]) {
                    int temp = matrix[i][j];
                    matrix[i][j] = matrix[k][j];
                    matrix[k][j] = temp;
                }
            }
        }
    }
}

// Ham ghi ma tran vao file
void writeToFile(int** matrix, int rows, int cols, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Loi mo file!\n");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%d ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

int main() {
    int n, m;
    printf("Nhap so hang (n): ");
    scanf("%d", &n);
    printf("Nhap so cot (m): ");
    scanf("%d", &m);

    // Cap phat dong cho ma tran
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(m * sizeof(int));
    }

    // Nhap va in ma tran
    enterMatrix(matrix, n, m);
    printf("Ma tran goc:\n");
    printMatrix(matrix, n, m);

    // Sap xep va in ma tran sau khi sap xep
    sortColumnsDescending(matrix, n, m);
    printf("Ma tran sau khi sap xep:\n");
    printMatrix(matrix, n, m);

    // Ghi ma tran vao file
    writeToFile(matrix, n, m, "output8.txt");

    // Giai phong bo nho
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}