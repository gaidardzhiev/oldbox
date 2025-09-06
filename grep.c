/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <string.h>

#define BUF 65536
#define G "\033[32m"
#define R "\033[0m"
#define E "\x63\x6F\x75\x6C\x64\x20\x6E\x6F\x74\x20\x6F\x70\x65\x6E\x20\x66\x69\x6C\x65"
#define P "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x70\x61\x74\x74\x65\x72\x6E\x3E\x20\x3C\x66\x69\x6C\x65\x6E\x61\x6D\x65\x3E"

void h(const char*l, const char*p) {
	const char*o=l;
	while((o=strstr(o,p))!=NULL) {
		fwrite(l,1,o-l,stdout);
		printf(G"%.*s"R, (int)strlen(p),o);
		o+=strlen(p);
		l=o;
	}
	printf("%s",l);
}

void m(const char*n, const char*p) {
	FILE*f=fopen(n,"r");
	if(!f) {
		fprintf(stderr,E"\n");
		return;
	}
	char b[BUF];
	while(fgets(b,BUF,f)) {
		if(strstr(b,p)) {
			h(b,p);
			printf("\n");
		}
	}
	fclose(f);
}

int main(int c, char*v[]) {
	if(c!=3) {
		fprintf(stderr,P"\n",v[0]);
		return 1;
	}
	m(v[2],v[1]);
	return 0;
}
