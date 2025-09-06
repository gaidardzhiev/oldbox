/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

#define MAX 20
#define BUF 512

int fd[MAX] = {1};
int fc = 1;
int iscd = 0;
int af = 0;
char ib[BUF];
char ob[BUF];

void s(int size);
void err(const char *m);

int main(int argc, char **argv) {
	struct stat fi;
	int rb, wb, cf;
	while (argc > 1 && argv[1][0] == '-') {
		switch (argv[1][1]) {
		case 'a':
			af++;
			break;
		case 'i':
		case '0':
			signal(SIGINT, SIG_IGN);
			break;
		}
		argv++;
		argc--;
	}
	fstat(1, &fi);
	iscd = (fi.st_mode & S_IFMT) == S_IFCHR;
	if (lseek(1, 0L, SEEK_CUR) == -1 && errno == ESPIPE) {
		iscd++;
	}
	while (argc-- > 1) {
		if (af) {
			fd[fc] = open(argv[1], O_WRONLY);
			if (fd[fc] < 0) {
				fd[fc] = creat(argv[1], 0666);
			}
			lseek(fd[fc++], 0L, SEEK_END);
		} else {
			fd[fc++] = creat(argv[1], 0666);
		}
		if (stat(argv[1], &fi) >= 0) {
			if ((fi.st_mode & S_IFMT) == S_IFCHR) {
				iscd++;
			}
		} else {
			err("tee: cannot open ");
			err(argv[1]);
			putchar('\n');
			fc--;
		}
		argv++;
	}
	rb = wb = 0;
	for (;;) {
		for (cf = 0; cf < BUF;) {
			if (rb >= wb) {
				if (iscd > 0 && cf > 0) {
					break;
				}
				wb = read(0, ib, BUF);
				rb = 0;
				if (wb <= 0) {
					s(cf);
					return 0;
				}
			}
			ob[cf++] = ib[rb++];
		}
		s(cf);
	}
}

void s(int size) {
	int i, k, cs = iscd ? 16 : size;
	for (i = 0; i < size; i += cs) {
		for (k = 0; k < fc; k++) {
			write(fd[k], ob + i, cs < size - i ? cs : size - i);
		}
	}
}

void err(const char *m) {
	while (*m) {
		write(2, m++, 1);
	}
}
