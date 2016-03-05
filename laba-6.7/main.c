#include "laba6.h"

int main(int argc, char *argv[])
{
	if(argc > 1)
	{
		FILE *f, *g;
		int flag = 0;
		int *A;
		int opt = 0;
		int longIndex = 0;

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
		while(opt != -1) 
		{
			A = (int *)calloc(N, sizeof(int));
			switch(opt)
			{
			case 'h': 
				puts("--add -a	Создание F-файла");
				puts("--see -s	Просмотр F-файла и G-файла(без сохранения)");
				puts("--convert -c	Конвертирование F-файла в G-файл");
				puts("--clean -l	Очистка файлов");
				break;
			case 'a': 
				flag = 10; sozd(A, flag);
				f = fopen("F.txt", "w");
				write_f(A, flag, f);
				fclose(f);
				break;
			case 's': 
				f = fopen("F.txt", "r");
				if (!f)
				{
					puts("F-файл не найден");
					break;
				}
				zagr(A, f);
				fclose(f);
				flag = 10;
				puts("\nF-файл ----------------------------");
				see(A, flag);
				flag = 5;
				puts("\nG-файл ----------------------------");
				see(A, flag);
				break;	
			case 'c': 
				f = fopen("F.txt", "r");
				if (!f)
				{
					puts("F-файл не найден");
					break;
				}
				zagr(A, f);
				fclose(f);
				flag = 5;
				g = fopen("G.txt", "w");
				write_g(A, flag, g);
				fclose(g);
				break;
			case 'l': 
				f = fopen("F.txt", "w");
				fclose(f);
				g = fopen("G.txt", "w");
				fclose(g);
				break;	break;
			}
			opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
			free(A);
		}
	}
	else 
	{
		menu();
	}
	return;
}
