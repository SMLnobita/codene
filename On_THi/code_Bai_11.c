#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void xuLyFileVaGhiKetQua(const char* fileDauVao, const char* fileDauRa) {
    FILE* fileIn = fopen(fileDauVao, "r");
    FILE* fileOut = fopen(fileDauRa, "w");
    if (fileIn == NULL || fileOut == NULL) {
        perror("Loi mo file");
        if (fileIn != NULL) fclose(fileIn);
        if (fileOut != NULL) fclose(fileOut);
        return;
    }

    int so, tong = 0, index = 0;
    // Đọc số lượng phần tử (không sử dụng trong bài này)
    int soLuong;
    fscanf(fileIn, "%d", &soLuong);

    while (fscanf(fileIn, "%d", &so) != EOF) {
        if (index % 2 == 0) { // Vị trí chẵn
            tong += so;
            fprintf(fileOut, "%d ", so);
        }
        index++;
    }

    printf("Tong cac phan tu nam o vi tri chan la: %d\n", tong);

    fclose(fileIn);
    fclose(fileOut);
}

int main() {
    xuLyFileVaGhiKetQua("input11.txt", "output11.txt");
    return 0;
}
