// 1/ giai thừa
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

int main() {
	int x, y, z, t;
	int haman;
	int maxne, minene;
	int maxness;
	int minness;
	scanf("%d%d%d%d", &x, &y,&z,&t);

	if (x > y) {
		maxne = x;
	}
	else {
		maxne = y;
	}

	//Dòng 2 in ra số nhỏ hơn trong 2 số z, t
	if (z > t) {
		minene = t;
	}
	else {
		minene = z;
	}

	// Dòng 3 in ra số lớn nhất trong 3 số x, y, z
	if ((z > x) &&(z>y)) {
		maxness = z;
	}
	else if ((y > x) && (y > z)) {
		maxness = y;
	}
	else {
		maxness = x;
	}

	//Dòng 4 in ra số nhỏ nhất trong 4 số x, y, z, t
	if ((x < y) && (x < z && x < t)) {
		minness = x;
	}
	else if ((y < z) && (y < t && y < x)) {
		minness = y;
	}
	else if ((z < t) && (z < x && z < y)) {
		minness = z;
	}
	else {
		minness = t;
	}



	printf("%d\n", maxne);
	printf("%d\n", minene);
	printf("%d\n", maxness);
	printf("%d", minness);
	_getch();
    return 0;
}