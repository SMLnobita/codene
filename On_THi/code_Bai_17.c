#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

void inputMatrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Nhap phan tu [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void outputMatrix(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void sortDescending(int arr[MAX_COLS], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] < arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void saveToFile(int matrix[MAX_ROWS][MAX_COLS], int rows, int cols, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        return;
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
    int matrix[MAX_ROWS][MAX_COLS];
    int rows, cols;

    printf("Nhap so hang: ");
    scanf("%d", &rows);
    printf("Nhap so cot: ");
    scanf("%d", &cols);

    inputMatrix(matrix, rows, cols);

    for (int i = 0; i < rows; i++) {
        sortDescending(matrix[i], cols);
    }

    printf("Ma tran sau khi sap xep:\n");
    outputMatrix(matrix, rows, cols);
    saveToFile(matrix, rows, cols, "output17.txt");

    return 0;
}
