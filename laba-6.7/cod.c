#include "laba6.h"

void sozd(int *A, int flag)
{
	int i, c = 0, sh = 0, gg = 1;
	if (A[0] != 0)
	{
		puts("Массив уже создан");
		return;
	}
	puts("Введите количество компонентов (кратное десяти)");
	do
	{
		//fflush(stdin);
		__fpurge(stdin);
		if (!scanf("%d", &c) || (c < 1) || (c > 10000) || c % 10 != 0)
		{
			puts("Ошибка ввода. Введите заново");
		}
	} while (!c || (c < 1) || (c > 10000) || c % 10 != 0);

	for (i = 0; i < c; i++)
	{
		A[i] = rand() % 1000000 + 1;
	}

	for (i = 0; i < N; i++)
	{
		if (A[i] == 0)
		{
			break;
		}
		A[i] *= gg;
		sh++;
		if (sh % flag == 0)
		{
			gg *= -1;
		}
	}
	return;
}


void see(int *A, int flag)
{
	int i, sh = 0, gg = 1;
	if (A[0] == 0)
	{
		puts("Массив не создан");
		return;
	}
	for (i = 0; i < N; i++)
	{
		if (A[i] == 0)
		{
			break;
		}
		if (i % 5 == 0)
		{
			printf("\n");
		}
		printf("%d ", A[i] * gg);
		sh++;
		if (sh % 10 == 5 && flag == 5)
		{
			gg *= -1;
		}
	}
	printf("\n");
	return;
}


void zagr(int *A, FILE *f)
{
	int i;
	if (A[0] != 0)
	{
		puts("Массив уже создан");
		return;
	}
	for (i = 0; i < N; i++)
	{
		fscanf(f, "%d", &A[i]);
	}
	if (A[0] == 0)
	{
		puts("Массив в файле не обнаружен");
		return;
	}
	return;
}


void write_f(int *A, int flag, FILE *f)
{
	int i;
	if (A[0] == 0)
	{
		puts("Массив еще не создан");
		return;
	}
	for (i = 0; i < N; i++)
	{
		if (A[i] == 0)
		{
			break;
		}
		if (i % 5 == 0 && i != 0)
		{
			fprintf(f, "\n");
		}
		fprintf(f,"%d ", A[i]);
	}
}


void write_g(int *A, int flag, FILE *g)
{
	int i, sh = 0, gg = 1;
	if (A[0] == 0)
	{
		puts("Массив еще не создан");
		return;
	}
	for (i = 0; i < N; i++)
	{
		if (A[i] == 0)
		{
			break;
		}
		if (i % 5 == 0 && i != 0)
		{
				fprintf(g, "\n");
		}
			fprintf(g, "%d ", A[i] * gg);
		sh++;
		if (sh % 10 == 5 && flag == 5)
		{
			gg *= -1;
		}
	}
}
