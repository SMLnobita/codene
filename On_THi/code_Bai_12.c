#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

void xoaKyTu(char* chuoi, char kyTuXoa) {
    int len = strlen(chuoi);
    int i, j;

    for (i = 0; i < len; i++) {
        if (chuoi[i] == kyTuXoa) {
            for (j = i; j < len - 1; j++) {
                chuoi[j] = chuoi[j + 1];
            }
            chuoi[j] = '\0';
            len--;
            i--;
        }
    }
}

int main() {
    FILE* fileIn = fopen("input12.txt", "r");
    FILE* fileOut = fopen("output12.txt", "w");
    char chuoi[MAX_SIZE];
    char kyTuXoa;

    if (fileIn == NULL || fileOut == NULL) {
        perror("Loi mo file");
        return 1;
    }

    fgets(chuoi, MAX_SIZE, fileIn);
    fclose(fileIn);

    printf("Nhap ky tu muon xoa: ");
    scanf("%c", &kyTuXoa);

    xoaKyTu(chuoi, kyTuXoa);
    fputs(chuoi, fileOut);

    fclose(fileOut);
    return 0;
}
