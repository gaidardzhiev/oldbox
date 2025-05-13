#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define L 512
#define P "/proc"

int i(const char *str) {
	while(*str) {
		if(!isdigit(*str))return 0;
		str++;
	}
	return 1;
}

void r(const char *p) {
	char q[L];
	snprintf(q,sizeof(q),"%s/%s/stat",P,p);
	FILE *f = fopen(q,"r");
	if(!f)return;
	char c[L];
	int d,r,n;
	fscanf(f,"%*d %s %*c %d %d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d",c,&d,&r,&n);
	fclose(f);
	char t[10];
	snprintf(t,sizeof(t),"%d",n);
	printf("%s\t%s\t%s\n",p,t,c);
}

int main() {
	DIR*dir=opendir(P);
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
