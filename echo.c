#include <stdio.h>
#include <stdlib.h>

int main(int p, char *v[]) {
	int n=0;
	if (p>1&&v[1][0]=='-'&&v[1][1]=='n') {
		n++;
		p--;
		v++;
	}
	for (int i=1; i<p; i++) {
		fputs(v[i],stdout);
		if (i<p-1) {
			putchar(' ');
		}
	}
	if (n==0) {
		putchar('\n');
	}
	return 0;
}
