#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 1000 // Giả sử kích thước tối đa của dãy số

int main() {
    FILE* inputFile, * outputFile;
    int numbers[MAX_SIZE];
    int num, countPos = 0, countNeg = 0;
    int i = 0;

    // Đọc từ file input9.txt
    inputFile = fopen("input9.txt", "r");
    if (inputFile == NULL) {
        perror("Khong the mo file input9.txt");
        return 1;
    }

    while (fscanf(inputFile, "%d", &num) != EOF) {
        numbers[i++] = num;
        if (num > 0) {
            countPos++;
        }
        else if (num < 0) {
            countNeg++;
        }
    }

    fclose(inputFile);

    // In số lượng phần tử âm và dương
    printf("So phan tu am la %d, so phan tu duong la %d\n", countNeg, countPos);

    // Ghi vào file output9.txt
    outputFile = fopen("output9.txt", "w");
    if (outputFile == NULL) {
        perror("Khong the mo file output9.txt");
        return 1;
    }

    for (int j = 0; j < i; j++) {
        if (numbers[j] < 0) {
            fprintf(outputFile, "%d ", numbers[j]);
        }
    }

    fprintf(outputFile, "\n");

    for (int j = 0; j < i; j++) {
        if (numbers[j] > 0) {
            fprintf(outputFile, "%d ", numbers[j]);
        }
    }

    fclose(outputFile);
    printf("Noi dung da duoc ghi vao file output9.txt\n");

    return 0;
}
