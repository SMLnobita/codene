#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main() {
    FILE* fileIn = fopen("input13.txt", "r");
    FILE* fileOut = fopen("output13.txt", "w");
    char chuoi[MAX_SIZE];
    int dem[256] = { 0 }; // Mảng đếm cho tất cả các ký tự ASCII có thể có
    int max = 0;
    char kyTuMax;

    if (fileIn == NULL || fileOut == NULL) {
        perror("Loi mo file");
        return 1;
    }

    fgets(chuoi, MAX_SIZE, fileIn);
    fclose(fileIn);

    int len = strlen(chuoi);
    for (int i = 0; i < len; i++) {
        dem[chuoi[i]]++;
        if (dem[chuoi[i]] > max) {
            max = dem[chuoi[i]];
            kyTuMax = chuoi[i];
        }
    }

    for (int i = 0; i < max; i++) {
        fputc(kyTuMax, fileOut);
    }

    fclose(fileOut);
    return 0;
}
