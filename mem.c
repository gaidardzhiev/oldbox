/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void mem(pid_t pid) {
	char f[65536];
	snprintf(f, sizeof(f), "/proc/%d/maps", pid);
	char b[65536];
	int fd = open(f, O_RDONLY);
	if (fd == -1) {
		perror("error opening: /proc/%d/maps");
		exit(EXIT_FAILURE);
	}
	printf("memory layout of PID: %d\n", pid);
	ssize_t r;
	while ((r = read(fd, b, sizeof(b) - 1)) > 0) {
		b[r] = '\0';
		printf("%s",b);
	}
	if (r == -1) {
		perror("error reading: /proc/%d/maps");
	}
	close(fd);
}

int main(int z, char *x[]) {
	if (z != 2) {
		fprintf(stderr, "usage: %s <PID>\n", x[0]);
		exit(EXIT_FAILURE);
	}
	pid_t pid = atoi(x[1]);
	mem(pid);
	return 0;
}
