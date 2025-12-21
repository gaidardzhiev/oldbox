/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int z, char **x) {
	int c, n = 0;
	char *i;
	if (z < 2) {
		fprintf(stderr, "usage: %s <sec> \n", x[0]);
		return EXIT_FAILURE;
	}
	i = x[1];
	while ((c = *i++)) {
		if (c < '0' || c > '9') {
			fprintf(stderr, "error: invalid character...\n");
			return EXIT_FAILURE;
		}
		n = n * 10 + (c - '0');
	}
	sleep(n);
	return EXIT_SUCCESS;
}
