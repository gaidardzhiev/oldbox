#include <stdio.h>
#include <stdlib.h>

#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x66\x69\x6C\x65\x30\x3E\x20\x3C\x66\x69\x6C\x65\x31\x3E\x20\x2E\x2E\x2E"

int main(int argc,char*argv[]){if(argc<2){fprintf(stderr,HEX"\n",argv[0]);return 1;}for(int i=1;i<argc;i++){if(remove(argv[i])!=0){perror(argv[i]);}}return 0;}
