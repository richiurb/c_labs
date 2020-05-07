#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <math.h>

struct coordinate {
	double x;
	double y;
};

int gcd(int a, int b) {
	if (a % b == 0) return b;
	if (b % a == 0) return a;

	if (a > b) return gcd(a % b, b);
	return gcd(a, b % a);
}

int lcm(int a, int b) {
	return (a * b) / gcd(a, b);
}

double* get_dist(struct coordinate* m, int n) {
	double* res = malloc(n * (n - 1) * sizeof(double));
	int count = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j) {
				res[count] = sqrt(pow(m[i].x - m[j].x, 2) + pow(m[i].y - m[j].y, 2));
				count++;
			}
		}
	}

	return res;
}

int main() {
	char* locale = setlocale(LC_ALL, "");

	printf("������� 1. ��� � ���.\n");
	int first_numb, second_numb;
	printf("������� ��� ����� �����: ");
	scanf("%d%d", &first_numb, &second_numb);
	printf("��� ���� �����: %d\n", gcd(first_numb, second_numb));
	printf("��� ���� �����: %d\n", lcm(first_numb, second_numb));

	printf("������� 2. ����������.\n");
	printf("������� n - ���������� �����: ");
	int n;
	scanf("%d", &n);
	struct coordinate* memory = malloc(n * 2 * sizeof(double));
	for (int i = 0; i < n; ++i) {
		double x, y;
		printf("������� ���������� ����� %d: ", i + 1);
		scanf("%lf%lf", &x, &y);
		memory[i].x = x;
		memory[i].y = y;
	}
	printf("������ ����������:\n");
	double* dist = malloc(n * (n - 1) * sizeof(double));
	dist = get_dist(memory, n);
	for (int i = 0; i < n * (n - 1); ++i) {
		printf("from %d to %d: %lf\n", i / (n - 1) + 1, (i / (n - 1)) > (i % (n - 1)) ? i % (n - 1) + 1 : i % (n - 1) + 2, *(dist + i));
	}
	return 0;
}
