#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void taoFileNhiPhan(const char* tenFile, int* duLieu, int kichThuoc) {
    FILE* file = fopen(tenFile, "wb");
    if (file == NULL) {
        perror("Không thể tạo file");
        return;
    }

    fwrite(duLieu, sizeof(int), kichThuoc, file);
    fclose(file);
}

void xuLySoNguyen(const char* fileDauVao, const char* fileChan, const char* fileLe) {
    FILE* fileINP = fopen(fileDauVao, "rb");
    FILE* fileChanOut = fopen(fileChan, "wb");
    FILE* fileLeOut = fopen(fileLe, "wb");

    if (fileINP == NULL || fileChanOut == NULL || fileLeOut == NULL) {
        perror("Không thể mở file");
        return;
    }

    int so;
    while (fread(&so, sizeof(int), 1, fileINP)) {
        if (so % 2 == 0) {
            fwrite(&so, sizeof(int), 1, fileChanOut);
        }
        else {
            fwrite(&so, sizeof(int), 1, fileLeOut);
        }
    }

    fclose(fileINP);
    fclose(fileChanOut);
    fclose(fileLeOut);
}

void inNoiDungFileNhiPhan(const char* tenFile) {
    FILE* file = fopen(tenFile, "rb");
    if (file == NULL) {
        perror("Khong the mo file");
        return;
    }

    int so;
    printf("Noi dung file %s la: ", tenFile);
    while (fread(&so, sizeof(int), 1, file)) {
        printf("%d ", so);
    }
    printf("\n");

    fclose(file);
}

int main() {
    int duLieu[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

    taoFileNhiPhan("SONGUYEN.INP", duLieu, sizeof(duLieu) / sizeof(duLieu[0]));
    xuLySoNguyen("SONGUYEN.INP", "SOCHAN.OUT", "SOLE.OUT");

    inNoiDungFileNhiPhan("SONGUYEN.INP");
    inNoiDungFileNhiPhan("SOCHAN.OUT");
    inNoiDungFileNhiPhan("SOLE.OUT");

    return 0;
}
