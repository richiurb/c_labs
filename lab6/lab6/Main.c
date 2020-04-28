#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

int main() {
	char memory_arr[4];
	char* memory = memory_arr;
	memory[0] = 'a';
	memory[1] = 'b';
	memory[2] = 'c';
	memory[3] = 'd';
	for (int i = 0; i < 4; ++i) {
		printf("%c ", memory[i]);
	}
	printf("\n");

	char* mem = malloc(sizeof(char[4]));
	mem[0] = 'a';
	mem[1] = 'b';
	mem[2] = 'c';
	mem[3] = 'd';
	for (int i = 0; i < 4; ++i) {
		printf("%c ", mem[i]);
	}
	free(mem);
	return 0;
}
