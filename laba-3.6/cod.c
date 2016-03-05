#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>


#define N 1000
const char *proverka = "qwertyuiopasdfghjklmnbvcxzQWERTYUIOPASDFGHJKLMNBVCXZ/*-+^:";

int fflushstdin()
{
	int q;

	do
	{
		q = getchar();
	} while (q != '\n' && q != EOF);

	return 0;
}

int f_proverka(char *s, char *sf)
{
	int x1, x2, sh = 0, i, y;

	do
	{
		x1 = 0; x2 = 0;
		puts("Введите выражение в префиксной форме без пробелов. Пример - '^xy':");
		sh = 0;
		fgets(s, N, stdin);
		for (i = 0; i < N; i++)
		{
			sh = 0;
			for (y = 0; y < 58; y++)
			{
				if (s[i] == proverka[y] || s[i] == 0 || s[i] == '\n')
				{
					sh = 2;
				}
				if (y == 57 || s[0] == '\n')
				{
					if (sh == 0 || s[0] == '\n')
					{
						puts("Ошибка ввода. Введите заново");
						sh = 1;
						free(s);
						s = (char *)calloc(N, sizeof(char));
						break;
					}
				}
			}
			if (s[0] == 0)
			{
				break;
			}
		}
	

		for (i = 0; i < N; i++)
		{
			if (s[i] == 0 || s[i] == '\n')
			{
				break;
			}
			if (s[i] == '/' || s[i] == '*' || s[i] == '-' || s[i] == '+' || s[i] == '^' || s[i] == ':')
			{
				x1++;
			}
			else
			{
				x2++;
			}
		}
		if (((x2 == 0 || x1 == 0) && sh != 1) || ((x2 - 1) != x1 && sh != 1))
		{
			puts("Ошибка ввода. Введите заново");
			sh = 1;
			free(s);
			s = (char *)calloc(N, sizeof(char));
		}
	} while (sh == 1);

	strcpy(sf, s);
	free(s);
	return 0;
}

int pref_to_postf(char *sf, char *res)
{
	char tmp[N];
	
	res[0] = sf[0];
	res[1] = 0;

	strcpy(tmp, res);

	sf++;

	if (!isalpha(res[0]))
	{
		pref_to_postf(sf, res);
		pref_to_postf(sf + strlen(res), res + strlen(res));
		strcat(res, tmp);
	}

	return 0;
}


int main()
{
	char *s, res[N], *sf;
	int a = 0, sh = 0;

	do
	{
		s = (char *)calloc(N, sizeof(char));
		if (!s)
		{
			puts("Ошибка памяти");
			return 0;
		}
		sf = (char *)calloc(N, sizeof(char));
		if (!sf)
		{
			puts("Ошибка памяти");
			return 0;
		}
		f_proverka(s, sf);


		puts("Это же выражение в постфиксной форме:");
		pref_to_postf(sf, res);

		if ((strlen(sf) - 1) == strlen(res))
		{
			printf("%s\n", res);
		}
		else
		{
			puts("Неполучилось:-)");
		}
	
		free(sf);

		puts("Завершить программу (1 - да)(2 - нет)");
		do
		{
			if (sh == 1)
			{
				fflushstdin();
			}
			if (!scanf("%d", &a) || (a < 1) || (a > 2))
			{
				puts("Ошибка ввода. Введите заново");
			}
			sh = 1;
		} while (!a || (a < 1) || (a > 2));
		sh = 0;
		fflushstdin();
	} while(a == 2);

	return 0;
}
