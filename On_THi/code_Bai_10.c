#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// Hàm kiểm tra số nguyên tố
int isPrime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;

    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }

    return 1;
}

int main() {
    FILE* inputFile, * outputFile;
    int n, num, sum = 0;

    // Mở file input10.txt để đọc
    inputFile = fopen("input10.txt", "r");
    if (inputFile == NULL) {
        perror("Loi mo file");
        return 1;
    }

    // Đọc số lượng số nguyên
    fscanf(inputFile, "%d", &n);

    // Mở file output10.txt để ghi
    outputFile = fopen("output10.txt", "w");
    if (outputFile == NULL) {
        perror("Loi mo file");
        fclose(inputFile);
        return 1;
    }

    // Đọc các số nguyên và xử lý
    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%d", &num);
        if (isPrime(num)) {
            sum += num;
            fprintf(outputFile, "%d ", num);
        }
    }

    // Đóng các file
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
