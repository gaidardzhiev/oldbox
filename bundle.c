#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		fprintf(stderr, "usage: %s files >> archive\n", argv[0]);
		fprintf(stderr, "this program bundles files into a POSIX shell script archive\n");
		return 1;
	}
	printf("#!/bin/sh\n");
	for (int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "%s does not exist...\n", argv[i]);
			continue;
		}
		printf("cat > \"%s\" << 'BUNDLE'\n", argv[i]);

		int ch;
		while ((ch = fgetc(fp)) != EOF) {
			putchar(ch);
		}
		fclose(fp);
		printf("BUNDLE\n");
	}
	return 0;
}
