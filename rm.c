/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>

#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x66\x69\x6C\x65\x30\x3E\x20\x3C\x66\x69\x6C\x65\x31\x3E\x20\x2E\x2E\x2E"

int main(int z, char*x[]) {
	if(z<2) {
		fprintf(stderr,HEX"\n",x[0]);
		return 1;
	}
	for(int i=1; i<z; i++) {
		if(remove(x[i])!=0) {
			perror(x[i]);
		}
	}
	return 0;
}
