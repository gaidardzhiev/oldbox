/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x64\x69\x72\x65\x63\x74\x6F\x72\x79\x3E"

void h(long s,char*b) {
	const char*u[]= {"B","KB","MB","GB","TB"};
	int ui=0;
	while(s>=1024&&ui<4) {
		s/=1024;
		ui++;
	}
	sprintf(b,"%ld %s",s,u[ui]);
}

long c(const char*p) {
	long t=0;
	struct dirent*e;
	struct stat fs;
	DIR*d=opendir(p);
	if(d==NULL) {
		perror("opendir");
		return 0;
	}
	while((e=readdir(d))!=NULL) {
		if(strcmp(e->d_name,".")!=0&&strcmp(e->d_name,"..")!= 0) {
			char fp[1024];
			snprintf(fp,sizeof(fp),"%s/%s",p,e->d_name);
			if(stat(fp, &fs)==0) {
				if(S_ISDIR(fs.st_mode)) {
					t+=c(fp);
				} else {
					t+=fs.st_size;
				}
			}
		}
	}
	closedir(d);
	return t;
}

int main(int z,char*x[]) {
	if(z<2) {
		fprintf(stderr,HEX"\n",x[0]);
		return EXIT_FAILURE;
	}
	char sb[20];
	long t=c(x[1]);
	h(t,sb);
	printf("total size of '%s': %s\n",x[1],sb);
	return EXIT_SUCCESS;
}
