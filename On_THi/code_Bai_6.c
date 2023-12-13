#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_INTS 1000

void selectionSort(int arr[], int n) {
    int i, j, min_idx, temp;

    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

void printArray(const int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    FILE* file;
    int numbers[NUM_INTS];
    int i;

    // Tao gia so ngau nhien
    for (i = 0; i < NUM_INTS; i++) {
        numbers[i] = i * 3 % 1000; // So gia ngau nhien
    }

    // Ghi vao file SONGUYEN.INP
    file = fopen("SONGUYEN.INP", "wb");
    if (!file) {
        perror("Khong the mo file SONGUYEN.INP");
        return 1;
    }

    fwrite(numbers, sizeof(numbers[0]), NUM_INTS, file);
    fclose(file);

    printf("Noi dung file SONGUYEN.INP la: ");
    printArray(numbers, 9); // Chi in 9 so dau tien de don gian

    // Doc va sap xep
    file = fopen("SONGUYEN.INP", "rb");
    if (!file) {
        perror("Khong the mo file SONGUYEN.INP");
        return 1;
    }

    fread(numbers, sizeof(numbers[0]), NUM_INTS, file);
    fclose(file);

    selectionSort(numbers, NUM_INTS);

    // Ghi vao file SONGUYEN.OUT
    file = fopen("SONGUYEN.OUT", "wb");
    if (!file) {
        perror("Khong the mo file SONGUYEN.OUT");
        return 1;
    }

    fwrite(numbers, sizeof(numbers[0]), NUM_INTS, file);
    fclose(file);

    printf("Noi dung file SONGUYEN.OUT la: ");
    printArray(numbers, 9); // Chi in 9 so dau tien de don gian

    return 0;
}
