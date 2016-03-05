#include "laba6.h"

void menu()
{
	srand(time(0));
	int *A;
	int flag = 0, sh = 0;
	FILE *f, *g;
	A = (int *)calloc(N, sizeof(int));	
	
	while (1)
	{
		puts("Выбирите вид операции:");
		puts("	1 - Создать массив");//
		puts("	2 - Загрузить массив из файла");
		puts("	3 - Вывод массива для F-файла");//
		puts("	4 - Вывод массива для G-файла");//
		puts("	5 - Сохранить F-файл");
		puts("	6 - Сохранить G-файл");
		puts("	7 - Очистить F-файл");
		puts("	8 - Очистить G-файл");
		puts("	9 - Очистить массив");
		puts("	10 - Выход");//
		do
		{
			//fflush(stdin);
			__fpurge(stdin);
			if (!scanf("%d", &sh) || (sh < 1) || (sh > 10))
			{
				puts("Ошибка ввода. Введите заново");
			}
		} while (!sh || (sh < 1) || (sh > 10));

		switch (sh)
		{
		case 1: flag = 10; sozd(A, flag); break;
		case 2:
		{
				  f = fopen("F.txt", "r");
				  if (!f)
				  {
					  puts("F-файл не найден");
					  break;
				  }
				  zagr(A, f);
				  fclose(f);
				  break;
		}
		case 3: flag = 10; see(A, flag); break;
		case 4:	flag = 5; see(A, flag); break;
		case 5:
		{
				  flag = 10;
				  f = fopen("F.txt", "w");
				  write_f(A, flag, f);
				  fclose(f);
				  break;
		}
		case 6:
		{
				  flag = 5;
				  g = fopen("G.txt", "w");
				  write_g(A, flag, g);
				  fclose(g);
				  break;
		}
		case 7:
		{			
				  f = fopen("F.txt", "w");
				  fclose(f);
				  break;
		}
		case 8:
		{
				  g = fopen("G.txt", "w");
				  fclose(g);
				  break;
		}
		case 9:
		{
				if (A[0] == 0)
				{
					puts("Массив еще не создан");
					break;
				}
				free(A);
				A = (int *)calloc(N, sizeof(int));
				break;
		}
		case 10: free(A); return;
		}
	}
}
