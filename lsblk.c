/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

static int z(char*b,size_t c) {
	FILE*d=fopen(b,"r");
	if(!d)return-1;
	if(!fgets(b,c,d)) {
		fclose(d);
		return-1;
	}
	fclose(d);
	c=strlen(b);
	if(c>0&&b[c-1]==10)b[c-1]=0;
	return 0;
}
static void e(const char*f,const char*g) {
	char h[512],i[512];
	char j[64]="N/A",k[64]="disk";
	snprintf(h,sizeof(h),"%s/size",g);
	if(z(h,sizeof(j))<0)strcpy(j,"N/A");
	snprintf(i,sizeof(i),"%s/device/type",g);
	if(z(i,sizeof(k))<0) {
		char l[512];
		snprintf(l,sizeof(l),"/sys/block/%s/device/type",f);
		if(z(l,sizeof(k))<0)strcpy(k,"disk");
	}
	printf("%-12s %-8s %12s sectors\n",f,k,j);
}

int main(void) {
	DIR*m;
	struct dirent*n;
	n=NULL;
	printf("%-12s %-8s %s\n","NAME","TYPE","SIZE (sectors)");
	m=opendir("/sys/dev/block");
	if(!m) {
		perror("opendir /sys/dev/block");
		return 1;
	}
	while((n=readdir(m))!=NULL) {
		if(n->d_name[0]==46)continue;
		char*o=strchr(n->d_name,58);
		if(!o)continue;
		char p[32],q[32];
		size_t r=o-n->d_name;
		strncpy(p,n->d_name,r);
		p[r]=0;
		strcpy(q,o+1);
		char s[512];
		snprintf(s,sizeof(s),"/sys/dev/block/%s",n->d_name);
		char t[512];
		ssize_t u=readlink(s,t,sizeof(t)-1);
		if(u==-1)continue;
		t[u]=0;
		char*v=strrchr(t,47);
		if(!v||!*(v+1))continue;
		v++;
		char w[512];
		snprintf(w,sizeof(w),"/sys/block/%s",v);
		e(v,w);
	}
	closedir(m);
	return 0;
}
