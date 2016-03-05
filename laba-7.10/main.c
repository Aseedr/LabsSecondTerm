#include "laba7.h"

void main(int argc, char *argv[])
{
	if(argc > 1)
	{
		FILE *file = 0; FILE *file_w = 0;
		int opt = 0, start = 0, end = 0;
		int longIndex = 0, i, flag = 0, amount = 0;

		opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
		while(opt != -1) 
		{
			switch(opt)
			{
			case 'h': 
				puts("--file -f	Имя вашего файла");
				puts("--start -s	Начало удаления");
				puts("--end -e	Конец удаления");
				return;
			case 'f': 
				if (!file)
				{
					file = fopen(optarg, "rb+");
					file_w = fopen(optarg, "r");
				}
				else
				{
					puts("Файл уже используется");
					break;
				}
				if (!file)
				{
					puts("Ошибка файла");
					return;
				}
				flag += M;
				break;
			case 's': 
				if (start != 0)
				{
					puts("Данные для начала удаления уже введены");
					break;
				}
				for (i = 0; i < N; i++)
				{
					if (optarg[i] - 48 > 9 || start < 0)
					{
						puts("Ошибка ввода данных для начала удаления");
						start = 0;
						break;
					}
					if (!optarg[i])
					{
						break;
					}
					else
					{
						start *= M;
					}
					start += optarg[i] - 48;
				}
				flag++;
				break;	
			case 'e': 
				if (end != 0)
				{
					puts("Данные для конца удаления уже введены");
					break;
				}
				for (i = 0; i < N; i++)
				{
					if (optarg[i] - 48 > 9 || end < 0)
					{
						puts("Ошибка ввода данных для конца удаления");
						end = 0;
						break;
					}
					if (!optarg[i])
					{
						break;
					}
					else
					{
						end *= M;
					}
					end += optarg[i] - 48;
				}
				flag++;
				break;
			}
			opt = getopt_long(argc, argv, optString, longOpts, &longIndex);
		}
		amount = number(file, amount);
		if (flag == 12)
		{
			if (start > end || start == 0 || end == 0 || end > amount) //|| start == end)
			{
				puts("Проверьте введенные данные");
				printf("В файле %d чисел\n", amount);
				fclose(file_w);
				fclose(file);
			}
			else
			{
				cutout(file, file_w, start, end);
				ftruncate(fileno(file), (amount - end + start - 1) * 4);
				fclose(file_w);
				fclose(file);
			}
		}
		else
		{
			puts("Введены не все параметры");
		}
	}
	else 
	{
		menu();
	}
	return;
}
