#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define LENGTH 512
#define PROC "/proc"

int i(const char *str) {
	while(*str) {
		if(!isdigit(*str))return 0;
		str++;
	}
	return 1;
}

void r(const char *p) {
	char q[LENGTH];
	snprintf(q,sizeof(q),"%s/%s/stat",PROC,p);
	FILE *f = fopen(q,"r");
	if(!f)return;
	char c[LENGTH];
	int ppid,pgrp,tty_nr;
	fscanf(f,"%*d %s %*c %d %d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d",c, &ppid, &pgrp, &tty_nr);
	fclose(f);
	char tty[10];
	snprintf(tty,sizeof(tty),"%d",tty_nr);
	printf("%s\t%s\t%s\n",p,tty,c);
}

int main()
{
	DIR*dir=opendir(PROC);
	struct dirent*entry;
	if(!dir) {
		perror("opendir");
		return EXIT_FAILURE;
	}
	printf("pid\ttty\tcmd\n");
	while((entry=readdir(dir))!=NULL) {
		if(i(entry->d_name)) {
			r(entry->d_name);
		}
	}
	closedir(dir);
	return EXIT_SUCCESS;
}
