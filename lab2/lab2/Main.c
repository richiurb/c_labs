#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int main(int argc, char** argv) {
	double alpha;
	scanf("%lf", &alpha);
	double first = 2 * pow(sin(3 * acos(-1) - 2 * alpha), 2) * pow(cos(5 * acos(-1) + 2 * alpha), 2);
	double second = (double)1 / 4 - (double)1 / 4 * sin(5 / 2 * acos(-1) - 8 * alpha);
	printf("z_1 = %lf; z_2 = %lf", first, second);
	return 0;
}
