#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x64\x69\x72\x65\x63\x74\x6F\x72\x79\x3E"

void hrs(long s,char*b) {
	const char*u[]= {"B","KB","MB","GB","TB"};
	int ui=0;
	while(s>=1024&&ui<4) {
		s/=1024;
		ui++;
	}
	sprintf(b,"%ld %s",s,u[ui]);
}

long cds(const char*p) {
	long t=0;
	struct dirent*entry;
	struct stat fs;
	DIR*d=opendir(p);
	if(d==NULL) {
		perror("opendir");
		return 0;
	}
	while((entry=readdir(d))!=NULL) {
		if(strcmp(entry->d_name,".")!=0&&strcmp(entry->d_name,"..")!= 0) {
			char fp[1024];
			snprintf(fp,sizeof(fp),"%s/%s",p,entry->d_name);
			if(stat(fp, &fs)==0) {
				if(S_ISDIR(fs.st_mode)) {
					t+=cds(fp);
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
	char size_buffer[20];
	long t=cds(x[1]);
	hrs(t,size_buffer);
	printf("total size of '%s': %s\n",x[1],size_buffer);
	return EXIT_SUCCESS;
}
