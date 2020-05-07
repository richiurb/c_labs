#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

char* concat(char* s1, char* s2) {
	char* result;
	int i = 0;
	int j = 0;
	while ((s1[i]) != '\0') {
		i++;
	}
	while ((s2[j]) != '\0') {
		i++;
		j++;
	}

	result = calloc(i, sizeof(char));
	i = 0;
	j = 0;
	while ((result[i] = s1[i]) != '\0') {
		i++;
	}
	while ((result[i] = s2[j]) != '\0') {
		i++;
		j++;
	}
	return result;
}

int comp_n(char* s1, char* s2, int n) {
	int i = 0;
	while (i < n) {
		if (s1[i] != s2[i]) {
			return 0;
		}
		if (s1[i] == '\0') {
			return 0;
		}
		if (s2[i] == '\0') {
			return 0;
		}
		i++;
	}

	return 1;
}

int str_len(char* s) {
	int res = 0;
	while (s[res] != '\0') {
		res++;
	}

	return res;
}

int find_char(char* s, char c) {
	int res = 0;
	while ((s[res] != '\0') && (s[res] != c)) {
		res++;
	}

	return res;
}

int max_subset(char* s1, char* s2) {
	int res = 0;
	int i = 0;
	int count = 0;

	while (s1[i] != '\0') {
		int j = 0;
		while ((s2[j] != '\0') && (j != -1)) {
			if (s1[i] == s2[j]) {
				count++;
				j = -2;
			}
			j++;
		}

		if (j != -1) {
			res = count > res ? count : res;
			count = 0;
		}

		i++;
	}

	return count > res ? count : res;;
}

int main() {
	char* locale = setlocale(LC_ALL, "");
	char* first = malloc(200 * sizeof(char));
	char* second = malloc(200 * sizeof(char));
	scanf("%s", first);
	scanf("%s", second);

	char* firstSecond = concat(first, second);
	printf("Конкатенация двух строк: %s\n", firstSecond);

	int n;
	printf("Введите n для 4-ого задания: ");
	scanf("%d", &n);
	int res_4 = comp_n(first, second, n);
	if (!res_4) {
		printf("Первые %d символ(а/ов) в двух строках не совпадают:(\n", n);
	}
	else {
		printf("Первые %d символ(а/ов) в двух строках совпадают:)\n", n);
	}

	printf("Длина первой строки: %d\n", str_len(first));
	printf("Длина второй строки: %d\n", str_len(second));

	char symb;
	printf("Введите символ для 8-ого задания: ");
	scanf(" %c", &symb);
	printf("Первое вхождение %c в первой строке: %d\n", symb, find_char(first, symb));
	printf("Первое вхождение %c во второй строке: %d\n", symb, find_char(second, symb));

	printf("Максимальный отрезок в первой строке из символов второй: %d\n", max_subset(first, second));
	printf("Максимальный отрезок во второй строке из символов первой: %d\n", max_subset(second, first));

	return 0;
}
