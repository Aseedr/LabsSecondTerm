#include "laba5.h"

struct der *sozd(struct der *dr)
{
	int i = 0;
	if (dr)
	{
		puts("Бинарное дерево уже создано");
		return(dr);
	}
	dr = (struct der *)calloc(1, sizeof(struct der));
	if (!dr)
	{
		puts("Ошибка памяти!");
		return NULL;
	}
	puts("Введите имя вашего файла");
	dr->inf = (char *)calloc(1, sizeof(char)* N);
	if (!dr->inf)
	{
		puts("Ошибка памяти!");
		free(dr);
		return NULL;
	}
	//fflush(stdin);
	__fpurge(stdin);
	fgets(dr->inf, N, stdin);
	if (dr->inf[0] == '\n')
	{
		free(dr->inf);
		free(dr);
		return NULL;
	}
	for (i = 0; i < N; i++)
	{
		if(dr->inf[i] == ' ')
			dr->inf[i] = '_';
		if(dr->inf[i] == '\n')
			break;
	}
	
	puts("Введите год создание этого файла (пример - 2015)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &dr->god) || (dr->god < 1) || (dr->god > 2015))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!dr->god || (dr->god < 1) || (dr->god > 2015));

	puts("Введите месяц создания этого файла (пример - 3)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &dr->mec) || (dr->mec < 1) || (dr->mec > 12))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!dr->mec || (dr->mec < 1) || (dr->mec > 12));

	puts("Введите день создания этого файла (пример - 23)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &dr->den) || (dr->den < 1) || (dr->den > 31))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!dr->den || (dr->den < 1) || (dr->den > 31));
	GP++;
	return dr;
}


void see(struct der *dr1)
{
	int i, sh;
	sh = 0;
	if (dr1)
	{
		for (i = 0; i < PP; i++)
		{
			if (GG[i] == dr1)
			{
				sh = 1;
			}
		}
		if (sh == 0)
		{
			printf("Файл: %s	дата создания: %d.%d.%d\n", dr1->inf, dr1->den, dr1->mec, dr1->god);
		}
		if (dr1->l)
		{
			see(dr1->l);
		}
		if (dr1->r)
		{
			see(dr1->r);
		}
	}
	else
	{
		puts("Бинарное дерево еще не создано");
	}
}


void add(struct der *dr)
{
	struct der *dr1, *dr2;
	char *st;
	int k, i, flag = 0;
	int ind;
	if (!dr)
	{
		puts("Нет корня дерева");
		return;
	}
	
	puts("Введите имя файла в новый узел дерева");
	st = (char *)calloc(1, sizeof(char)* N);
	if (!st)
	{
		puts("Ошибка памяти!");
		return;
	}
	//fflush(stdin);
	__fpurge(stdin);
	fgets(st, N, stdin);
	if (st[0] == '\n')
	{
		free(st);
		return;
	}
	for (i = 0; i < N; i++)
	{
		if(st[i] == ' ')
			st[i] = '_';
		if(st[i] == '\n')
			break;
	}
	dr1 = dr;
	ind = 0;
	do
	{
		for (i = 0; i < N; i++)
		{
			if (st[i] == '\n')
				break;
			if (st[i] != dr1->inf[i])
				flag++;
		}
		if (!(k = strcmp(st, dr1->inf)) || flag == 0)
		{
			puts("Файл с таким именем уже существует, либо существовал в дереве и требуется очистка");
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
	GP++;
	free(st);
	vvod(dr2);
}


void vvod(struct der *dr2)
{
	puts("Введите год создание этого файла (пример - 2015)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &dr2->god) || (dr2->god < 1) || (dr2->god > 2015))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!dr2->god || (dr2->god < 1) || (dr2->god > 2015));

	puts("Введите месяц создания этого файла (пример - 3)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &dr2->mec) || (dr2->mec < 1) || (dr2->mec > 12))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!dr2->mec || (dr2->mec < 1) || (dr2->mec > 12));

	puts("Введите день создания этого файла (пример - 23)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &dr2->den) || (dr2->den < 1) || (dr2->den > 31))
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!dr2->den || (dr2->den < 1) || (dr2->den > 31));
}


struct der *del(struct der *dr)
{
	struct der *dr1, *dr2;
	char *st;
	int k;
	int ind;
	int i, flag = 0;
	if (!dr)
	{
		puts("Дерево еще не создано");
		return NULL;
	}
	puts("Введите информацию для поиска удаляемого узла");
	st = (char *)calloc(1, sizeof(char) * N);
	if (!st)
	{
		puts("Ошибка памяти!");
		return NULL;
	}
	//fflush(stdin);
	__fpurge(stdin);
	fgets(st, N, stdin);
	if (!*st)
	{
		free(st);
		return NULL;
	}
	dr2 = dr1 = dr;
	ind = 0;
	do
	{
		flag = 0;
		for (i = 0; i < N; i++)
		{
			if (st[i] == '\n')
				break;
			if (st[i] != dr1->inf[i])
				flag++;
		}
		if (!(k = strcmp(st, dr1->inf)) || flag == 0)
		{
			GG[PP] = dr1;
			PP++; GP--;
			ind = 1;
		}
		if (k < 0)
		{
			if (dr1->l)
			{
				dr2 = dr1;
				dr1 = dr1->l;
			}
			else
			{
				ind = 1;
			}
		}
		if (k > 0)
		{
			if (dr1->r)
			{
				dr2 = dr1;
				dr1 = dr1->r;
			}
			else
			{
				ind = 1;
			}
		}
	} while (!ind);
	free(st);
	if (k && flag != 0)
	{
		puts("Требуемый узел не найден");
		return dr;
	}
}


void f_free(struct der *dr)
{
	if (dr == NULL)
	{
		return;
	}
	else
	{
		f_free(dr->l);
		f_free(dr->r);
		free(dr->inf);
		free(dr);
	}
}
