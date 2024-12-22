#include <stdio.h>
#include <stdlib.h>

void fe(const char *filename) {
	FILE *file;
	unsigned char e_ident[16];
	file = fopen(filename, "rb");
	if (!file) {
		perror("error opening ELF file");
		return;
	}
	if (fread(e_ident, 1, sizeof(e_ident), file) < sizeof(e_ident)) {
		perror("error reading ELF header");
		fclose(file);
		return;
	}
	fclose(file);
	printf("architecture: ");
	switch (e_ident[4]) {
	case 1:
		printf("32-bit\n");
		break;
	case 2:
		printf("64-bit\n");
		break;
	default:
		printf("unknown architecture\n");
		break;
	}
	if (e_ident[5] == 1) {
		printf("dynamically linked\n");
	} else {
		printf("statically linked\n");
	}
	printf("CPU type: ");
	switch (e_ident[16]) {
	case 0x28:
		printf("ARM\n");
		break;
	case 0x3E:
		printf("x86_64\n");
		break;
	case 0x03:
		printf("x86\n");
		break;
	default:
		printf("unknown CPU type\n");
		break;
	}
}

void ff(const char *filename) {
	FILE *file;
	unsigned char header[4];
	file = fopen(filename, "rb");
	if (!file) {
		perror("error opening file");
		return;
	}
	if (fread(header, 1, sizeof(header), file) < sizeof(header)) {
		perror("error reading file");
		fclose(file);
		return;
	}
	fclose(file);
	if (header[0] == 0x7f && header[1] == 'E' && header[2] == 'L' && header[3] == 'F') {
		printf("%s: ELF executable linkable format\n", filename);
		fe(filename);
	} else if (header[0] == '#' && header[1] == '!') {
		printf("%s: POSIX shell script\n", filename);
	} else if (header[0] == 0x89 && header[1] == 'P' && header[2] == 'N' && header[3] == 'G') {
		printf("%s: PNG portable network graphics\n", filename);
	} else if (header[0] == 'B' && header[1] == 'M') {
		printf("%s: BMP bitmap image file\n", filename);
	} else if (header[0] == 'G' && header[1] == 'I' && header[2] == 'F') {
		printf("%s: GIF graphics interchange format\n", filename);
	} else {
		printf("%s: unknown file type...\n", filename);
	}
}

int main(int z, char *x[]) {
	if (z < 2) {
		fprintf(stderr, "usage: %s <file>\n", x[0]);
		return EXIT_FAILURE;
	}
	ff(x[1]);
	return EXIT_SUCCESS;
}
