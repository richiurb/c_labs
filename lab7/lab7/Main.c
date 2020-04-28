#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

enum weekday {
	Monday,
	Tuesday,
	Wednesday,
	Thursday,
	Friday,
	Saturday,
	Sunday,
};

struct circle {
	double r;
	double x;
	double y;
};

struct circle makeCircle(double r, double x, double y) {
	struct circle c;
	c.r = r;
	c.x = x;
	c.y = y;

	return c;
}

double lengthOfCircle(double r) {
	struct circle c = makeCircle(r, 0, 0);
	return 2 * acos(-1) * c.r;
}

union ADSL {
	int number;
	struct {
		unsigned DSL : 1;
		unsigned PPP : 1;
		unsigned Link : 1;
	};
};

int main() {
	printf("%d\n", Monday);

	double radius = 2.5;
	printf("%lf\n", lengthOfCircle(radius));

	union ADSL num;
	scanf("%x", &num.number);
	printf("DSL: %d; PPP: %d; Link: %d", num.DSL, num.PPP, num.Link);

	return 0;
}
