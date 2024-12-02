#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define NMNT  512
#define SIZE  1024

typedef struct {
	char mp[SIZE];
	char d[SIZE];
} e;

e t[NMNT];

int main(int c, char** v) {
	e* ce;
	char* p;
	int mount_file;
	sync();
	mount_file = open("/etc/mtab", O_RDONLY);
	read(mount_file, (char*)t, NMNT * sizeof(e));
	if (c != 2) {
		fprintf(stderr, "usage: %s <mount_point>\n", v[0]);
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
	for (ce = t; ce < &t[NMNT]; ce++) {
		p = v[1];
		char* device_ptr = ce->d;
		while (*p++ == *device_ptr) {
			if (*device_ptr++ == '\0') {
				for (p = ce->mp; p < &ce->mp[SIZE];) {
					*p++ = '\0';
				}
				ce = &t[NMNT];
				while ((--ce)->mp[0] == '\0');
				mount_file = creat("/etc/mtab", 0644);
				write(mount_file, (char*)t, (ce - t + 1) * sizeof(e));
				return EXIT_SUCCESS;
			}
		}
	}
	fprintf(stderr, "%s not found in mount table\n", v[1]);
	return EXIT_FAILURE;
}
