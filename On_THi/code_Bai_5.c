#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void taoFileSonguyen() {
    FILE* file = fopen("SONGUYEN.INP", "wb");
    if (file == NULL) {
        printf("Khong the tao file SONGUYEN.INP.\n");
        return;
    }

    int so[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    fwrite(so, sizeof(int), 9, file);
    fclose(file);
}

void docVaPhanLoaiFile() {
    FILE* fileInp = fopen("SONGUYEN.INP", "rb");
    FILE* fileChan = fopen("SOCHAN.OUT", "wb");
    FILE* fileLe = fopen("SOLE.OUT", "wb");

    if (fileInp == NULL || fileChan == NULL || fileLe == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    int so;
    while (fread(&so, sizeof(int), 1, fileInp) == 1) {
        if (so % 2 == 0) {
            fwrite(&so, sizeof(int), 1, fileChan);
        }
        else {
            fwrite(&so, sizeof(int), 1, fileLe);
        }
    }

    fclose(fileInp);
    fclose(fileChan);
    fclose(fileLe);
}

void inNoiDungFile(const char* tenFile) {
    FILE* file = fopen(tenFile, "rb");
    if (file == NULL) {
        printf("Khong the mo file %s.\n", tenFile);
        return;
    }

    int so;
    printf("Noi dung file %s la: ", tenFile);
    while (fread(&so, sizeof(int), 1, file) == 1) {
        printf("%d ", so);
    }
    printf("\n");

    fclose(file);
}

int main() {
    taoFileSonguyen();
    docVaPhanLoaiFile();

    inNoiDungFile("SONGUYEN.INP");
    inNoiDungFile("SOCHAN.OUT");
    inNoiDungFile("SOLE.OUT");

    return 0;
}
