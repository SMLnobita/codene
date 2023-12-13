#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 1000 // Định nghĩa kích thước tối đa của mảng

int main() {
    FILE* inputFile, * outputFile;
    int numbers[MAX_SIZE]; // Khai báo mảng có kích thước cố định
    int count, i;

    // Mở file input9.txt để đọc
    inputFile = fopen("input9.txt", "r");
    if (inputFile == NULL) {
        perror("Loi mo file");
        return 1;
    }

    // Đọc số lượng số nguyên và kiểm tra không vượt quá MAX_SIZE
    fscanf(inputFile, "%d", &count);
    if (count > MAX_SIZE) {
        printf("So luong so nguyen vuot qua kich thuoc toi da\n"); 
        fclose(inputFile);
        return 1;
    }

    // Đọc các số nguyên từ file
    for (i = 0; i < count; i++) {
        fscanf(inputFile, "%d", &numbers[i]);
    }

    // Đóng file input
    fclose(inputFile);

    // Mở file output9.txt để ghi
    outputFile = fopen("output9.txt", "w");
    if (outputFile == NULL) {
        perror("Loi mo file");
        return 1;
    }

    // Ghi các số âm vào file
    for (i = 0; i < count; i++) {
        if (numbers[i] < 0) {
            fprintf(outputFile, "%d ", numbers[i]);
        }
    }
    fprintf(outputFile, "\n");

    // Ghi các số dương và không vào file
    for (i = 0; i < count; i++) {
        if (numbers[i] >= 0) {
            fprintf(outputFile, "%d ", numbers[i]);
        }
    }

    // Đóng file
    fclose(outputFile);

    return 0;
}
