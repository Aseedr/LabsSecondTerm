#include "laba7.h"

void menu()
{	
	int sh = 0;
	while (1)
	{
		puts("Выбирите вид операции:");
		puts("	1 - Создать файл");
		puts("	2 - Просмотреть содержимое файла");
		puts("	3 - Выход");
		do
		{
			//fflush(stdin);
			__fpurge(stdin);
			if (!scanf("%d", &sh) || (sh < 1) || (sh > 3))
			{
				puts("Ошибка ввода. Введите заново");
			}
		} while (!sh || (sh < 1) || (sh > 3));

		switch (sh)
		{
		case 1: add_file(); break;
		case 2: print(); break;
		case 3: return;
		}
	}
}


void add_file()
{
	char *name;
	FILE *file; int i, sh = 0, number = 0;
	name = (char *)calloc(N, sizeof(char));
	puts("Введите имя файла с его расширением (file.txt), не более 20 символов");
	//fflush(stdin);
	__fpurge(stdin);
	fgets(name, N, stdin);
	if (name[0] == '\n')
	{
		puts("Ошибка ввода имени файла");
		return;
	}
	for (i = 0; i < N; i++)
	{
		if(name[i] == '\n')
		{
			name[i] = 0;
			break;
		}
	}
	srand(time(NULL));
	
	puts("Введите количество цифр в файле");
	do
		{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &sh) || (sh < 1) || (sh > MAX))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!sh || (sh < 1) || (sh > MAX));

	file = fopen(name, "w");
	
	for(i = 0; i < sh; i++)
	{
		number = rand() % 10;
		fwrite(&number , 1 , sizeof(int) , file);
	}

	fclose(file);
	free(name);
	return;
}


void print()
{
	char name[N]; FILE *file;
	int read = 0, i;
	puts("Введите имя файла с его расширением (file.txt), не более 20 символов");
	//fflush(stdin);
	__fpurge(stdin);
	fgets(name, N, stdin);
	for (i = 0; i < N; i++)
	{
		if(name[i] == '\n')
		{
			name[i] = 0;
			break;
		}
	}
	file = fopen(name, "r");
	if (!file)
	{
		puts("Ошибка файла");
		return;
	}

	for (i = 0; i < MAX; i++)
	{
		if (i % N == 0)
		{
			printf("\n");
		}
		fread(&read, sizeof(int), 1, file);
		if (feof(file))
		{
			if (i == 0)
			{
				puts("Файл пуст");
			}
			break;
		}
		printf("%d ", read);
	}
	printf("\n");
	fclose(file);
	return;
}


int number(FILE *file, int amount)
{
	int i, read = 0;
	for (i = 0; i < MAX; i++)
	{
		fread(&read, sizeof(int), 1, file);
		if (feof(file))
		{
			break;
		}
		amount++;
	}
	return amount;
}


void cutout(FILE *file, FILE *file_w, int start, int end)
{
	int i, y, read1 = 0, read2 = 0, sh1 = 0, sh2 = 0;
	fseek(file, 0, 0);
	fseek(file_w, 0, 0);
	for (i = 0; i < MAX; i++)
	{
		if (start != 1)
		{
			fread(&read1, sizeof(int), 1, file);
		}
		if (feof(file))
		{
			break;
		}
		sh1++;
		if (sh1 + 1 == start || start == 1)
		{
			for (y = 0; y < MAX; y++)
			{
				fread(&read2, sizeof(int), 1, file_w);
				if (feof(file_w))
				{
					break;
				}
				sh2++;
				if (sh2 > end)
				{
					fwrite(&read2 , 1 , sizeof(int) , file);
				}
			}
			break;
		}
	}
}
