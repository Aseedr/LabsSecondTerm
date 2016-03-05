#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define N 50
#define M 100


struct der
{
	char *inf;
	int god, mec, den;
	struct der *l, *r;
};


struct der **GG; int PP, GP;
void see(struct der *);
struct der *sozd(struct der *);
void add(struct der *);
void vvod(struct der *);
struct der *del(struct der *);
void f_free(struct der *);
void save(struct der *, FILE *file);
struct der *read(struct der *, FILE *file);
void read_add(struct der *, FILE *file);
struct der *del_op(struct der *);
void del_op_el(struct der *, int X);
