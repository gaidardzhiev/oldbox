#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 16

void hex(unsigned char *buffer, size_t bytes, size_t offset) {
	printf("%08lx: ", offset);
	for (size_t i = 0; i < bytes; i++) {
		printf("%02x ", buffer[i]);
	}
	printf("\n");
}

void octal(unsigned char *buffer, size_t bytes, size_t offset) {
	printf("%08lx: ", offset);
	for (size_t i = 0; i < bytes; i++) {
		printf("%03o ", buffer[i]);
	}
	printf("\n");
}

void decimal(unsigned char *buffer, size_t bytes, size_t offset) {
	printf("%08lx: ", offset);
	for (size_t i = 0; i < bytes; i++) {
		printf("%03d ", buffer[i]);
	}
	printf("\n");
}

void ascii(unsigned char *buffer, size_t bytes, size_t offset) {
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
	unsigned char buffer[BUFFER_SIZE];
	size_t bytesRead;
	size_t offset = 0;
	while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
		switch (format) {
		case 'x':
			hex(buffer, bytesRead, offset);
			break;
		case 'o':
			octal(buffer, bytesRead, offset);
			break;
		case 'd':
			decimal(buffer, bytesRead, offset);
			break;
		case 'a':
			ascii(buffer, bytesRead, offset);
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

int main(int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "usage: %s <filename> <x|o|d|a>\n", argv[0]);
		return EXIT_FAILURE;
	}
	xoda(argv[1], argv[2][0]);
	return EXIT_SUCCESS;
}
