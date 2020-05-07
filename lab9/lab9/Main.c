#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

struct str_analis {
	int numbers;
	int lowercase;
	int uppercase;
};

struct str_analis info_str(char* s) {
	struct str_analis result = { 0, 0, 0 };
	int i = 0;
	while (s[i] != '\0') {
		if (('0' <= s[i]) && (s[i] <= '9')) {
			result.numbers++;
		}
		if (('a' <= s[i]) && (s[i] <= 'z')) {
			result.lowercase++;
		}
		if (('A' <= s[i]) && (s[i] <= 'Z')) {
			result.uppercase++;
		}

		i++;
	}

	return result;
}

int main() {
	char* locale = setlocale(LC_ALL, "");

	printf("Задание 1. Анализ строки.\n");
	char* first = malloc(200 * sizeof(char));
	scanf("%s", first);
	struct str_analis info_first = info_str(first);
	printf("Цифр в строке: %d;\nСтрочных букв в строке: %d;\nПрописных букв в строке: %d.\n", info_first.numbers, info_first.lowercase, info_first.uppercase);

	printf("\nЗадание 2. Плата за мобильную связь.\n");
	int minutes, seconds;
	double base_cost, per_minute;
	printf("Время, потраченное на разговоры: ");
	scanf("%d:%d", &minutes, &seconds);
	printf("Введите стоимость тарифа на 499 минут: ");
	scanf("%lf", &base_cost);
	printf("Введите стоимость минуты по истечении тарифа: ");
	scanf("%lf", &per_minute);

	double total_cost = 0;
	if (per_minute * 499 < base_cost) {
		printf("К сожалению, тариф невыгоден.");
	}
	else {
		if (minutes < 499) {
			total_cost = base_cost;
		}
		else {
			total_cost = base_cost + (double)((minutes - 499) * 60 + seconds) * per_minute / 60;
		}

		printf("Стоимость: %lf", total_cost);
	}
	return 0;
}
