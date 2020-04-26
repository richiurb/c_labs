#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>

int main(int argc, char** argv) {
	char* locale = setlocale(LC_ALL, "");
	int numb;
	scanf("%x", &numb);
	printf("Задание 2: %d\n", numb);
	printf("Задание 3: %o %o\n", numb, numb >> 1);
	printf("Задание 4: %o %o\n", numb, ~numb);
	int numb5;
	scanf("%o", &numb5);
	printf("Задание 5: %o.", numb5 & numb);
	return 0;
}
