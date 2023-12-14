#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void extractLastName(char* fullName, char* lastName) {
    char* lastSpace = strrchr(fullName, ' ');
    if (lastSpace != NULL) {
        strcpy(lastName, lastSpace + 1);
    }
    else {
        strcpy(lastName, fullName); // Trường hợp không có khoảng trắng
    }
}

int main() {
    FILE* inputFile = fopen("input20.txt", "r");
    FILE* outputFile = fopen("output20.txt", "w");

    char line[100];
    char lastName[100];

    while (fgets(line, sizeof(line), inputFile)) {
        extractLastName(line, lastName);
        fprintf(outputFile, "%s\n", lastName);
    }

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
