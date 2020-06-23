#define _CRT_SECURE_NO_WARNINGS

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable : 4996)

FILE* file;

struct BMP {
	unsigned short int type;
	unsigned int size_file;
	unsigned short int res1;
	unsigned short int res2;
	unsigned int offset;

	unsigned int size;
	int width;
	int height;
	unsigned short int planes;
	unsigned short int byte_count;

	unsigned int compression;
	unsigned int size_image;
	int xpels_per_meter;
	int ypels_per_meter;
	unsigned int colors_used;
	unsigned int color_important;
} header;

int arguments(char* input_file, char* output_dir, int *max_iter, int *dump_freq, int argc, char* argv[]) {
	for (int i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "--input") == 0)
			strcat(input_file, argv[i + 1]);

		if (strcmp(argv[i], "--output") == 0)
			strcat(output_dir, argv[i + 1]);

		if (strcmp(argv[i], "--max_iter") == 0)
			*max_iter = atoi(argv[i + 1]);

		if (strcmp(argv[i], "--dump_freq") == 0)
			*dump_freq = atoi(argv[i + 1]);
	}

	if (strcmp(input_file, "") == 0) {
		printf("No info about input file!");
		return 1;
	}

	if (strcmp(output_dir, "") == 0) {
		printf("No info about output file!");
		return 1;
	}

	return 0;
}

int* read_file() {
	fread(&header, 1, sizeof(header), file);

	int height = header.height;
	int width = header.width;

	int *a = malloc(height * width * sizeof(int));

	unsigned short int t = 0;
	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; ++j) {
			fread(&t, 1, 1, file);
			fread(&t, 1, 1, file);
			fread(&t, 1, 1, file);
			if (t == 255) {
				a[i * width + j] = 255;
			}
			else {
				a[i * width + j] = 0;
			}
		}
	}
	return a;
}

/*int write_file(char* output_dir, int count, int *b) {
	return 0;
}*/

int main(int argc, char* argv[]) {
	// work with arguments
	if ((argc < 5) || (argc > 9)) {
		printf("Invalid number of arguments!");
		return 1;
	}

	char input_file[100] = "";
	char output_dir[100] = "";
	int max_iter = -1;
	int dump_freq = 1;

	if (arguments(input_file, output_dir, &max_iter, &dump_freq, argc, argv) == 1)
		return 1;

	printf("%d %d ", max_iter, dump_freq);

	file = fopen(input_file, "rb");
	if (file == NULL) {
		printf("File %s can't open!", input_file);
		return 1;
	}

	fseek(file, 0, SEEK_SET);

	// read file

	fread(&header.type, 2, 1, file);
	fread(&header.size_file, 4, 1, file);
	fread(&header.res1, 2, 1, file);
	fread(&header.res2, 2, 1, file);
	fread(&header.offset, 4, 1, file);
	fread(&header.size, 4, 1, file);
	fread(&header.width, 4, 1, file);
	fread(&header.height, 4, 1, file);
	fread(&header.planes, 2, 1, file);
	fread(&header.byte_count, 2, 1, file);
	fread(&header.compression, 4, 1, file);
	fread(&header.size_image, 4, 1, file);
	fread(&header.xpels_per_meter, 4, 1, file);
	fread(&header.ypels_per_meter, 4, 1, file);
	fread(&header.colors_used, 4, 1, file);
	fread(&header.color_important, 4, 1, file);

	printf("\n%u %u %u %u %u %u %d %d %u %u %u %u %d %d %u %u\n", header.type, header.size_file, header.res1, header.res2, header.offset, header.size, header.width, header.height, header.planes, header.byte_count, header.compression, header.size_image, header.xpels_per_meter, header.ypels_per_meter, header.colors_used, header.color_important);

	int height = header.height;
	int width = header.width;

	int* a = malloc((height) * width * sizeof(int));

	int sizeInf = header.offset - sizeof(header);
	char* information = (char*)malloc(sizeInf);
	for (int i = 0; i < sizeInf; i++) {
		fread(&information[i], 1, 1, file);
	}

	

	unsigned short int t = 0;
	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			fread(&t, 1, 1, file);
			fread(&t, 1, 1, file);
			fread(&t, 1, 1, file);
			if (j == width - 1) {
				char skip;
				fread(&skip, 1, 1, file);
			}
			// printf("%d ", t);
			a[i * width + j] = (t == 255) ? 255 : 0;
			/* a[i * width + j] = t / 128;
			t %= 128;
			a[i * width + j + 1] = t / 64;
			t %= 64;
			a[i * width + j + 2] = t / 32;
			t %= 32;
			a[i * width + j + 3] = t / 16;
			t %= 16;
			a[i * width + j + 4] = t / 8;
			t %= 8;
			a[i * width + j + 5] = t / 4;
			t %= 4;
			a[i * width + j + 6] = t / 2;
			t %= 2;
			a[i * width + j + 7] = t; */
		}
	}

	int* b = malloc(header.height * header.width * sizeof(int));

	char output_name[5];
	strcpy(output_name, "life");


	// game
	int count = 1;
	while ((count <= max_iter) || (max_iter == -1)) {
		// check position
		for (int i = 0; i < header.height; ++i) {
			for (int j = 0; j < header.width; ++j) {
				int vertical_up = i - 1;
				int vertical_down = i + 1;
				int horizontal_left = j - 1;
				int horizontal_right = j + 1;

				if (vertical_up < 0)
					vertical_up = header.height - 1;
				if (vertical_down == header.height)
					vertical_down = 0;
				if (horizontal_left < 0)
					horizontal_left = header.width - 1;
				if (horizontal_right == header.width)
					horizontal_right = 0;

				int k = 0;
				if (a[vertical_up * header.width + horizontal_left] == 0)
					++k;
				if (a[vertical_up * header.width + j] == 0)
					++k;
				if (a[vertical_up * header.width + horizontal_right] == 0)
					++k;
				if (a[i * header.width + horizontal_left] == 0)
					++k;
				if (a[i * header.width + horizontal_right] == 0)
					++k;
				if (a[vertical_down * header.width + horizontal_left] == 0)
					++k;
				if (a[vertical_down * header.width + j] == 0)
					++k;
				if (a[vertical_down * header.width + horizontal_right] == 0)
					++k;

				b[i * header.width + j] = ((k == 3) || ((k == 2) && (a[i * header.width + j] == 0))) ? 0 : 255;
			}
		}

		// save new position
		for (int i = 0; i < header.height; ++i) {
			for (int j = 0; j < header.width; ++j) {
				a[i * header.width + j] = b[i * header.width + j];
			}
		}

		// write in file
		if ((count % dump_freq) == 0) {
			char out_name[200] = "";
			strcpy(out_name, output_dir);
			//char* out_name = malloc(sizeof(output_dir) + sizeof("\\"));
			strcat(out_name, "\\");
			//char* out_name = malloc(sizeof(output_dir) + sizeof("\\") + sizeof(output_name));
			strcat(out_name, output_name);
			strcat(out_name, "_");
			char number[10];
			char* s = itoa(count, number, 10);
			strcat(out_name, number);
			strcat(out_name, ".bmp");

			printf("%s", out_name);

			FILE* file_out = fopen(out_name, "wb");

			fseek(file, 0, SEEK_SET);
			fseek(file_out, 0, SEEK_SET);

			fwrite(&header.type, 2, 1, file_out);
			fwrite(&header.size_file, 4, 1, file_out);
			fwrite(&header.res1, 2, 1, file_out);
			fwrite(&header.res2, 2, 1, file_out);
			fwrite(&header.offset, 4, 1, file_out);
			fwrite(&header.size, 4, 1, file_out);
			fwrite(&header.width, 4, 1, file_out);
			fwrite(&header.height, 4, 1, file_out);
			fwrite(&header.planes, 2, 1, file_out);
			fwrite(&header.byte_count, 2, 1, file_out);
			fwrite(&header.compression, 4, 1, file_out);
			fwrite(&header.size_image, 4, 1, file_out);
			fwrite(&header.xpels_per_meter, 4, 1, file_out);
			fwrite(&header.ypels_per_meter, 4, 1, file_out);
			fwrite(&header.colors_used, 4, 1, file_out);
			fwrite(&header.color_important, 4, 1, file_out);

			for (int i = height - 1; i >= 0; i--) {
				for (int j = 0; j < width; j++) {
					unsigned char v = b[i * width + j];
					fwrite(&v, 1, 1, file_out);
					fwrite(&v, 1, 1, file_out);
					fwrite(&v, 1, 1, file_out);
					if (j == width - 1)
						fwrite(&v, 1, 1, file_out);
				}
			}

			fclose(file_out);
		}

		count++;
	}

	fclose(file);

	return 0;
}
