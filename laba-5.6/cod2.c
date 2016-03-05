#include "laba5.h"

void save(struct der *dr, FILE *file)
{
	int i, sh;
	sh = 0;
	if (dr)
	{
		for (i = 0; i < PP; i++)
		{
			if (GG[i] == dr)
			{
				sh = 1;
			}
		}
		if (sh == 0)
		{
			fprintf(file, "%s\r\n%d\r\n%d\r\n%d\r\n\r\n", dr->inf, dr->god, dr->mec, dr->den);
		}
		if (dr->l)
		{
			save(dr->l, file);
		}
		if (dr->r)
		{
			save(dr->r, file);
		}
	}
	else
	{
		puts("Бинарное дерево еще не создано");
	}
}


struct der *read(struct der *dr, FILE *file)
{
	dr = (struct der *)calloc(1, sizeof(struct der));
	if (!dr)
	{
		puts("Ошибка памяти!");
		return NULL;
	}

	dr->inf = (char *)calloc(1, sizeof(char)* N);
	if (!dr->inf)
	{
		puts("Ошибка памяти!");
		free(dr);
		return NULL;
	}

	fscanf(file, "%s", dr->inf);

	fscanf(file, "%d", &dr->god);

	fscanf(file, "%d", &dr->mec);

	fscanf(file, "%d", &dr->den);
	
	return dr;
}


void read_add(struct der *dr, FILE *file)
{
	struct der *dr1, *dr2;
	int k;
	int ind;	
	char *st;
	st = (char *)calloc(1, sizeof(char)* N);
	if (!st)
	{
		puts("Ошибка памяти!");
		return;
	}
	fscanf(file, "%s", st);

	dr1 = dr;
	ind = 0;
	do
	{
		if (!(k = strcmp(st, dr1->inf)))
		{
			free(st);
			return;
		}
		else
		{
			if (k < 0)
			{
				if (dr1->l)
				{
					dr1 = dr1->l;
				}
				else
				{
					ind = 1;
				}
			}
			else
			{
				if (dr1->r)
				{
					dr1 = dr1->r;
				}
				else
				{
					ind = 1;
				}
			}
		}
	} while (ind == 0);
	dr2 = (struct der *)calloc(1, sizeof(struct der));
	if (!dr2)
	{
		puts("Ошибка памяти!");
		free(st);
		return;
	}
	if (k < 0)
	{
		dr1->l = dr2;
	}
	else
	{
		dr1->r = dr2;
	}
	dr2->inf = (char *)calloc(1, sizeof(char)* N);
	if (!dr2->inf)
	{
		puts("Ошибка памяти!");
		free(dr2);
		free(st);
		return;
	}
	strcpy(dr2->inf, st);
	free(st);
	fscanf(file, "%d%d%d", &dr2->god, &dr2->mec, &dr2->den);
}


struct der *del_op(struct der *dr)
{
	struct der *dr1, *dr2;
	int k;
	int ind;
	int a = 0, b = 0, c = 0, X = 0;

	if (!dr)
	{
		puts("Дерево еще не создано");
		return NULL;
	}

	puts("Введите год (пример - 2015)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &a) || (a < 1) || (a > 2015))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!a || (a < 1) || (a > 2015));

	puts("Введите месяц (пример - 3)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &b) || (b < 1) || (b > 12))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!b || (b < 1) || (b > 12));

	puts("Введите день (пример - 23)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &c) || (c < 1) || (c > 31))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!c || (c < 1) || (c > 31));

	X = a * 10000 + b * 100 + c;
	del_op_el(dr, X);
	return dr;
}


void del_op_el(struct der *dr, int X)
{
	int i, sh;
	sh = 0;
	if (dr)
	{
		for (i = 0; i < PP; i++)
		{
			if (GG[i] == dr)
			{
				sh = 1;
			}
		}
		if (sh == 0)
		{
			if (dr->god * 10000 + dr->mec * 100 + dr->den < X)
			{
				GG[PP] = dr;
				PP++; GP--;
			}
		}
		if (dr->l)
		{
			del_op_el(dr->l, X);
		}
		if (dr->r)
		{
			del_op_el(dr->r, X);
		}
	}
}
