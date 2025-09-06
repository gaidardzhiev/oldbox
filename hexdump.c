/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>

#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x66\x69\x6C\x65\x6E\x61\x6D\x65\x3E"

void hex(const unsigned char*b,size_t l) {
	for(size_t i=0; i<l; i++) {
		printf("%02x ",b[i]);
		if((i+1)%16==0) {
			printf(" | ");
			for(size_t j=i-15; j<=i; j++) {
				if(b[j]>=32&&b[j]<=126) {
					printf("%c",b[j]);
				} else {
					printf(".");
				}
			}
			printf("\n");
		}
	}
	if(l%16!=0) {
		size_t padding=16-(l%16);
		for(size_t i=0; i<padding; i++) {
			printf("   ");
		}
		printf(" | ");
		for(size_t j=l-(l%16); j<l; j++) {
			if(b[j]>=32&&b[j]<=126) {
				printf("%c",b[j]);
			} else {
				printf("•");
			}
		}
		printf("\n");
	}
}

int main(int z,char*x[]) {
	if(z!=2) {
		fprintf(stderr,HEX"\n",x[0]);
		return EXIT_FAILURE;
	}
	FILE*file=fopen(x[1],"rb");
	if(!file) {
		perror("error opening file");
		return EXIT_FAILURE;
	}
	unsigned char buf[16];
	size_t bytesRead;
	while((bytesRead=fread(buf,1,sizeof(buf),file))>0) {
		hex(buf,bytesRead);
	}
	fclose(file);
	return EXIT_SUCCESS;
}
