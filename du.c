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
	struct stat file_stat;
	DIR*dir=opendir(p);
	if(dir==NULL) {
		perror("opendir");
		return 0;
	}
	while((entry=readdir(dir))!=NULL) {
		if(strcmp(entry->d_name,".")!=0&&strcmp(entry->d_name,"..")!= 0) {
			char full_path[1024];
			snprintf(full_path,sizeof(full_path),"%s/%s",p,entry->d_name);
			if(stat(full_path, &file_stat)==0) {
				if(S_ISDIR(file_stat.st_mode)) {
					t+=cds(full_path);
				} else {
					t+=file_stat.st_size;
				}
			}
		}
	}
	closedir(dir);
	return t;
}

int main(int argc,char*argv[]) {
	if(argc<2) {
		fprintf(stderr,HEX"\n",argv[0]);
		return EXIT_FAILURE;
	}
	char size_buffer[20];
	long t=cds(argv[1]);
	hrs(t,size_buffer);
	printf("total size of '%s': %s\n",argv[1],size_buffer);
	return EXIT_SUCCESS;
}
