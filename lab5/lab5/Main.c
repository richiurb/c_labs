#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int arr[7];
	for (int i = 0; i < 7; ++i) {
		arr[i] = (i + 1) * 10;
		printf("a[%d] = %d;\n", i, arr[i]);
	}

	int arr2_1[2][2];
	int arr2_2[2][2];
	int arr2_final[2][2];
	arr2_1[0][0] = 1;
	arr2_1[0][1] = 1;
	arr2_1[1][0] = 1;
	arr2_1[1][1] = 4;
	arr2_2[0][0] = 1;
	arr2_2[0][1] = 2;
	arr2_2[1][0] = 4;
	arr2_2[1][1] = 1;
	arr2_final[0][0] = arr2_1[0][0] * arr2_2[0][0] + arr2_1[0][1] * arr2_2[1][0];
	arr2_final[0][1] = arr2_1[0][0] * arr2_2[0][1] + arr2_1[0][1] * arr2_2[1][1];
	arr2_final[1][0] = arr2_1[1][0] * arr2_2[0][0] + arr2_1[1][1] * arr2_2[1][0];
	arr2_final[1][1] = arr2_1[1][0] * arr2_2[0][1] + arr2_1[1][1] * arr2_2[1][1];
	printf("%d %d\n%d %d", arr2_final[0][0], arr2_final[0][1], arr2_final[1][0], arr2_final[1][1]);
	return 0;
}
