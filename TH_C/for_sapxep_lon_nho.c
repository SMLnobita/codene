// Sắp xếp giá trị
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

int main() {
	int a, b, c, d, e, temp;
	scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
	for (int i = 0; i <= 5; i++) {
		if (a < b) { temp = a; a = b; b = temp; };
		if (b < c) { temp = b; b = c; c = temp; };
		if (c < d) { temp = c; c = d; d = temp; };
		if (d < e) { temp = d; d = e; e = temp; };
	}
	printf("gia tri la: %d %d %d %d", a, b, c, d);
}