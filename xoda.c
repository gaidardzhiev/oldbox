#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define B 16

void x(unsigned char *b, size_t s, size_t o) {
	printf("%08lx: ", o);
	for (size_t i = 0; i < s; i++) {
		printf("%02x ", b[i]);
	}
	printf("\n");
}

void o(unsigned char *b, size_t s, size_t o) {
	printf("%08lx: ", o);
	for (size_t i = 0; i < s; i++) {
		printf("%03o ", b[i]);
	}
	printf("\n");
}

void d(unsigned char *b, size_t s, size_t o) {
	printf("%08lx: ", o);
	for (size_t i = 0; i < s; i++) {
		printf("%03d ", b[i]);
	}
	printf("\n");
}

void a(unsigned char *b, size_t s, size_t o) {
	printf("%08lx: ", o);
	for (size_t i = 0; i < s; i++) {
		if (isprint(b[i])) {
			printf("%c", b[i]);
		} else {
			printf(".");
		}
	}
	printf("\n");
}

void f(const char *n, const char m) {
	FILE *f = fopen(n, "rb");
	if (!f) {
		perror("error opening file");
		return;
	}
	unsigned char b[B];
	size_t r;
	size_t offset = 0;
	while ((r = fread(b, 1, B, f)) > 0) {
		switch (m) {
		case 'x':
			x(b, r, offset);
			break;
		case 'o':
			o(b, r, offset);
			break;
		case 'd':
			d(b, r, offset);
			break;
		case 'a':
			a(b, r, offset);
			break;
		default:
			fprintf(stderr, "invalid format specified...\n");
			fclose(f);
			return;
		}
		offset += r;
	}
	fclose(f);
}

int main(int z, char *x[]) {
	if (z != 3) {
		fprintf(stderr, "usage: %s <x|o|d|a> <file>\n", x[0]);
		return EXIT_FAILURE;
	}
	f(x[2], x[1][0]);
	return EXIT_SUCCESS;
}
