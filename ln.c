/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

char* f(const char* s, char c) {
	char* l = NULL;
	while (*s) {
		if (*s == c) {
			l = (char*)s;
		}
		s++;
	}
	return l;
}

int main(int z, char** x) {
	struct stat fs;
	char n[100], *b, *t;
	int ff = 0;
	if (z > 1 && strcmp(x[1], "-f") == 0) {
		z--;
		x++;
		ff = 1;
	}
	if (z < 2 || z > 3) {
		fprintf(stderr, "usage: ln <target> <link>\n");
		exit(EXIT_FAILURE);
	}
	b = f(x[1], '/');
	b = (b == NULL) ? x[1] : b + 1;
	t = (z == 2) ? b : x[2];
	if (stat(x[1], &fs) < 0) {
		fprintf(stderr, "ln: %s does not exist\n", x[1]);
		exit(EXIT_FAILURE);
	}
	if (!ff && (fs.st_mode & S_IFMT) == S_IFDIR) {
		fprintf(stderr, "ln: %s is a directory\n", x[1]);
		exit(EXIT_FAILURE);
	}
	if (stat(t, &fs) >= 0 && (fs.st_mode & S_IFMT) == S_IFDIR) {
		snprintf(n, sizeof(n), "%s/%s", t, b);
	} else {
		strncpy(n, t, sizeof(n));
	}
	if (link(x[1], n) < 0) {
		perror("ln");
		exit(EXIT_FAILURE);
	}
	return EXIT_SUCCESS;
}
