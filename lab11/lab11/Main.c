#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include "Rectangle.h"

int main() {
	char* locale = setlocale(LC_ALL, "");

	struct rectangle geo_fig;
	struct point* p = malloc(4 * 2 * sizeof(double));

	for (int i = 0; i < 4; ++i) {
		printf("Введите точку %d: ", i + 1);
		double x, y;
		scanf("%lf%lf", &x, &y);
		*(p + i) = make_point(x, y);
	}

	geo_fig = make_rectangle(p[0], p[1], p[2], p[3]);
	printf("Периметр прямоугольника: %lf\n", perimeter(geo_fig));
	printf("Площадь прямоугольника: %lf\n", square(geo_fig));

	return 0;
}
