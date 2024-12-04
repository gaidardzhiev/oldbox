#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define S 4

void s(FILE *f) {
	int c;
	int n = 0;
	char b[1024];
	while ((c = fgetc(f)) != EOF) {
		if (isprint(c)) {
			b[n++] = c;
			if (n >= sizeof(b) - 1) {
				break;
			}
		} else {
			if (n >= S) {
				b[n] = '\0';
				printf("%s\n", b);
			}
			n = 0;
		}
	}
	if (n >= S) {
		b[n] = '\0';
		printf("%s\n", b);
	}
}

int main(int z, char *x[]) {
	if (z < 2) {
		fprintf(stderr, "usage: %s <file>\n", x[0]);
		return EXIT_FAILURE;
	}
	for (int i = 1; i < z; i++) {
		FILE *f = fopen(x[i], "r");
		if (!f) {
			perror("error opening file");
			continue;
		}
		printf( x[i]);
		s(f);
		fclose(f);
	}
	return EXIT_SUCCESS;
}
