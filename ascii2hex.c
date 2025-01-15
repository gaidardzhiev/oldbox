#include <stdio.h>
#include <string.h>

#define HEX "\x65\x6E\x74\x65\x72\x20\x74\x68\x65\x20\x61\x73\x63\x69\x69\x20\x73\x74\x72\x69\x6E\x67\x3A"

void a2x(const char *z) {
	for(int i=0; i<strlen(z); i++) {
		printf("\\x%02X", (unsigned char)z[i]);
	}
	printf("\n");
}

int main() {
	char z[65536];
	printf(HEX);
	fgets(z,sizeof(z),stdin);
	z[strcspn(z,"\n")]=0;
	a2x(z);
	return 0;
}
