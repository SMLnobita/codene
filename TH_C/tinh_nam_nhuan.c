// Sắp xếp giá trị
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

int main() {
	int date, moth, year;
	printf("Nhap ngay sinh: ");
	scanf("%d", &date);
	printf("Nhap thang sinh: ");
	scanf("%d", &moth);
	printf("Nhap nam sinh: ");
	scanf("%d", &year);
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		printf("Nam nhuan");
	else
	{
		printf("Nam khong nhuan");
	}
}