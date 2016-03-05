#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#define N 20
#define M 10
#define MAX 100000000

static const char *optString = "hf:s:e:";

static const struct option longOpts[] = {
	{ "help", no_argument, NULL, 'h' },
	{ "file", required_argument, NULL, 'f' },
	{ "start", required_argument, NULL, 's' },
	{ "end", required_argument, NULL, 'e' },
	{ NULL, no_argument, NULL, 0 }
};


void menu();
void add_file();
void print();
int number(FILE *file, int amount);
void cutout(FILE *file, FILE *file_w, int start, int end);
