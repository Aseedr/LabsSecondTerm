#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define N 10
#define P 9
#define M 26
int maks_shis_stoia;
const char *str1 = "1234567890";
const char *str2 = "QWERTYUIOPLKJHGFDSAZXCVBNM";

struct turn
{
	int stoian;
	char *nomer_t;
	struct turn *nx;
};

void del_el(struct turn **h, struct turn **t, int flag);
void add(struct turn **, struct turn **);
void see_turn(struct turn *h, int i);
void print_turn(struct turn *h, FILE *file);
void del_turn(struct turn **h, struct turn **t);
void add_f(struct turn **, struct turn **, FILE *file);

struct str
{
	int mest;
	int mest_sv;
	char **nomer;
};

void del_op_el(struct str *s);
void dobavlenie(struct str *s, struct turn **h, struct turn **t, struct turn *b, int qqq);
void zapolnenie(struct str *s);
void videlenie(struct str *s, int q);
void see(struct str *s, struct turn *h, int q, int ooo);
void vvod_nom(struct str *s);
void f_free(struct str *s);
void menu(struct str *s, FILE *file);
void add_stoian(struct str *s);
void vivod(struct str *s, struct turn *h);

void main()
{
	setlocale(LC_ALL, "Russian");
	struct str *s;
	int sh = 0;
	
	FILE *file;
	int i = 0, q = 0, y = 0;

	file = fopen("file.txt", "rb+");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		file = fopen("file.txt", "w");
		puts("Введите количество автостоянок в городе");
		do
		{
			if (sh == 1)
			{
				//fflush(stdin);
				__fpurge(stdin);
			}
			if (!scanf("%d", &maks_shis_stoia) || (maks_shis_stoia < 1) || (maks_shis_stoia > 100))
			{
				puts("Ошибка ввода, либо слишком много стоянок. Введите заново");
			}
			sh = 1;
		} while (!maks_shis_stoia || (maks_shis_stoia < 1) || (maks_shis_stoia > 100));
		sh = 0;

		s = (struct str *)malloc((maks_shis_stoia + M) * sizeof(struct str));
		if (!s)
		{
			puts("Ошибка памяти");
			return;
		}
		zapolnenie(s);
	}
	else
	{
		fscanf(file, "%d", &maks_shis_stoia);
		s = (struct str *)malloc((maks_shis_stoia + M) * sizeof(struct str));
		if (!s)
		{
			puts("Ошибка памяти");
			return;
		}
		for (i = 0; i < maks_shis_stoia; i++)
		{
			fscanf(file, "%d %d", &s[i].mest, &s[i].mest_sv);
		}
		videlenie(s, q);
		for (i = 0; i < maks_shis_stoia; i++)
		{
			for (y = 0; y < s[i].mest - s[i].mest_sv; y++)
			{
				fscanf(file, "%s", s[i].nomer[y]);
			}
		}
	}

	menu(s, file);

	f_free(s);
	free(s);
	return;
}


void menu(struct str *s, FILE *file)
{
	int flag = 0, sh = 1, q = 0, ooo = 0, qqq = 0;
	struct turn *h, *t, *a;
	h = t = a = NULL;

	if (file)
	{
		fscanf(file, "%d", &sh);
		do
		{
			if(sh == 0)
			{
				break;
			}
			add_f(&h, &t, file);
			sh--;
		} while (sh != 0);
	}
	sh = 0;

	while (1)
	{
		q = 0;
		ooo = 0;
		qqq = 0;
		puts("\n\nВыберите вид операции:");
		puts("	1 - Добавить автомобиль на стоянку");//
		puts("	2 - Добавить новую автостоянку");//
		puts("	3 - Убрать автомобиль с автостоянки");//
		puts("	4 - Просмотреть состояние всех стоянок и очередей на них");//
		puts("	5 - Просмотреть сосятояние на определенной стоянке и очереди на ней");//
		puts("	6 - Завершить работу с сохранением текущего состояния в базе\n");
		do
		{
			if (sh == 1)
			{
				//fflush(stdin);
				__fpurge(stdin);
			}
			if (!scanf("%d", &flag) || (flag < 1) || (flag > 7))
			{
				puts("Ошибка ввода. Введите заново");
			}
			sh = 1;
		} while (!flag || (flag < 1) || (flag > 7));

		switch (flag)
		{
		case 1:
		{
				  add(&h, &t);
				  struct turn *b = h;
				  dobavlenie(s, &h, &t, b, qqq);
				  break;
		}
		case 2: add_stoian(s);  break;
		case 3:
		{
				  qqq = 1;
				  struct turn *b = h;
				  del_op_el(s);
				  dobavlenie(s, &h, &t, b, qqq);
				  break;
		}
		case 5:
		{
				  puts("Введите номер стоянки, которую хотите посмотреть");
				  do
				  {
					  if (sh == 1)
					  {
						  //fflush(stdin);
						  __fpurge(stdin);
					  }
					  if (!scanf("%d", &q) || (q < 1) || (q > maks_shis_stoia))
					  {
						  puts("Ошибка ввода, либо слишком много мест. Введите заново");
					  }
					  sh = 1;
				  } while (!q || (q < 1) || (q > maks_shis_stoia));
				  sh = 0; q--;	ooo = 1;
				  see(s, h, q, ooo);
				  break;
		}
		case 4: see(s, h, q, ooo); break;
		case 6: vivod(s, h); del_turn(&h, &t); return;
		}
	}
}


void add_stoian(struct str *s)
{
	int sh = 0, q;

	maks_shis_stoia++;
	q = maks_shis_stoia - 1;

	printf("\nВведите количество парковочных мест на парковке № %d\n", maks_shis_stoia);
	do
	{
		if (sh == 1)
		{
			//fflush(stdin);
			__fpurge(stdin);
		}
		if (!scanf("%d", &s[q].mest) || (s[q].mest < 1) || (s[q].mest > 20000))
		{
			puts("Ошибка ввода, либо слишком много мест. Введите заново");
		}
		sh = 1;
	} while (!s[q].mest || (s[q].mest < 1) || (s[q].mest > 20000));
	sh = 0;

	s[q].mest_sv = s[q].mest;

	videlenie(s, q);
}


void add(struct turn **h, struct turn **t)
{
	struct turn *n;
	int sh = 0, flag = 0, k = 0, z = 0;

	n = (struct turn *)calloc(1, sizeof(struct turn));
	if (!n)
	{
		puts("Ошибка памяти");
		return;
	}

	puts("Введите номер стоянки на которую хотите поставить авто");
	do
	{
		if (sh == 1)
		{
			//fflush(stdin);
			__fpurge(stdin);
		}
		if (!scanf("%d", &n->stoian) || (n->stoian < 1) || (n->stoian > maks_shis_stoia))
		{
			puts("Введен ошибочный номер стоянки. Введите заново");
		}
		sh = 1;
	} while (!n->stoian || (n->stoian < 1) || (n->stoian > maks_shis_stoia));
	sh = 0;

	n->nomer_t = (char *)calloc(N + 1, sizeof(char));
	if (!n->nomer_t)
	{
		puts("Ошибка памяти");
		free(n);
		return;
	}

	puts("Введите номер авто");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		fgets(n->nomer_t, N + 1, stdin);
		sh = 0;
		for (k = 0; k < P; k++)
		{
			if (k == 0 || k == 1 || k == 2 || k == 3 || k == 8)
			{
				for (z = 0; z < N; z++)
				{
					if (n->nomer_t[k] == str1[z])
					{
						sh++;
						if (k == 8 && z > 6)
						{
							sh--;
						}
					}
				}
			}
			if (k == 4 || k == 7)
			{
				if (n->nomer_t[k] == '-')
				{
					sh++;
				}
			}
			if (k == 5 || k == 6)
			{
				for (z = 0; z < M; z++)
				{
					if (n->nomer_t[k] == str2[z])
					{
						sh++;
					}
				}
			}
		}
		if (sh != 9 || n->nomer_t[9] != '\n')
		{
			puts("Ошибка ввода. Введите заново");
			free(n->nomer_t);
			n->nomer_t = (char *)calloc(N + 1, sizeof(char));
		}
	} while (sh != 9 || n->nomer_t[9] != '\n');

	if (!*h)
	{
		*h = *t = n;
	}
	else
	{
		(*t)->nx = n;
		*t = n;
	}
}


void f_free(struct str *s)
{
	int i, y;
	for (i = 0; i < maks_shis_stoia; i++)
	{
		for (y = 0; y < s[i].mest; y++)
		{
			free(s[i].nomer[y]);
		}
		free(s[i].nomer);
	}
}


void vvod_nom(struct str *s)
{
	int i, y, k, z, sh = 0;
	for (i = 0; i < maks_shis_stoia; i++)
	{
		if (s[i].mest - s[i].mest_sv > 0)
		{
			printf("\nВведите список номеров (пример: 1234-ab-1) нашина на стоянке № %d\n", i + 1);
		}
		for (y = 0; y < s[i].mest - s[i].mest_sv; y++)
		{
			do
			{
				//fflush(stdin);
				__fpurge(stdin);
				fgets(s[i].nomer[y], N + 1, stdin);
				sh = 0;
				for (k = 0; k < P; k++)
				{
					if (k == 0 || k == 1 || k == 2 || k == 3 || k == 8)
					{
						for (z = 0; z < N; z++)
						{
							if (s[i].nomer[y][k] == str1[z])
							{
								sh++;
								if (k == 8 && z > 6)
								{
									sh--;
								}
							}
						}
					}
					if (k == 4 || k == 7)
					{
						if (s[i].nomer[y][k] == '-')
						{
							sh++;
						}
					}
					if (k == 5 || k == 6)
					{
						for (z = 0; z < M; z++)
						{
							if (s[i].nomer[y][k] == str2[z])
							{
								sh++;
							}
						}
					}
				}
				if (sh != 9 || s[i].nomer[y][9] != '\n')
				{
					puts("Ошибка ввода. Введите заново");
					free(s[i].nomer[y]);
					s[i].nomer[y] = (char *)calloc(N + 1, sizeof(char));
				}
			} while (sh != 9 || s[i].nomer[y][9] != '\n');
		}
	}
}


void videlenie(struct str *s, int q)
{
	int i, y, k;
	for (i = q; i < maks_shis_stoia; i++)
	{
		s[i].nomer = (char **)calloc(s[i].mest, sizeof(char *));
		if (!s[i].nomer)
		{
			puts("Ошибка памяти!");
			for (y = i - 1; y >= 0; y--)
			{
				for (k = 0; k < s[i].mest; k++)
				{
					free(s[y].nomer[k]);
				}
				free(s[y].nomer);
			}
			free(s);
			return;
		}
		for (y = 0; y < s[i].mest; y++)
		{
			s[i].nomer[y] = (char *)calloc(N + 1, sizeof(char));
			if (!s[i].nomer[y])
			{
				puts("Ошибка памяти!");
				for (k = y - 1; k >= 0; k--)
				{
					free(s[i].nomer[k]);
				}
				for (y = i - 1; y >= 0; y--)
				{
					for (k = 0; k < s[i].mest; k++)
					{
						free(s[y].nomer[k]);
					}
					free(s[y].nomer);
				}
				free(s);
				return;
			}
		}
	}
}


void zapolnenie(struct str *s)
{
	int sh = 0, b = 0, i, q = 0;

	for (i = 0; i < maks_shis_stoia; i++)
	{
		printf("\nВведите количество парковочных мест на парковке № %d\n", i + 1);
		do
		{
			if (sh == 1)
			{
				//fflush(stdin);
				__fpurge(stdin);
			}
			if (!scanf("%d", &s[i].mest) || (s[i].mest < 1) || (s[i].mest > 20000))
			{
				puts("Ошибка ввода, либо слишком много мест. Введите заново");
			}
			sh = 1;
		} while (!s[i].mest || (s[i].mest < 1) || (s[i].mest > 20000));
		sh = 0;
		printf("\nВведите количество свободных парковочных мест на парковке № %d\n", i + 1);
		do
		{
			if (sh == 1)
			{
				//fflush(stdin);
				__fpurge(stdin);
			}
			if (!scanf("%d", &s[i].mest_sv) || (s[i].mest_sv < 0) || (s[i].mest_sv > s[i].mest))
			{
				puts("Ошибка ввода, либо слишком много свободных мест. Введите заново");
			}
			sh = 1;
		} while ((s[i].mest_sv < 0) || (s[i].mest_sv > s[i].mest));
		sh = 0;
	}

	videlenie(s, q);

	vvod_nom(s);
}


void see(struct str *s, struct turn *h, int q, int ooo)
{
	int i, y;
	for (i = q; i < maks_shis_stoia; i++)
	{
		puts("\n_____________________________________");
		printf("\nСостояние парковки № %d\n", i + 1);
		printf("\nЗанято - %d	Свободно - %d\n", s[i].mest - s[i].mest_sv, s[i].mest_sv);
		printf("\nСписок номеров машин на стоянке:\n");
		for (y = 0; y < s[i].mest; y++)
		{
			if (*s[i].nomer[y])
			{
				printf("%s\n", s[i].nomer[y]);
			}
			if (s[i].mest - s[i].mest_sv == 0)
			{
				printf("Машин нету\n");
				break;
			}
		}
		puts("\nСписок номеров машин в очереди:");
		see_turn(h, i);
		if (ooo == 1)
		{
			break;
		}
	}
	puts("_____________________________________");
}


void see_turn(struct turn *h, int i)
{
	int sh = 0;

	if (!h)
	{
		puts("Очередь пуста\n");
		return;
	}
	do
	{
		if (h->stoian == i + 1)
		{
			printf("%s\n", h->nomer_t);
			sh = 1;
		}
		h = h->nx;
	} while (h);
	if (sh == 0)
	{
		puts("Очередь пуста\n");
	}
	return;
}


void dobavlenie(struct str *s, struct turn **h, struct turn **t, struct turn *b, int qqq)
{
	int i = 0, d = 0, flag = 0;
	struct turn *a = b;
	char str[N + 1];

	if (!b)
	{
		return;
	}

	do
	{
		if (flag == 1)
		{
			break;
		}

		i = b->stoian / 10;
		//printf("%d", i);
		if (s[i].mest_sv > 0)
		{
			strcpy(s[i].nomer[s[i].mest - s[i].mest_sv], b->nomer_t);
			s[i].mest_sv--;
			d = a->stoian;
			strcpy(str, a->nomer_t);
			a->stoian = b->stoian;
			strcpy(a->nomer_t, b->nomer_t);
			b->stoian = d;
			strcpy(b->nomer_t, str);

			struct turn *p;
			if (*t == *h)
			{
				free(*h);
				*t = *h = NULL;
				flag = 1;
				return;
			}
			p = (*h)->nx;
			free(*h);
			*h = p;

			if (qqq == 1)
			{
				break;
			}
		}
		b = b->nx;
	} while (b);
}


void del_op_el(struct str *s)
{
	int sh = 0, a = 0, i, y;
	char str[N + 1];

	puts("Введите номер стоянки с которой надо удалить авто");
	do
	{
		if (sh == 1)
		{
			//fflush(stdin);
			__fpurge(stdin);
		}
		if (!scanf("%d", &a) || (a < 1) || (a > maks_shis_stoia))
		{
			puts("Ошибка ввода. Введите заново");
		}
		sh = 1;
	} while (!a || (a < 1) || (a > maks_shis_stoia));
	sh = 0; a--;

	if (s[a].mest == s[a].mest_sv)
	{
		puts("Машин на стоянке нету");
		return;
	}

	puts("Введите номер машины для удаление");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		fgets(str, N, stdin);
		for (i = 0; i < s[a].mest - s[a].mest_sv; i++)
		{
			if (strcmp(str, s[a].nomer[i]) == 0)
			{
				sh = 1;
				if (i == 0 && s[a].mest - s[a].mest_sv == 1)
				{
					free(s[a].nomer[0]);
					s[a].nomer[0] = (char *)calloc(N + 1, sizeof(char));
					s[a].mest_sv++;
					break;
				}
				s[a].mest_sv++;
				for (y = i; y < s[a].mest - s[a].mest_sv; y++)
				{
					strcpy(s[a].nomer[y], s[a].nomer[y + 1]);
					if (y + 1 == s[a].mest - s[a].mest_sv)
					{
						free(s[a].nomer[y + 1]);
						s[a].nomer[y + 1] = (char *)calloc(N + 1, sizeof(char));
						break;
					}
				}
			}
			if (i + 1 == s[a].mest - s[a].mest_sv && sh == 0)
			{
				puts("Совпадений не найдено");
				sh = 1;
			}
		}
	} while (sh != 1);
}


void vivod(struct str *s, struct turn *h)
{
	FILE *file;
	int i = 0, y;

	file = fopen("file.txt", "rb+");
	if (!file)
	{
		printf("\nОшибка файла\n\n");
		return;
	}

	fprintf(file, "%d\r\n", maks_shis_stoia);
	for (i = 0; i < maks_shis_stoia; i++)
	{
		fprintf(file, "%d %d\r\n", s[i].mest, s[i].mest_sv);
	}
	for (i = 0; i < maks_shis_stoia; i++)
	{
		for (y = 0; y < s[i].mest - s[i].mest_sv; y++)
		{
			fprintf(file, "%s\r\n", s[i].nomer[y]);
		}
		fprintf(file, "\r\n");
	}
	print_turn(h, file);
	return;
}


void print_turn(struct turn *h, FILE *file)
{
	int sh = 0;

	if (!h)
	{
		return;
	}
	do
	{
		//fprintf(file, "1");
		fprintf(file, "%s %d\r\n", h->nomer_t, h->stoian);
		h = h->nx;
	} while (h);
	fprintf(file, "0");
	return;
}


void del_turn(struct turn **h, struct turn **t)
{
	struct turn *p;
	do
	{
		if (*t == *h)
		{
			free(*h);
			*t = *h = NULL;
			return;
		}
		p = (*h)->nx;
		free(*h);
		*h = p;
	} while (h);
}


void add_f(struct turn **h, struct turn **t, FILE *file)
{
	struct turn *n;
	int sh = 0, flag = 0, k = 0, z = 0;

	n = (struct turn *)calloc(1, sizeof(struct turn));
	if (!n)
	{
		puts("Ошибка памяти");
		return;
	}
	n->nomer_t = (char *)calloc(N + 1, sizeof(char));
	if (!n->nomer_t)
	{
		puts("Ошибка памяти");
		free(n);
		return;
	}

	fscanf(file, "%s", n->nomer_t);
	fscanf(file, "%d", &n->stoian);

	if (!*h)
	{
		*h = *t = n;
	}
	else
	{
		(*t)->nx = n;
		*t = n;
	}
}
