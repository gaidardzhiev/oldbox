#include <stdio.h>
#include <stdlib.h>

void cmp(const char *p, const char *q) {
	FILE *b, *d;
	int x, z;
	long s = 0;
	b = fopen(p, "rb");
	d = fopen(q, "rb");
	if (b == NULL || d == NULL) {
		perror("error opening files...");
		exit(EXIT_FAILURE);
	}
	while (1) {
		x = fgetc(b);
		z = fgetc(d);
		if (x == EOF && z == EOF) {
			break;
		}
		if (x != z) {
			printf("difference at byte position %ld: %02X != %02X\n", s, x, z);
		}
		s++;
	}
	fclose(b);
	fclose(d);
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <file1> <file2>\n", argv[0]);
		return EXIT_FAILURE;
	}
	cmp(argv[1], argv[2]);
	return EXIT_SUCCESS;
}
