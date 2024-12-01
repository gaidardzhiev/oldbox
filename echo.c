#include <stdio.h>
#include <stdlib.h>

int main(int c, char *v[]) {
	int nlf=0;
	if (c>1&&v[1][0]=='-'&&v[1][1]=='n') {
		nlf++;
		c--;
		v++;
	}
	for (int i=1; i<c; i++) {
		fputs(v[i],stdout);
		if (i<c-1) {
			putchar(' ');
		}
	}
	if (nlf==0) {
		putchar('\n');
	}
	return 0;
}
