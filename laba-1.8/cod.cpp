#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int fflushstdin()
{
	int q;
	do
	{
		q = getchar();
	} while (q != '\n' && q != EOF);
}

struct str
{
	char tov[20];
	char strana[20];
	int shtuk[1];
};

int main()
{
	struct str *s;
	setlocale(LC_ALL, "Russian");
	int a = 0, i = 0, y = 0, x = 0, sh = 0, end = 0, j = 0;
	char c[20];
	char str1[20], str2[20];

	do
	{

		puts("\nВведите количество товаров (min 2)(max 10)");
		do
		{
			if (sh == 1)
			{
				fflushstdin();
			}
			if (!scanf("%d", &a) || (a < 2) || (a > 10))
			{
				puts("Ошибка ввода. Введите заново");
			}
			sh = 1;
		} while (!a || (a < 2) || (a > 10));
		sh = 0;

		s = (struct str *)calloc(a, sizeof(struct str));
		if (s == NULL)
		{
			printf("\nОшибка памяти");
			return 0;
		}

		for (i = 0; i < a; i++)
		{
			fflushstdin();
			printf("\nВведите название %d-го товара\n", i + 1);
			fgets(s[i].tov, 20, stdin);
			printf("\nВведите страну, импортирующую %d-й товар\n", i + 1);
			fgets(s[i].strana, 20, stdin);
			printf("\nВведите объем поставки %d-го товара\n", i + 1);
			do
			{
				if (sh == 1)
				{
					fflushstdin();
				}
				if (!scanf("%d", &s[i].shtuk[0]) || (s[i].shtuk[0] < 1) || (s[i].shtuk[0] > 2147483647))
				{
					puts("Ошибка ввода. Введите заново");
				}
				sh = 1;
			} while (!s[i].shtuk[0] || (s[i].shtuk[0] < 1) || (s[i].shtuk[0] > 2147483647));
			sh = 0;
		}

		//сортировка по товару по алфавиту
		for (i = 1; i < a; i++)
		{
			for (j = 0; j < a - i; j++)
			{
				if (strcmp(s[j].tov, s[j + 1].tov) > 0)
				{
					strcpy(str1, s[j].tov);
					strcpy(s[j].tov, s[j + 1].tov);
					strcpy(s[j + 1].tov, str1);

					strcpy(str2, s[j].strana);
					strcpy(s[j].strana, s[j + 1].strana);
					strcpy(s[j + 1].strana, str2);

					x = s[j].shtuk[0];
					s[j].shtuk[0] = s[j + 1].shtuk[0];
					s[j + 1].shtuk[0] = x;
				}
			}
		}
		x = 0;


		printf("\nВведенная информация\n\n");
		printf("\n Товар			Страна			Объем\n");
		for (i = 0; i < a; i++)
		{
			printf("________________________________________________________________________");
			printf("\n %s", s[i].tov);
			printf("			%s", s[i].strana);
			printf("						%d\n", s[i].shtuk[0]);
		}
		printf("________________________________________________________________________");

		printf("\n\n\n\nВведите товар для поиска\n");
		fflushstdin();
		fgets(c, 20, stdin);
		printf("\n\n Страна(ы)		Объем");
		for (i = 0; i < a; i++)
		{
			if (!strcmp(s[i].tov, c))
			{
				x += s[i].shtuk[0];
				printf("\n %s", s[i].strana);
			}
		}
		if (x == 0)
		{
			printf("\n\n	Данных нет");
		}
		else
		{
			printf("			%d\n", x);
		}

		printf("\n\nЗавершить программу? (1 - нет)(2 - да)\n");
		do
		{
			if (sh == 1)
			{
				fflushstdin();
			}
			if (!scanf("%d", &end) || (end < 1) || (end > 2))
			{
				puts("Ошибка ввода. Введите заново");
			}
			sh = 1;
		} while (!end || (end < 1) || (end > 2));
		sh = 0;
		free(s);
		x = 0;

	} while (end == 1);

	return 0;
}
