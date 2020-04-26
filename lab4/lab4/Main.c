#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char** argv) {
	int numb;
	scanf("%d", &numb);
	printf("%d\n", (numb >= 10) & (numb <= 100));
	int numb2;
	scanf("%d", &numb2);
	printf("%d", (numb2 >> 21) % 2);
	return 0;
}
