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

void a(unsigned char *buffer, size_t bytes, size_t offset) {
	printf("%08lx: ", offset);
	for (size_t i = 0; i < bytes; i++) {
		if (isprint(buffer[i])) {
			printf("%c", buffer[i]);
		} else {
			printf(".");
		}
	}
	printf("\n");
}

void xoda(const char *filename, const char format) {
	FILE *file = fopen(filename, "rb");
	if (!file) {
		perror("error opening file");
		return;
	}
	unsigned char buffer[B];
	size_t bytesRead;
	size_t offset = 0;
	while ((bytesRead = fread(buffer, 1, B, file)) > 0) {
		switch (format) {
		case 'x':
			x(buffer, bytesRead, offset);
			break;
		case 'o':
			o(buffer, bytesRead, offset);
			break;
		case 'd':
			d(buffer, bytesRead, offset);
			break;
		case 'a':
			a(buffer, bytesRead, offset);
			break;
		default:
			fprintf(stderr, "invalid format specified\n");
			fclose(file);
			return;
		}
		offset += bytesRead;
	}
	fclose(file);
}

int main(int z, char *x[]) {
	if (z != 3) {
		fprintf(stderr, "usage: %s <x|o|d|a> <file>\n", x[0]);
		return EXIT_FAILURE;
	}
	xoda(x[2], x[1][0]);
	return EXIT_SUCCESS;
}
