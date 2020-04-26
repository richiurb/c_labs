#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char** argv) {
	int numb;
	char symb;
	scanf("%d %c", &numb, &symb);
	printf("number: %d; char: %c.", numb, symb);
	return 0;
}
