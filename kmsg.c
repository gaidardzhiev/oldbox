#include <stdio.h>
#include <stdlib.h>

#define SIZE 65536

void kmsg() {
	char b[SIZE];
	FILE *fp;
	fp = fopen("/proc/kmsg", "r");
	if (fp == NULL) {
		perror("failed to open /proc/kmsg");
		exit(EXIT_FAILURE);
	}
	while (fgets(b, sizeof(b), fp) != NULL) {
		printf("%s", b);
	}
	fclose(fp);
}

int main(void) {
	kmsg();
	return 0;
}
