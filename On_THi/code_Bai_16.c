#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Hàm so sánh cho qsort
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    FILE* inputFile, * outputFile;
    int n, i, j, k = 0;
    int matrix[100][100]; // Giả sử kích thước tối đa là 100x100
    int tempArray[10000]; // Mảng tạm để chứa các phần tử khi sắp xếp

    // Mở tập tin đầu vào
    inputFile = fopen("input16.txt", "r");
    if (inputFile == NULL) {
        perror("Không thể mở tập tin đầu vào");
        return 1;
    }

    // Đọc kích thước ma trận
    fscanf(inputFile, "%d", &n);

    // Đọc ma trận
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(inputFile, "%d", &matrix[i][j]);
        }
    }
    fclose(inputFile);

    // Chuyển ma trận sang mảng một chiều và sắp xếp
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            tempArray[k++] = matrix[i][j];
        }
    }
    qsort(tempArray, n * n, sizeof(int), compare);

    // Điền lại ma trận từ mảng đã sắp xếp, theo cột
    k = 0;
    for (j = 0; j < n; j++) {
        for (i = 0; i < n; i++) {
            matrix[i][j] = tempArray[k++];
        }
    }

    // Mở tập tin đầu ra và ghi ma trận
    outputFile = fopen("output16.txt", "w");
    if (outputFile == NULL) {
        perror("Không thể mở tập tin đầu ra");
        return 1;
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fprintf(outputFile, "%d ", matrix[i][j]);
        }
        fprintf(outputFile, "\n");
    }
    fclose(outputFile);

    return 0;
}
