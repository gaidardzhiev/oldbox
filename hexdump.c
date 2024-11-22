#include <stdio.h>
#include <stdlib.h>

#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x66\x69\x6C\x65\x6E\x61\x6D\x65\x3E"

void print_hex(const unsigned char*buffer,size_t length) {
	for(size_t i=0; i<length; i++) {
		printf("%02x ",buffer[i]);
		if((i+1)%16==0) {
			printf(" | ");
			for(size_t j=i-15; j<=i; j++) {
				if(buffer[j]>=32&&buffer[j]<=126) {
					printf("%c",buffer[j]);
				} else {
					printf("•");
				}
			}
			printf("\n");
		}
	}
	if(length%16!=0) {
		size_t padding=16-(length%16);
		for(size_t i=0; i<padding; i++) {
			printf("   ");
		}
		printf(" | ");
		for(size_t j=length-(length%16); j<length; j++) {
			if(buffer[j]>=32&&buffer[j]<=126) {
				printf("%c",buffer[j]);
			} else {
				printf("•");
			}
		}
		printf("\n");
	}
}

int main(int argc,char*argv[]) {
	if(argc!=2) {
		fprintf(stderr,HEX"\n",argv[0]);
		return EXIT_FAILURE;
	}
	FILE*file=fopen(argv[1],"rb");
	if(!file) {
		perror("error opening file");
		return EXIT_FAILURE;
	}
	unsigned char buffer[16];
	size_t bytesRead;
	while((bytesRead=fread(buffer,1,sizeof(buffer),file))>0) {
		print_hex(buffer,bytesRead);
	}
	fclose(file);
	return EXIT_SUCCESS;
}
