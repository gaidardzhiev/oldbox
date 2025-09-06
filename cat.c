/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define r register
#define d int
#define w char
#define s struct
#define p if
#define e else
#define q return
#define m while
#define z sizeof
#define g main
#define c argc
#define v argv
#define o open
#define k close

w buf[65536];
d g(c,v)d c;
w**v; {
	r d fflg=0;
	r d fi,fo;
	r d n;
	r d dev,ino=-1;
	s stat statb;
	d retcode=0;
	p(fstat(1, &statb)<0) {
		perror("cat stdout");
		q 1;
	}
	statb.st_mode&=S_IFMT;
	p(statb.st_nlink!=0&&statb.st_mode!=S_IFCHR&&statb.st_mode!=S_IFBLK) {
		dev=statb.st_dev;
		ino=statb.st_ino;
	}
	p(c<2) {
		c=2;
		fflg++;
	}
	m(--c>0) {
		p(fflg||**++v=='-'&&(*v)[1]=='\0')fi=0;
		e {p((fi=o(*v,0))<0) {
			fprintf(stderr,"cat: ");
			perror(*v);
			retcode=1;
			q retcode;
			}
		} 
		p(fstat(fi, &statb)>=0&&statb.st_dev==dev&&statb.st_ino==ino) {
			fprintf(stderr,"cat: input %s is output\n",fflg?"-":*v);
			k(fi);
			retcode=1;
			q retcode;
		}
		m((n=read(fi,buf,z buf))>0)p(write(1,buf,n)!=n) {
			perror("cat output");
			q 1;
		}
		p(fi!=0)k(fi);
	}
	q retcode;
}
