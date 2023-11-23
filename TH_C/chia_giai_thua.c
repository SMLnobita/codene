// 1/ giai thừa
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int n;
	double sum = 0;
	do {
		printf("Nhap n: ");
		scanf("%d", &n);
		if (n <= 0) { system("cls"); printf("Vui long nhap lai n>0\n"); }
	} while (n <= 0);
	for (int i = 1; i <= n; i++) {
		double lq = 1;
		for (int j = 1; j <= i; j++) {
			lq *= j;
		}
		sum += (double)i / lq;
	}
	printf("Ket qua la: %.2lf ", sum);
}