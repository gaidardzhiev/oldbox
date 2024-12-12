#include <stdio.h>
#include <stdlib.h>

int a=0, b=0, c=0, d=0;
char e[256], f[256], g[256];

struct h {
	int i, j;
	char *k;
} m, n;

w(struct h *x) {
        register int y, z, a;
        y = *x->k++;
        if (y == '\\') {
                z = a = 0;
                while (z < 3 && (y = *x->k) >= '0' && y <= '7') {
                        a = a * 8 + y - '0';
                        z++;
                        x->k++;
                }
                if (z > 0) y = a;
                else y = *x->k++;
        }
        if (y == 0) *--x->k = 0;
        return (y & 0377);
}

l(struct h *x) {
again:
        if (x->j) {
                if (x->i++ < x->j) return (x->i);
                x->j = x->i = 0;
        }
        if (x->i && *x->k == '-') {
                w(x);
                x->j = w(x);
                if (x->j == 0) {
                        x->k--;
                        return ('-');
                }
                if (x->j < x->i) {
                        x->i = x->j - 1;
                        return ('-');
                }
                goto again;
        }
        return (x->i = w(x));
}

int main(int o, char **p) {
	register int q;
	int r;
	register int s, t;
	char *u;
	int v;
	m.i = n.i = 0;
	m.j = n.j = 0;
	m.k = n.k = "";
	if (--o > 0) {
		p++;
		if (*p[0] == '-' && p[0][1] != 0) {
			while (*++p[0]) {
				switch (*p[0]) {
				case 'c':
					c++;
					continue;
				case 'd':
					a++;
					continue;
				case 's':
					b++;
					continue;
				}
			}
			o--;
			p++;
		}
	}
	if (o > 0) m.k = p[0];
	if (o > 1) n.k = p[1];
	for (q = 0; q < 256; q++) e[q] = g[q] = 0;
	if (c) {
		while (s = l(&m)) g[s & 0377] = 1;
		r = 0;
		for (q = 1; q < 256; q++)
			if (g[q] == 0) g[r++] = q;
		g[r] = 0;
		u = g;
	}
	for (q = 0; q < 256; q++) f[q] = 0; v = 0;
	for (;;) {
		if (c) s = *u++;
		else s = l(&m);
		if (s == 0) 
		break;
		t = l(&n);
		if (t == 0) t = v;
		else v = t;f[t & 0377] = 1;e[s & 0377] = a ? 1 : t;
	}
	while (t = l(&n)) f[t & 0377] = 1;
	f[0] = 1;
	for (q = 0; q < 256; q++) {
		if (e[q] == 0) e[q] = q;
		else if (a) e[q] = 0;
	}
	while ((s = getc(stdin)) != EOF) {
		if (s == 0) 
			continue;
		if (s = e[s & 0377] & 0377)
			if (!b || s != d || !f[s & 0377]) putchar(d = s);
	}
	exit(0);
}
