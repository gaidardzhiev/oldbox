/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	char *p = NULL;
	char *q = NULL;
	if (argc < 2) {
		putchar('\n');
		exit(EXIT_FAILURE);
	}
	q = argv[1];
	while (*q) {
		if (*q== '/') {
			p = q + 1;
		}
		q++;
	}
	if (argc > 2) {
		char *ca = argv[2];
		char *ec = ca;

		while (*ec) {
			ec++;
		}
		while (ca > p && ec > ca) {
			if (*--ec != *--ca) {
				goto out;
			}
		}
		*ca = '\0';
	}
out:
	puts(p);
	exit(EXIT_SUCCESS);
}
