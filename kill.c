/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void u() {
	printf("usage: kill <SIG> <PID>\n");
	exit(EXIT_FAILURE);
}

int main(int c, char **v) {
	int s = SIGTERM;
	int e = 0;
	if (c < 2) {
		u();
	}
	if (v[1][0] == '-') {
		s = atoi(v[1] + 1);
		c--;
		v++;
	}
	v++;
	while (c > 1) {
		int p = atoi(*v);
		if (p <= 0) {
			u();
		}
		if (kill(p, s) < 0) {
			perror("error sending signal");
			e = 1;
		}
		c--;
		v++;
	}
	return e;
}
