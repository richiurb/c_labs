#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <time.h>

int main() {
	char* locale = setlocale(LC_ALL, "");

	FILE* days;
	days = fopen("tendays.txt", "w");
	if (days == NULL) {
		printf("Can't create file.");
		return 1;
	}

	struct tm *u;
	char s[11] = { 0 };
	time_t time_now = time(NULL);

	for (int i = 0; i < 10; ++i) {
		u = localtime(&time_now);
		strftime(s, 11, "%d.%m.%Y", u);
		fprintf(days, "%s\n", s);
		u->tm_mday += 1;
		time_now = mktime(u);
	}

	fclose(days);
}
