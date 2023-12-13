#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int laSoNguyenTo(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int main() {
    FILE* fileIn = fopen("input14.txt", "r");
    FILE* fileOut = fopen("output14.txt", "w");
    int n, so;

    if (fileIn == NULL || fileOut == NULL) {
        perror("Loi mo file");
        return 1;
    }

    fscanf(fileIn, "%d", &n); // Doc kich thuoc ma tran

    printf("Cac so nguyen to nam tren duong cheo phu la: ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fileIn, "%d", &so);
            // Kiem tra neu la phan tu tren duong cheo phu
            if (i + j == n - 1) {
                if (laSoNguyenTo(so)) {
                    fprintf(fileOut, "%d ", so);
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
