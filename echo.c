#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int nlf=0;
	if (argc>1&&argv[1][0]=='-'&&argv[1][1]=='n') {
		nlf++;
		argc--;
		argv++;
	}
	for (int i=1; i<argc; i++) {
		fputs(argv[i],stdout);
		if (i<argc-1) {
			putchar(' ');
		}
	}
	if (nlf==0) {
		putchar('\n');
	}
	return 0;
}
