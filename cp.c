#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUF 65536

#define O "\x75\x73\x61\x67\x65\x3A\x20\x63\x70\x20\x3C\x73\x6F\x75\x72\x63\x65\x3E\x20\x3C\x64\x65\x73\x74\x3E"
#define B "\x63\x70\x3A\x20\x63\x61\x6E\x6E\x6F\x74\x20\x6F\x70\x65\x6E\x20\x25\x73"
#define F "\x63\x70\x3A\x20\x63\x61\x6E\x6E\x6F\x74\x20\x63\x6F\x70\x79\x20\x66\x69\x6C\x65\x20\x74\x6F\x20\x69\x74\x73\x65\x6C\x66\x2E\x2E\x2E"
#define U "\x63\x70\x3A\x20\x63\x61\x6E\x6E\x6F\x74\x20\x63\x72\x65\x61\x74\x65\x20\x25\x73"
#define S "\x63\x70\x3A\x20\x72\x65\x61\x64\x20\x65\x72\x72\x6F\x72\x2E\x2E\x2E"
#define C "\x63\x70\x3A\x20\x77\x72\x69\x74\x65\x20\x65\x72\x72\x6F\x72\x2E\x2E\x2E"

struct stat ss, ds;
char b[BUF];

int cf(const char *sp, const char *dp);
void u();

int main(int z, char *x[]) {
	if (z < 3) {
		u();
	}
	if (z > 3) {
		if (stat(x[z - 1], &ds) < 0 || (ds.st_mode & S_IFMT) != S_IFDIR) {
			u();
		}
	}
	int r = 0;
	for (int i = 1; i < z - 1; i++) {
		r |= cf(x[i], x[z - 1]);
	}
	return r;
}

void u() {
	fprintf(stderr,O"\n");
	exit(EXIT_FAILURE);
}

int cf(const char *sp, const char *dp) {
	int sf = open(sp, O_RDONLY);
	if (sf < 0) {
		fprintf(stderr,B"\n", sp);
		return 1;
	}
	fstat(sf, &ss);
	int m = ss.st_mode;
	if (stat(dp, &ds) >= 0 && (ds.st_mode & S_IFMT) == S_IFDIR) {
		char *sptr = (char *)sp;
		char *dptr = (char *)dp;
		char *bptr = b;
		while (*bptr++ = *dptr++);
		bptr[-1] = '/';
		dptr = bptr;
		while (*bptr = *sptr++) {
			if (*bptr++ == '/') {
				bptr = dptr;
			}
		}
		dp = b;
	}
	if (stat(dp, &ds) >= 0) {
		if (ss.st_dev == ds.st_dev && ss.st_ino == ds.st_ino) {
			fprintf(stderr,F"\n");
			close(sf);
			return 1;
		}
	}
	int df = creat(dp, m);
	if (df < 0) {
		fprintf(stderr,U"\n", dp);
		close(sf);
		return 1;
	}
	ssize_t br;
	while ((br = read(sf, b, BUF)) > 0) {
		if (br < 0) {
			fprintf(stderr,S"\n");
			close(sf);
			close(df);
			return 1;
		} else if (write(df, b, br) != br) {
			fprintf(stderr,C"\n");
			close(sf);
			close(df);
			return 1;
		}
	}
	close(sf);
	close(df);
	return 0;
}
