#include <stdio.h>
#include <string.h>

#define HEX "\x65\x6E\x74\x65\x72\x20\x74\x68\x65\x20\x61\x73\x63\x69\x69\x20\x73\x74\x72\x69\x6E\x67\x3A"

void ascii2hex(const char*input){for(int i=0;i<strlen(input);i++){printf("\\x%02X",(unsigned char)input[i]);}printf("\n");}int main(){char input[1024];printf(HEX);fgets(input,sizeof(input),stdin);input[strcspn(input,"\n")]=0;ascii2hex(input);return 0;}
