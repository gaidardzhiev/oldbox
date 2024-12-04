#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MIN_LENGTH 4

void strings(FILE *file) {
	int c;
	int count = 0;
	char b[1024];
	while ((c = fgetc(file)) != EOF) {
		if (isprint(c)) {
			b[count++] = c;
			if (count >= sizeof(b) - 1) {
				break;
			}
		} else {
			if (count >= MIN_LENGTH) {
				b[count] = '\0';
				printf("%s\n", b);
			}
			count = 0;
		}
	}
	if (count >= MIN_LENGTH) {
		b[count] = '\0';
		printf("%s\n", b);
	}
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s <file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	for (int i = 1; i < argc; i++) {
		FILE *file = fopen(argv[i], "r");
		if (!file) {
			perror("error opening file");
			continue;
		}
		printf( argv[i]);
		strings(file);
		fclose(file);
	}
	return EXIT_SUCCESS;
}
