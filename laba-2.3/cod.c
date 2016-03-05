#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define H 100
#define P 20



const char *help = "--help";//
const char *add = "--add";//
const char *remov = "--remove";//
const char *removeall = "--remove-all";//
const char *print = "--print";//
const char *findname = "--find-name";//
const char *findsname = "--find-sname";//
const char *findlname = "--find-lname";//
const char *findgr = "--find-gr";//
const char *sortname = "--sort-name";//
const char *sortsname = "--sort-sname";//
const char *sortlname = "--sort-lname";//
const char *sortgr = "--sort-gr";//
const char *kol = "--count";//


int f_help()
{
	printf("\n--add == Добавить к списку дополнительную информацию, без потери того, что уже есть в файле\n");
	printf("\n--remove == Удалить определеннут строчку с данными\n");
	printf("\n--remove-all == Удалить все данные из файла\n");
	printf("\n--print == Показывает содержимое файла на экране\n");
	printf("\n--count == Показыват количество людей в списке в файле\n");
	printf("\n--find-name == Поиск по имени\n");
	printf("\n--find-sname == Поиск по фамилии\n");
	printf("\n--find-lname == Поиск по отчеству\n");
	printf("\n--find-gr == Поиск по группе\n");
	printf("\n--sort-name == Сортировать список по именам по алфавиту\n");
	printf("\n--sort-sname == Сортировать список по фамилии по алфавиту\n");
	printf("\n--sort-lname == Сортировать список по отчеству по алфавиту\n");
	printf("\n--sort-gr == Сортировати список по группе\n");

	return 0;
}


int fflushstdin()
{
	int q;

	do
	{
		q = getchar();
	} while (q != '\n' && q != EOF);

	return 0;
}


struct str
{
	char *name;
	char *sname;
	char *lname;
	char *gr;
};


int memory(int a, int l, struct str *s);
int fmemory(int a, int l, struct str *s);


int f_removeall()
{
	FILE *file;
	file = fopen("file.txt", "w");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}
	fclose(file);

	return 0;
}


int sort(struct str *s, int j, char *str)
{
	strcpy(str, s[j].name);
	strcpy(s[j].name, s[j + 1].name);
	strcpy(s[j + 1].name, str);
	strcpy(str, s[j].sname);
	strcpy(s[j].sname, s[j + 1].sname);
	strcpy(s[j + 1].sname, str);
	strcpy(str, s[j].lname);
	strcpy(s[j].lname, s[j + 1].lname);
	strcpy(s[j + 1].lname, str);
	strcpy(str, s[j].gr);
	strcpy(s[j].gr, s[j + 1].gr);
	strcpy(s[j + 1].gr, str);

	return 0;
}


int f_sort(int x)
{
	int sh = 0, a = 0, l = 0, i = 0, y = 0, j = 0;
	struct str *s;
	char *str;
	FILE *file;

	file = fopen("file.txt", "r");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}

	puts("\nВведите количество строчек в файле (если не знайте содержимое файла, введите 100 или более)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &a) || (a < 1) || (a > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!a || (a < 1) || (a > 1000));
	sh = 0; a += P;

	if (x != -1)
	{
		puts("\nВведите max символьную длину имя, фамилии, отчества или группы (min 15)(если не знайте содержимое файла, введите 30 или более)");
		do
		{
			if (sh == 1)
			{
				fflushstdin();
			}
			if (!scanf("%d", &l) || (l < 15) || (l > 1000))
			{
				puts("Ошибка ввода. Введите заново");
			}
			sh = 1;
		} while (!l || (l < 15) || (l > 1000));
		sh = 0;
	}
	else
	{
		l = P;
	}

	str = (char *)calloc((l + H), sizeof(char));
	//Выделение памяти
	s = (struct str *)malloc(a * sizeof(struct str));
	if (s == NULL)
	{
		printf("\nОшибка памяти\n");
		return 1;
	}
	memory(a, l, s);

	for (i = 0; i < a; i++)
	{
		fscanf(file, "%s %s %s %s", s[i].name, s[i].sname, s[i].lname, s[i].gr);
		if (!*s[i].name)
		{
			y = i;
			break;
		}
	}

	if (x == 1)
	{
		for (i = 1; i < y; i++)
		{
			for (j = 0; j < y - i; j++)
			{
				if (strcmp(s[j].name, s[j + 1].name) > 0)
				{
					sort(s, j, str);
				}
			}
		}
	}
	if (x == 2)
	{
		for (i = 1; i < y; i++)
		{
			for (j = 0; j < y - i; j++)
			{
				if (strcmp(s[j].sname, s[j + 1].sname) > 0)
				{
					sort(s, j, str);
				}
			}
		}
	}
	if (x == 3)
	{
		for (i = 1; i < y; i++)
		{
			for (j = 0; j < y - i; j++)
			{
				if (strcmp(s[j].lname, s[j + 1].lname) > 0)
				{
					sort(s, j, str);
				}
			}
		}
	}
	if (x == 4)
	{
		for (i = 1; i < y; i++)
		{
			for (j = 0; j < y - i; j++)
			{
				if (strcmp(s[j].gr, s[j + 1].gr) > 0)
				{
					sort(s, j, str);
				}
			}
		}
	}

	fclose(file);

	f_removeall();

	FILE *file1;
	file1 = fopen("file.txt", "rb+");
	if (!file1)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}

	for (i = 0; i < y; i++)
	{
		fprintf(file1, "%s %s %s %s\r\n", s[i].name, s[i].sname, s[i].lname, s[i].gr);
	}
	fclose(file1);

	//Очищение памяти
	fmemory(a, l, s);
	free(str);
	free(s);

	return 0;
}


int f_find(int x)
{
	int sh = 0, a = 0, l = 0, i = 0, u = 0;
	struct str *s;
	char *im;
	FILE *file;

	file = fopen("file.txt", "rb+");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}

	puts("\nВведите количество строчек в файле (если не знайте содержимое файла, введите 100 или более)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &a) || (a < 1) || (a > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!a || (a < 1) || (a > 1000));
	sh = 0; a += P;

	puts("\nВведите max символьную длину имя, фамилии, отчества или группы (min 15)(если не знайте содержимое файла, введите 30 или более)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &l) || (l < 15) || (l > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!l || (l < 15) || (l > 1000));
	sh = 0;

	if (x == 0)
	{
		puts("\nВведите количество букв в имени, которое хотите найти");
	}
	if (x == 1)
	{
		puts("\nВведите количество букв в фамилии, которую хотите найти");
	}
	if (x == 2)
	{
		puts("\nВведите количество букв в отчестве, которое хотите найти");
	}
	if (x == 3)
	{
		puts("\nВведите количество цифр в группе, которую хотите найти");
	}
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &u) || (u < 1) || (u > 100))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!u || (u < 1) || (u > 100));
	sh = 0;

	if (x != 3)
	{
		u *= 2;
	}

	im = (char *)malloc((u + 1) * sizeof(char));
	fflushstdin();
	puts("\nВведите информацию для поиска");
	fgets(im, u + 1, stdin);

	//Выделение памяти
	s = (struct str *)malloc(a * sizeof(struct str));
	if (s == NULL)
	{
		printf("\nОшибка памяти\n");
		return 1;
	}
	memory(a, l, s);

	for (i = 0; i < a; i++)
	{
		fscanf(file, "%s %s %s %s", s[i].name, s[i].sname, s[i].lname, s[i].gr);
		if (!*s[i].name)
		{
			break;
		}

		if (strcmp(s[i].name, im) == 0 && x == 0)
		{
			printf("\n%s %s %s %s\n", s[i].name, s[i].sname, s[i].lname, s[i].gr);
			sh = 2;
		}
		if (strcmp(s[i].sname, im) == 0 && x == 1)
		{
			printf("\n%s %s %s %s\n", s[i].name, s[i].sname, s[i].lname, s[i].gr);
			sh = 2;
		}
		if (strcmp(s[i].lname, im) == 0 && x == 2)
		{
			printf("\n%s %s %s %s\n", s[i].name, s[i].sname, s[i].lname, s[i].gr);
			sh = 2;
		}
		if (strcmp(s[i].gr, im) == 0 && x == 3)
		{
			printf("\n%s %s %s %s\n", s[i].name, s[i].sname, s[i].lname, s[i].gr);
			sh = 2;
		}
	}
	if (sh != 2)
	{
		puts("\nДанных нет. Либо вы ввели не верное количество букв или цифр\n");
	}

	fclose(file);

	//Очищение памяти
	fmemory(a, l, s);
	free(im);
	free(s);

	return 0;
}


int f_remov()
{
	int sh = 0, a = 0, l = 0, i = 0, ct;
	struct str *s;
	FILE *file;

	file = fopen("file.txt", "rb+");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}

	puts("\nВведите количество строчек в файле (если не знайте содержимое файла, введите 100 или более)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &a) || (a < 1) || (a > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!a || (a < 1) || (a > 1000));
	sh = 0; a += P;

	puts("\nВведите max символьную длину имя, фамилии, отчества или группы (min 15)(если не знайте содержимое файла, введите 30 или более)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &l) || (l < 15) || (l > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!l || (l < 15) || (l > 1000));
	sh = 0;

	puts("\nВведите номер строки, которую хотите удалить");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &ct) || (ct < 1) || (ct > a))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!ct || (ct < 1) || (ct > a));
	sh = 0;

	//Выделение памяти
	s = (struct str *)malloc(a * sizeof(struct str));
	if (s == NULL)
	{
		printf("\nОшибка памяти\n");
		return 1;
	}
	memory(a, l, s);

	for (i = 0; i < a; i++)
	{
		fscanf(file, "%s %s %s %s", s[i].name, s[i].sname, s[i].lname, s[i].gr);
		if (!*s[i].name)
		{
			break;
		}
	}

	fclose(file);

	f_removeall();

	FILE *file1;
	file1 = fopen("file.txt", "rb+");
	if (!file1)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}

	for (i = 0; i < a; i++)
	{
		if (ct - 1 == i)
		{
			i++;
		}
		if (!*s[i].name)
		{
			break;
		}
		fprintf(file1, "%s %s %s %s\r\n", s[i].name, s[i].sname, s[i].lname, s[i].gr);
	}
	fclose(file1);

	//Очищение памяти
	fmemory(a, l, s);
	free(s);

	return 0;
}


int f_add()
{
	int sh = 0, a = 0, l = 0, y = 0, x = -1, z = 0, i;
	struct str *s;
	FILE *file;
	char proverka[11] = "0123456789";

	file = fopen("file.txt", "rb+");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}

	puts("\nВведите количество строк, которые хотите добавить");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &a) || (a < 1) || (a > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!a || (a < 1) || (a > 1000));
	sh = 0;

	puts("\nВведите max символьную длину имя, фамилии, отчества или группы (min 15)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &l) || (l < 15) || (l > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!l || (l < 15) || (l > 1000));
	sh = 0; l += 30;

	//Выделение памяти
	s = (struct str *)malloc(a * sizeof(struct str));
	if (s == NULL)
	{
		printf("\nОшибка памяти\n");
		return 1;
	}
	memory(a, l, s);

	fseek(file, 0, 2);

	for (y = 0; y < a; y++)
	{
		fflushstdin();

		do
		{
			printf("\nВведите имя %d-го человека\n", y + 1);
			sh = 0;
			fgets(s[y].name, l, stdin);
			for (z = 0; z < 10; z++)
			{
				for (i = 0; i < l; i++)
				{
					if (proverka[z] == s[y].name[i])
					{
						puts("Ошибка ввода. Введите заново");
						sh = 1;
						free(s[y].name);
						s[y].name = (char *)calloc(l, sizeof(char));
					}
				}
			}
		}while (sh == 1);

		do
		{
			printf("\nВведите фамилию %d-го человека\n", y + 1);
			sh = 0;
			fgets(s[y].sname, l, stdin);
			for (z = 0; z < 10; z++)
			{
				for (i = 0; i < l; i++)
				{
					if (proverka[z] == s[y].sname[i])
					{
						puts("Ошибка ввода. Введите заново");
						sh = 1;
						free(s[y].sname);
						s[y].sname = (char *)calloc(l, sizeof(char));
					}
				}
			}
		}while (sh == 1);

		do
		{
			printf("\nВведите отчество %d-го человека\n", y + 1);
			sh = 0;
			fgets(s[y].lname, l, stdin);
			for (z = 0; z < 10; z++)
			{
				for (i = 0; i < l; i++)
				{
					if (proverka[z] == s[y].lname[i])
					{
						puts("Ошибка ввода. Введите заново");
						sh = 1;
						free(s[y].lname);
						s[y].lname = (char *)calloc(l, sizeof(char));
					}
				}
			}
		}while (sh == 1);

		printf("\nВведите группу %d-го человека\n", y + 1);
		fgets(s[y].gr, l, stdin);

		fprintf(file, "%s %s %s %s", s[y].name, s[y].sname, s[y].lname, s[y].gr);
	}

	fclose(file);

	//Очищение памяти
	fmemory(a, l, s);
	free(s);

	f_sort(x);

	return 0;
}


int f_print(int x)
{
	int sh = 0, a = 0, l = 0, i = 0;
	struct str *s;
	FILE *file;

	file = fopen("file.txt", "r");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		return 1;
	}

	puts("\nВведите количество строчек, которой хотите вывести на экран (если не знайте содержимое файла, введите 100 или более)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &a) || (a < 1) || (a > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!a || (a < 1) || (a > 1000));
	sh = 0; a += P;

	puts("\nВведите max символьную длину имя, фамилии, отчества или группы (min 15)(если не знайте содержимое файла, введите 30 или более)");
	do
	{
		if (sh == 1)
		{
			fflushstdin();
		}
		if (!scanf("%d", &l) || (l < 15) || (l > 1000))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!l || (l < 15) || (l > 1000));
	sh = 0;

	//Выделение памяти
	s = (struct str *)malloc(a * sizeof(struct str));
	if (s == NULL)
	{
		printf("\nОшибка памяти\n");
		return 1;
	}
	memory(a, l, s);

	for (i = 0; i < a; i++)
	{
		fscanf(file, "%s %s %s %s", s[i].name, s[i].sname, s[i].lname, s[i].gr);
		if (!*s[i].name)
		{
			if (x == 1)
			{
				printf("\nВсего в файле обнаружено %d строчка(ек) данных\n\n", i);
			}
			break;
		}
		if (x != 1)
		{
			printf("\n%s %s %s %s\n", s[i].name, s[i].sname, s[i].lname, s[i].gr);
		}
	}

	fclose(file);

	//Очищение памяти
	fmemory(a, l, s);
	free(s);

	return 0;
}


int main(int argc, char * argv[])
{
	int x = 0, z = 1;

	if (argv[1] != NULL)
	{
		do
		{
			if (strcmp(argv[z], help) == 0)
			{
				f_help();
			}
			if (strcmp(argv[z], print) == 0)
			{
				x = 0;
				f_print(x);
			}
			if (strcmp(argv[z], removeall) == 0)
			{
				f_removeall();
			}
			if (strcmp(argv[z], add) == 0)
			{
				f_add();
			}
			if (strcmp(argv[z], remov) == 0)
			{
				f_remov();
			}
			if (strcmp(argv[z], findname) == 0)
			{
				x = 0;
				f_find(x);
			}
			if (strcmp(argv[z], findsname) == 0)
			{
				x = 1;
				f_find(x);
			}
			if (strcmp(argv[z], findlname) == 0)
			{
				x = 2;
				f_find(x);
			}
			if (strcmp(argv[z], findgr) == 0)
			{
				x = 3;
				f_find(x);
			}
			if (strcmp(argv[z], sortname) == 0)
			{
				x = 1;
				f_sort(x);
			}
			if (strcmp(argv[z], sortsname) == 0)
			{
				x = 2;
				f_sort(x);
			}
			if (strcmp(argv[z], sortlname) == 0)
			{
				x = 3;
				f_sort(x);
			}
			if (strcmp(argv[z], sortgr) == 0)
			{
				x = 4;
				f_sort(x);
			}
			if (strcmp(argv[z], kol) == 0)
			{
				x = 1;
				f_print(x);
			}
			z++;
		} while (argv[z] != NULL);
	}

	return 0;
}


int memory(int a, int l, struct str *s)
{
	int i = 0, y = 0;
	l += H;

	//Выделение памяти
	for (i = 0; i < a; i++)
	{
		s[i].name = (char *)calloc(l, sizeof(char));
		if (!s[i].name)
		{
			printf("\nОшибка памяти\n");
			for (y = i - 1; y >= 0; y--)
			{
				free(s[y].name);
			}

			return 1;
		}
	}

	for (i = 0; i < a; i++)
	{
		s[i].sname = (char *)calloc(l, sizeof(char));
		if (!s[i].sname)
		{
			printf("\nОшибка памяти\n");
			for (y = i - 1; y >= 0; y--)
			{
				free(s[y].sname);
			}
			for (y = 0; y < a; y++)
			{
				free(s[y].name);
			}

			return 1;
		}
	}

	for (i = 0; i < a; i++)
	{
		s[i].lname = (char *)calloc(l, sizeof(char));
		if (!s[i].lname)
		{
			printf("\nОшибка памяти\n");
			for (y = i - 1; y >= 0; y--)
			{
				free(s[y].lname);
			}
			for (y = 0; y < a; y++)
			{
				free(s[y].sname);
			}
			for (y = 0; y < a; y++)
			{
				free(s[y].name);
			}

			return 1;
		}
	}

	for (i = 0; i < a; i++)
	{
		s[i].gr = (char *)calloc(l, sizeof(char));
		if (!s[i].gr)
		{
			printf("\nОшибка памяти\n");
			for (y = i - 1; y >= 0; y--)
			{
				free(s[y].gr);
			}
			for (y = 0; y < a; y++)
			{
				free(s[y].lname);
			}
			for (y = 0; y < a; y++)
			{
				free(s[y].sname);
			}
			for (y = 0; y < a; y++)
			{
				free(s[y].name);
			}

			return 1;
		}
	}
	//Конец выделения памяти

	return 0;
}


int fmemory(int a, int l, struct str *s)
{
	int y = 0;

	//Очищение памяти
	for (y = 0; y < a; y++)
	{
		free(s[y].gr);
	}
	for (y = 0; y < a; y++)
	{
		free(s[y].name);
	}
	for (y = 0; y < a; y++)
	{
		free(s[y].sname);
	}
	for (y = 0; y < a; y++)
	{
		free(s[y].lname);
	}
	//Конец очищения памяти

	return 0;
}
