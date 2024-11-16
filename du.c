#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define HEX "\x75\x73\x61\x67\x65\x3A\x20\x25\x73\x20\x3C\x64\x69\x72\x65\x63\x74\x6F\x72\x79\x3E"

void human_readable_size(long size,char*buffer)
{
	const char*units[]= {"B","KB","MB","GB","TB"};
	int unit_index=0;
	while(size>=1024&&unit_index<4) {
		size/=1024;
		unit_index++;
	}
	sprintf(buffer,"%ld %s",size,units[unit_index]);
}

long calculate_directory_size(const char*path)
{
	long total_size=0;
	struct dirent*entry;
	struct stat file_stat;
	DIR*dir=opendir(path);
	if(dir==NULL) {
		perror("opendir");
		return 0;
	}
	while((entry=readdir(dir))!=NULL) {
		if(strcmp(entry->d_name,".")!=0&&strcmp(entry->d_name,"..")!= 0) {
			char full_path[1024];
			snprintf(full_path,sizeof(full_path),"%s/%s",path,entry->d_name);
			if(stat(full_path, &file_stat)==0) {
				if(S_ISDIR(file_stat.st_mode)) {
					total_size+=calculate_directory_size(full_path);
				} else {
					total_size+=file_stat.st_size;
				}
			}
		}
	}
	closedir(dir);
	return total_size;
}

int main(int argc,char*argv[])
{
	if(argc<2) {
		fprintf(stderr,HEX"\n",argv[0]);
		return EXIT_FAILURE;
	}
	char size_buffer[20];
	long total_size=calculate_directory_size(argv[1]);
	human_readable_size(total_size,size_buffer);
	printf("total size of '%s': %s\n",argv[1],size_buffer);
	return EXIT_SUCCESS;
}
