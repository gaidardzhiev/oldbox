#include <stdio.h>
#include <stdlib.h>

int main(int p, char *q[]) {
	int n=0;
	if (p>1&&q[1][0]=='-'&&q[1][1]=='n') {
		n++;
		p--;
		q++;
	}
	for (int i=1; i<p; i++) {
		fputs(q[i],stdout);
		if (i<p-1) {
			putchar(' ');
		}
	}
	if (n==0) {
		putchar('\n');
	}
	return 0;
}
