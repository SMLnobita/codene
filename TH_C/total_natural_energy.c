// tổng lũy thừa tự nhiên
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int n;
	long long sum = 0;
	do {
		printf("Nhap n: ");
		scanf("%d", &n);
		if (n <= 0) { system("cls"); printf("Vui long nhap lai n>0\n"); }
	} while (n <= 0);
	for (int i = 1; i <= n; i++) {
		sum += pow(i, i);
	}
	printf("Ket qua la: %lld ", sum);
}