#include <stdio.h>
#include <stdlib.h>

#define N 4096

char l[N];
FILE *in;
int main(argc,argv)char**argv; {
	register i,c;
	in=stdin;
	do {
		if(argc>1) {
			if((in=fopen(argv[1],"r"))==NULL) {
				fprintf(stderr,"rev: cannot open %s\n",argv[1]);
				exit(1);
			}
		}
		for(;;) {
			for(i=0; i<N; i++) {
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
		argc--;
		argv++;
	} while(argc>1);
}
