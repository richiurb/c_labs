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

	printf("������� 1. ������ ������.\n");
	char* first = malloc(200 * sizeof(char));
	scanf("%s", first);
	struct str_analis info_first = info_str(first);
	printf("���� � ������: %d;\n�������� ���� � ������: %d;\n��������� ���� � ������: %d.\n", info_first.numbers, info_first.lowercase, info_first.uppercase);

	printf("\n������� 2. ����� �� ��������� �����.\n");
	int minutes, seconds;
	double base_cost, per_minute;
	printf("�����, ����������� �� ���������: ");
	scanf("%d:%d", &minutes, &seconds);
	printf("������� ��������� ������ �� 499 �����: ");
	scanf("%lf", &base_cost);
	printf("������� ��������� ������ �� ��������� ������: ");
	scanf("%lf", &per_minute);

	double total_cost = 0;
	if (per_minute * 499 < base_cost) {
		printf("� ���������, ����� ���������.");
	}
	else {
		if (minutes < 499) {
			total_cost = base_cost;
		}
		else {
			total_cost = base_cost + (double)((minutes - 499) * 60 + seconds) * per_minute / 60;
		}

		printf("���������: %lf", total_cost);
	}
	return 0;
}
