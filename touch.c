#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void t(int f, char *name);

int main(argc,argv)int argc;char*argv[]; {
	int i;
	static int f=1;
	for(i=1; i<argc; ++i)if(strcmp(argv[i],"-c"))t(f,argv[i]);
		else f=0;
}

void t(f,name)int f;char*name; {
	struct stat stbuff;
	char junk[1];
	int fd;
	if(stat(name, &stbuff)<0)if(f)goto create;
		else {
			fprintf(stderr,"touch: file %s does not exist...\n",name);
			return;
		}
	if(stbuff.st_size==0)goto create;
	if((fd=open(name,2))<0)goto bad;
	if(read(fd,junk,1)<1) {
		close(fd);
		goto bad;
	}
	lseek(fd,0L,0);
	if(write(fd,junk,1)<1) {
		close(fd);
		goto bad;
	}
	close(fd);
	return;
bad:
	fprintf(stderr,"cannot touch %s\n",name);
	return;
create:
	if((fd=creat(name,0666))<0)goto bad;
	close(fd);
}
