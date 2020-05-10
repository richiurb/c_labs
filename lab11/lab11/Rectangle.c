#include "Rectangle.h"

struct point make_point(double x, double y) {
	struct point result;
	result.x = x;
	result.y = y;
	return result;
}

double length_side(struct point A, struct point B) {
	return sqrt((B.x - A.x) * (B.x - A.x) + (B.y - A.y) * (B.y - A.y));
}

struct rectangle make_rectangle(struct point A, struct point B, struct point C, struct point D) {
	struct rectangle result;
	result.A = A;
	result.B = B;
	result.C = C;
	result.D = D;
	return result;
}

double perimeter(struct rectangle fig) {
	return 2 * (length_side(fig.A, fig.B) + length_side(fig.B, fig.C));
}

double square(struct rectangle fig) {
	return length_side(fig.A, fig.B) * length_side(fig.B, fig.C);
}