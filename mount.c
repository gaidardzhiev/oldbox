#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mount.h>

#define MAX_ENTRIES 1024
#define NAME_SIZE 2048

struct t {
	char mp[NAME_SIZE];
	char d[NAME_SIZE];
} m[MAX_ENTRIES];

int main(int a, char **v) {
	int ro;
	struct t *c;
	char *p;
	int f;
	f = open("/etc/mtab", O_RDONLY);
	read(f, (char*)m, MAX_ENTRIES * 2 * NAME_SIZE);
	if(a == 1) {
		for(c = m; c < &m[MAX_ENTRIES]; c++)
			if(c->mp[0]) printf("%s on %s\n", c->d, c->mp);
		exit(0);
	}
	if(a < 3) {
		fprintf(stderr, "usage: mount <d> <mountpoint>\n");
		exit(1);
	}
	ro = 0;
	if(a > 3) ro++;
	if(mount(v[1], v[2], "ext4", ro, NULL) < 0) {
		perror("mount");
		exit(1);
	}
	p = v[1];
	while(*p++);
	p--;
	while(*--p == '/') *p = '\0';
	while(p > v[1] && *--p != '/');
	if(*p == '/') p++;
	v[1] = p;
	for(c = m; c < &m[MAX_ENTRIES]; c++) {
		if(c->mp[0] == 0) {
			for(p = c->d; p < &c->d[NAME_SIZE - 1];)
				if((*p++ = *v[1]++) == 0) v[1]--;
			for(p = c->mp; p < &c->mp[NAME_SIZE - 1];)
				if((*p++ = *v[2]++) == 0) v[2]--;
			c = &m[MAX_ENTRIES];
			while((--c)->mp[0] == 0);
			f = creat("/etc/mtab", 0644);
			write(f, (char*)m, (c - m + 1) * 2 * NAME_SIZE);
			exit(0);
		}
	}
	exit(0);
}
