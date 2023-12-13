#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void ghiSoVaoFile(const char* tenFile, int* so, int soLuong) {
    FILE* file = fopen(tenFile, "wb");
    if (!file) {
        perror("Loi khi mo file de ghi");
        return;
    }

    fwrite(so, sizeof(int), soLuong, file);
    fclose(file);
}

void docVaPhanLoaiSo(const char* tenFileInput, const char* tenFileChan, const char* tenFileLe) {
    FILE* fileInput = fopen(tenFileInput, "rb");
    if (!fileInput) {
        perror("Loi khi mo file de doc");
        return;
    }

    FILE* fileChan = fopen(tenFileChan, "wb");
    FILE* fileLe = fopen(tenFileLe, "wb");
    if (!fileChan || !fileLe) {
        perror("Loi khi mo file de ghi");
        return;
    }

    int so;
    while (fread(&so, sizeof(int), 1, fileInput) == 1) {
        if (so % 2 == 0) {
            fwrite(&so, sizeof(int), 1, fileChan);
        } else {
            fwrite(&so, sizeof(int), 1, fileLe);
        }
    }

    fclose(fileInput);
    fclose(fileChan);
    fclose(fileLe);
}

void hienThiNoiDungFile(const char* tenFile) {
    FILE* file = fopen(tenFile, "rb");
    if (!file) {
        perror("Loi khi mo file de doc");
        return;
    }

    printf("Noi dung file %s la: ", tenFile);
    int so;
    while (fread(&so, sizeof(int), 1, file) == 1) {
        printf("%d ", so);
    }
    printf("\n");

    fclose(file);
}

int main() {
    int cacSo[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // Vi du ve cac so nguyen
    int soLuong = sizeof(cacSo) / sizeof(cacSo[0]);

    ghiSoVaoFile("SONGUYEN.INP", cacSo, soLuong);
    docVaPhanLoaiSo("SONGUYEN.INP", "SOCHAN.OUT", "SOLE.OUT");

    hienThiNoiDungFile("SONGUYEN.INP");
    hienThiNoiDungFile("SOCHAN.OUT");
    hienThiNoiDungFile("SOLE.OUT");

    return 0;
}
