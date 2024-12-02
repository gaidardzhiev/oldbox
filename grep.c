#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 65536
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define STDERR "\x63\x6F\x75\x6C\x64\x20\x6E\x6F\x74\x20\x6F\x70\x65\x6E\x20\x66\x69\x6C\x65"
#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x70\x61\x74\x74\x65\x72\x6E\x3E\x20\x3C\x66\x69\x6C\x65\x6E\x61\x6D\x65\x3E"

void h(const char*line,const char*pattern) {
	const char*pos=line;
	while((pos=strstr(pos,pattern))!=NULL) {
		fwrite(line,1,pos-line,stdout);
		printf(GREEN"%.*s"RESET, (int)strlen(pattern),pos);
		pos+=strlen(pattern);
		line=pos;
	}
	printf("%s",line);
}

void match(const char*filename,const char*pattern) {
	FILE*file=fopen(filename,"r");
	if(!file) {
		fprintf(stderr,STDERR"\n");
		return;
	}
	char buffer[BUFFER];
	while(fgets(buffer,BUFFER,file)) {
		if(strstr(buffer,pattern)) {
			h(buffer,pattern);
			printf("\n");
		}
	}
	fclose(file);
}

int main(int argc,char*argv[]) {
	if(argc!=3) {
		fprintf(stderr,HEX"\n",argv[0]);
		return EXIT_FAILURE;
	}
	match(argv[2],argv[1]);
	return EXIT_SUCCESS;
}
