#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 100

int main() {
    FILE* fileIn = fopen("input15.txt", "r");
    FILE* fileOut = fopen("output15.txt", "w");
    int n, so;

    if (fileIn == NULL || fileOut == NULL) {
        perror("Loi mo file");
        return 1;
    }

    fscanf(fileIn, "%d", &n); // Doc kich thuoc ma tran

    printf("Cac so chan nam tren duong cheo chinh la: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fileIn, "%d", &so);
            if (i == j) {
                fprintf(fileOut, "%d ", so);
                if (so % 2 == 0) {
                    printf("%d ", so);
                }
            }
        }
    }
    printf("\n");

    fclose(fileIn);
    fclose(fileOut);
    return 0;
}
