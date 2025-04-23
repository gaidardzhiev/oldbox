#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF 65536

void r(FILE *in) {
	char l[BUF];
	int e;
	while (fgets(l, sizeof(l), in) != NULL) {
		e = strlen(l);
		for (int i = e - 1; i >= 0; i--) {
			putchar(l[i]);
		}
	}
}

int main(int x, char **z) {
	FILE *f = stdin;
	if (x > 1) {
		f = fopen(z[1], "r");
		if (f == NULL) {
			fprintf(stderr, "rev: cannot open %s\n", z[1]);
			exit(EXIT_FAILURE);
		}
	}
	r(f);
	printf("\n");
	if (f != stdin) {
		fclose(f);
	}
	return 0;
}
