#include <math.h>

#ifndef RECTANGLE_H
#define RECTANGLE_H

struct point {
	double x;
	double y;
};

struct point make_point(double, double);
double length_side(struct point, struct point);

struct rectangle {
	struct point A;
	struct point B;
	struct point C;
	struct point D;
};

struct rectangle make_rectangle(struct point, struct point, struct point, struct point);
double perimeter(struct rectangle);
double square(struct rectangle);

#endif
