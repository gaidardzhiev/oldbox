#include <stdio.h>
#include <stdlib.h>

void d(const char* o, long c, long w, long l);

int main(int z, char** x) {
	int i;
	FILE* f;
	long L = 0, W = 0, C = 0;
	long l, w, c;
	const char* o = "lwc";
	int t;
	if (z > 1 && x[1][0] == '-') {
		o = x[1] + 1;
		z--;
		x++;
	}
	for (i = 1; i < z; i++) {
		f = (z > 1) ? fopen(x[i], "r") : stdin;
		if (f == NULL) {
			fprintf(stderr, "wc: can't open %s\n", x[i]);
			continue;
		}
		l = w = c = 0;
		t = 0;
		while (1) {
			int character = getc(f);
			if (character == EOF) break;
			c++;
			if (character > ' ' && character < 127) {
				if (!t) {
					w++;
					t = 1;
				}
				continue;
			}
			if (character == '\n') l++;
			else if (character != ' ' && character != '\t') continue;
			t = 0;
		}
		d(o, c, w, l);
		if (z > 2) {
			printf(" %s\n", x[i]);
		} else {
			printf("\n");
		}
		fclose(f);
		L += l;
		W += w;
		C += c;
	}
	if (z > 2) {
		d(o, C, W, L);
		printf(" total\n");
	}
	return 0;
}

void d(const char* o, long c, long w, long l) {
	while (*o) {
		switch (*o++) {
		case 'l':
			printf("%7ld", l);
			break;
		case 'w':
			printf("%7ld ", w);
			break;
		case 'c':
			printf("%7ld", c);
			break;
		}
	}
}
