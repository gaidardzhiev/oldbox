#include <stdio.h>
#include <stdlib.h>

#define q 16

void s(const char *p) {
	FILE *f = fopen(p, "rb");
	if (!f) {
		perror("error opening file");
		return;
	}
	unsigned char m[q];
	size_t b = fread(m, 1, q, f);
	printf("magic signature bytes: ");
	for (size_t i = 0; i < q; i++) {
		printf("%02X ", m[i]);
	}
	printf("\n");
	printf("human readable ASCII: ");
	for (size_t i = 0; i < q; i++) {
		if (m[i] >= 32 && m[i] <= 126) {
			printf("%c", m[i]);
		} else {
			printf("*");
		}
	}
	printf("\n");
	fclose(f);
}

int main(int z, char *x[]) {
	if (z != 2) {
		fprintf(stderr, "usage: %s <file>\n", x[0]);
		return 1;
	}
	s(x[1]);
	return 0;
}
