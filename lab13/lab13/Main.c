#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>

int text_fr_ind = 0;
int url_fr_ind = 0;
FILE* f;

struct Header { //заголовок ID3
	char identifier[3];
	short version;
	char flags;
	char size[4];
} header;

struct FrameHeader
{
	char id[4];
	char size[4];
	char flags[2];
} frame_header;

struct Information
{
	struct Text
	{
		char name[5];
		char* info;
		int size;
		long int pos;
	} text_frames[40];

	struct URL
	{
		char name[5];
		char* info;
		int size;
		long int pos;
	} url_frames[10];

	struct
	{
		char name[5];
		char* info;
		int size;
		char language[3];
		long int pos;
	} Comm;

} Info;

void Show()
{
	int i, j;

	printf("\n");

	for (i = 0; i < text_fr_ind; i++)
	{
		printf("%s ", Info.text_frames[i].name);
		for (j = 0; j < Info.text_frames[i].size; j++)
			printf("%c", Info.text_frames[i].info[j]);
		printf("\n");
	}
	for (i = 0; i < url_fr_ind; i++)
	{
		printf("%s ", Info.url_frames[i].name);
		for (j = 0; j < Info.url_frames[i].size; j++)
			printf("%c", Info.url_frames[i].info[j]);
		printf("\n");
	}

	printf("\n%s ", Info.Comm.name);
	for (i = 0; i < Info.Comm.size; i++)
		printf("%c", Info.Comm.info[i]);

	printf("\n");
}

int ShowOne(char* prop_name)
{
	int i, j;
	int b = 0;

	printf("\n");

	if ((prop_name[0] == 'T') && (prop_name[1] != 'X'))
	{
		for (i = 0; i < text_fr_ind; i++)
			if (strcmp(prop_name, Info.text_frames[i].name) == 0)
			{
				for (j = 0; j < Info.text_frames[i].size; j++)
				{
					printf("%c", Info.text_frames[i].info[j]);
					b = 1;
				}

				break;
			}
	}
	else if ((prop_name[0] == 'W') && (prop_name[1] != 'X'))
	{
		for (i = 0; i < url_fr_ind; i++)
			if (strcmp(prop_name, Info.url_frames[i].name) == 0)
			{
				for (j = 0; j < Info.url_frames[i].size; j++)
				{
					printf("%c", Info.url_frames[i].info[j]);
					b = 1;
				}
				break;
			}
	}
	else if (strcmp(prop_name, "COMM") == 0)
	{
		b = 1;

		for (i = 0; i < Info.Comm.size; i++)
			printf("%c", Info.Comm.info[i]);
	}
	else
		return 1;

	if (b == 0)
		return 1;

	printf("\n");

	return 0;
}

int Change(char* prop_name, char* prop_value)
{
	int i, j;
	int b = 0;
	char emp = '\0';

	if (prop_name[0] == 'T')
	{
		for (i = 0; i < text_fr_ind; i++)
			if (!strcmp(prop_name, Info.text_frames[i].name))
			{
				if (strlen(prop_value) > Info.text_frames[i].size)
					return Info.text_frames[i].size;

				fseek(f, Info.text_frames[i].pos, SEEK_SET);
				fwrite(prop_value, 1, strlen(prop_value), f);

				for (j = strlen(prop_value); j < Info.text_frames[i].size; j++)
					fwrite(&emp, 1, 1, f);

				b = 1;

				break;
			}
	}
	else if (prop_name[0] == 'W')
	{
		for (i = 0; i < url_fr_ind; i++)
			if (strcmp(prop_name, Info.url_frames[i].name) == 0)
			{
				if (strlen(prop_value) > Info.url_frames[i].size)
					return Info.url_frames[i].size;

				fseek(f, Info.url_frames[i].pos, SEEK_SET);
				fwrite(prop_value, 1, strlen(prop_value), f);

				for (j = strlen(prop_value); j < Info.url_frames[i].size; j++)
					fwrite(&emp, 1, 1, f);

				b = 1;

				break;
			}
	}
	else if (strcmp(prop_name, "COMM") == 0)
	{
		if (strlen(prop_value) > Info.Comm.size)
			return Info.Comm.size;

		fseek(f, Info.Comm.pos, SEEK_SET);
		fwrite(prop_value, 1, strlen(prop_value), f);

		for (j = strlen(prop_value); j < Info.Comm.size; j++)
			fwrite(&emp, 1, 1, f);

		b = 1;
	}
	else
		return -1;

	if (b == 0)
		return -1;

	return 0;
}

int CharToInt(char* size, int bit)
{
	int res = 0;
	int k = 0;
	int i, j;
	for (i = 0; i < 4; i++)
	{
		int byte = size[3 - i];
		for (j = 0; j < bit; j++)
		{
			int d = (byte & 1);
			res += d * pow(2, k);
			k++;
			byte = byte >> 1;
		}
	}
	return res;
}

int main(int argc, char* argv[]) {
	char* locale = setlocale(LC_ALL, "");

	if (argc < 3) {
		printf("Неверное количество аргументов!");
		getchar();
		return 1;
	}

	char s[15] = "";
	strncat(s, argv[1], 10);

	if (strcmp(s, "--filepath") != 0) {
		printf("Ошибка в \"--filepath\"");
		getchar();
		return 1;
	}

	char filename[100] = "";
	for (int i = 11; i < strlen(argv[1]); i++)
		filename[i - 11] = argv[1][i];

	char command[7] = "";
	if (strcmp(argv[2], "--show") == 0)
	{
		strcpy(command, "--show");
	}

	char prop_name[5] = "";
	if (strcmp(argv[2], "--get") == 0)
	{
		strcpy(command, "--get");
		for (int i = 6; i < strlen(argv[2]); i++)
			prop_name[i - 6] = argv[2][i];
	}

	char prop_value[1000] = "";
	if (strcmp(argv[2], "--set") == 0)
	{
		strcpy(command, "--set");
		for (int i = 6; i < strlen(argv[2]); i++)
			prop_name[i - 6] = argv[2][i];

		for (int i = 8; i < strlen(argv[3]); i++)
			prop_value[i - 8] = argv[3][i];
	}

	f = fopen(filename, "r+b");
	if (f == NULL) 
	{
		printf("Error! Can't open file!\n");
		getchar();
		return 1;
	}

	fread(header.identifier, 1, 3, f);
	fread(&header.version, 2, 1, f);
	fread(&header.flags, 1, 1, f);
	fread(header.size, 1, 4, f);

	int size = CharToInt(header.size, 7);
	int cur = 0;

	while (cur < size)
	{
		fread(frame_header.id, 1, 4, f);
		fread(frame_header.size, 1, 4, f);
		int fr_size = CharToInt(frame_header.size, 8);
		fread(frame_header.flags, 1, 2, f);

		//обработка текстовых фреймов
		if ((frame_header.id[0] == 'T') && (frame_header.id[1] != 'X'))
		{
			char codesofsymbols;
			fread(&codesofsymbols, 1, 1, f);

			for (int i = 0; i < 4; i++)
				Info.text_frames[text_fr_ind].name[i] = frame_header.id[i];

			Info.text_frames[text_fr_ind].name[4] = '\0';
			Info.text_frames[text_fr_ind].info = (char*)malloc(fr_size - 1);
			Info.text_frames[text_fr_ind].pos = ftell(f);
			fread(Info.text_frames[text_fr_ind].info, 1, fr_size - 1, f);
			Info.text_frames[text_fr_ind].size = fr_size - 1;
			text_fr_ind++;
		}
		//обработка ссылочных фреймов
		else if ((frame_header.id[0] == 'W') && (frame_header.id[1] != 'X'))
		{
			for (int i = 0; i < 4; i++)
				Info.url_frames[url_fr_ind].name[i] = frame_header.id[i];

			Info.url_frames[url_fr_ind].name[4] = '\0';
			Info.url_frames[url_fr_ind].info = (char*)malloc(fr_size);
			Info.url_frames[url_fr_ind].pos = ftell(f);
			fread(Info.url_frames[url_fr_ind].info, 1, fr_size, f);
			Info.url_frames[url_fr_ind].size = fr_size;
			url_fr_ind++;
		}
		//обработка фрейма комментария
		else if (strcmp(frame_header.id, "COMM") == 0)
		{
			char codesofsymbols;

			fread(&codesofsymbols, 1, 1, f);
			fread(Info.Comm.language, 1, 3, f);

			for (int i = 0; i < 4; i++)
				Info.Comm.name[i] = frame_header.id[i];

			Info.Comm.name[4] = '\0';
			Info.Comm.info = (char*)malloc(fr_size - 4);
			Info.Comm.pos = ftell(f);
			fread(Info.Comm.info, 1, fr_size - 4, f);
			Info.Comm.size = fr_size - 4;
		}
		//считывание неопознанных фреймов
		else
		{
			if (fr_size < 0)
				break;
			char* other = (char*)malloc(fr_size);
			fread(other, 1, fr_size, f);
		}

		cur += 10 + fr_size;
	}

	if (strcmp(command, "--show") == 0)
		Show();

	if (strcmp(command, "--get") == 0)
		if (ShowOne(prop_name) == 1)
		{
			printf("No such field!\n");
			getchar();
		}

	if (strcmp(command, "--set") == 0)
	{
		int res = Change(prop_name, prop_value);

		if (res == -1)
		{
			printf("No such field!\n");
			getchar();
		}
		else if (res != 0)
		{
			printf("Your value has big size! Max value size = %d\n", res);
			getchar();
		}
		else
			printf("Changed successful\n\n");
	}

	fclose(f);

	getchar();

	return 0;
}
