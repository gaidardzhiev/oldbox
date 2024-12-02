#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define N 512
#define S 1024
#define H "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x6D\x6F\x75\x6E\x74\x5F\x70\x6F\x69\x6E\x74\x3E"

typedef struct {
	char mp[S];
	char d[S];
} 

e;e t[N];

int main(int c, char** v) {
	e* ce;
	char* p;
	int mf;
	sync();
	mf = open("/etc/mtab", O_RDONLY);
	read(mf, (char*)t, N * sizeof(e));
	if (c != 2) {
		fprintf(stderr,H"\n", v[0]);
		return EXIT_FAILURE;
	}
	if (umount(v[1]) < 0) {
		perror("failed to unmount...");
		return EXIT_FAILURE;
	}
	p = v[1];
	while (*p++);
	p--;
	while (p > v[1] && *--p == '/') *p = '\0';
	while (p > v[1] && *--p != '/');
	if (*p == '/') p++;
	v[1] = p;
	for (ce = t; ce < &t[N]; ce++) {
		p = v[1];
		char* w = ce->d;
		while (*p++ == *w) {
			if (*w++ == '\0') {
				for (p = ce->mp; p < &ce->mp[S];) {
					*p++ = '\0';
				}
				ce = &t[N];
				while ((--ce)->mp[0] == '\0');
				mf = creat("/etc/mtab", 0644);
				write(mf, (char*)t, (ce - t + 1) * sizeof(e));
				return EXIT_SUCCESS;
			}
		}
	}
	fprintf(stderr, "%s not found in mount table\n", v[1]);
	return EXIT_FAILURE;
}
