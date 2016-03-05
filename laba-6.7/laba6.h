#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#define N 10000


static const char *optString = "hascl";

static const struct option longOpts[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "add", no_argument, NULL, 'a' },
	{ "see", no_argument, NULL, 's' },
	{ "convert", no_argument, NULL, 'c' },
	{ "clean", no_argument, NULL, 'l' },
	{ NULL, no_argument, NULL, 0 }
};


void sozd(int *A, int flag);
void zagr(int *A, FILE *f);
void see(int *A, int flag);
void write_f(int *A, int flag, FILE *f);
void write_g(int *A, int flag, FILE *g);
void menu();
