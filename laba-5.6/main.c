#include "laba5.h"

void main()
{
	setlocale(LC_ALL, "Russian");
	struct der *dr;
	dr = NULL;
	int flag = 0, sh, i;
	FILE *file;

	GG = (struct der **)calloc(M, sizeof(struct der *));

	while (1)
	{
		puts("Выбирите вид операции:");
		puts("	1 - Создать дерево");//
		puts("	2 - Загрузить дерево из файла");
		puts("	3 - Вывод содержимого дерева");//
		puts("	4 - Добавление элемента в дерево");//
		puts("	5 - Удаление элемента из дерева");//
		puts("	6 - Полное удалнение (очистка) дерева");//
		puts("	7 - Сорханить в файл");//
		puts("	8 - Удалить все до определенной даты");//
		puts("	9 - Выход");
		do
		{
			//fflush(stdin);
			__fpurge(stdin);
			if (!scanf("%d", &flag) || (flag < 1) || (flag > 9))
			{
				puts("Ошибка ввода. Введите заново");
			}
		} while (!flag || (flag < 1) || (flag > 9));

		switch (flag)
		{
		case 1: dr = sozd(dr); break;
		case 2: 
		{
			file = fopen("file.txt", "r");
			if (!file)
			{
				puts("Файл не найден");
				break;
			}
			fscanf(file, "%d", &GP);
			
			if (dr || GP == 0)
			{
				fclose(file);
				puts("Бинарное дерево уже создано");
				break;
			}
			dr = read(dr, file);
			sh = 1;
			while (sh != GP)
			{
				read_add(dr, file);
				sh++;
			}
			
			fclose(file);
			break;
		}
		case 3: see(dr); puts("Если пусто, то элементы дерева удалены, добавте."); break;
		case 4: add(dr); break;
		case 5: del(dr); break;
		case 6: f_free(dr); dr = NULL; break;
		case 7:
		{
			file = fopen("file.txt", "w");
			fprintf(file, "%d\r\n\r\n", GP);
			save(dr, file);
			fclose(file);
			break;
		}
		case 8: del_op(dr); break;
		case 9: f_free(dr); free(GG); return;
		}
	}
}
