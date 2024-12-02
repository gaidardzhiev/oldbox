#include <stdio.h>
#include <stdlib.h>

#define X 4096

char l[X];
FILE *in;
int main(z,x)char**x; {
	register i,c;
	in=stdin;
	do {
		if(z>1) {
			if((in=fopen(x[1],"r"))==NULL) {
				fprintf(stderr,"rev: cannot open %s\n",x[1]);
				exit(1);
			}
		}
		for(;;) {
			for(i=0; i<X; i++) {
				l[i]=c=getc(in);
				switch(c) {
				case EOF:
					goto eof;
				default:
					continue;
				case'\n':
					break;
				}
				break;
			}
			while(--i>=0)putc(l[i],stdout);
			putc('\n',stdout);
		}
eof:
		fclose(in);
		z--;
		x++;
	} while(z>1);
}
