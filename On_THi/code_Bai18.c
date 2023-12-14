#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 1000

int main() {
    char str[MAX_SIZE];
    char outputStr[MAX_SIZE];
    char c;
    int i, j, len;

    // Bước 1: Đọc chuỗi từ file KYTU.INP
    FILE* file = fopen("KYTU.INP", "rb");
    if (!file) {
        perror("Khong the mo file KYTU.INP");
        return 1;
    }
    len = fread(str, sizeof(char), MAX_SIZE, file);
    str[len] = '\0';
    fclose(file);

    // In ra chuỗi ban đầu
    printf("Chuoi ban dau cua KYTU.INP: %s\n", str);

    // Bước 2: Nhập và xóa ký tự từ chuỗi
    printf("Nhap ky tu can xoa: ");
    scanf(" %c", &c);

    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != c) {
            outputStr[j++] = str[i];
        }
    }
    outputStr[j] = '\0';

    // Bước 3: Ghi chuỗi mới vào file OUTPUTKYTU.INP
    file = fopen("OUTPUTKYTU.INP", "wb");
    if (!file) {
        perror("Khong the mo file OUTPUTKYTU.INP");
        return 1;
    }
    fwrite(outputStr, sizeof(char), j, file);
    fclose(file);

    printf("Da ghi chuoi moi vao file OUTPUTKYTU.INP\n");
    return 0;
}
