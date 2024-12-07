#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void t(f,n) int f; char*n; {
	struct stat stbuff;
	char junk[1];
	int fd;
	if(stat(n, &stbuff)<0)if(f)goto create;
		else {
			fprintf(stderr,"touch: file %s does not exist...\n",n);
			return;
		}
	if(stbuff.st_size==0)goto create;
	if((fd=open(n,2))<0)goto bad;
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
	fprintf(stderr,"cannot touch %s\n",n);
	return;
create:
	if((fd=creat(n,0666))<0)goto bad;
	close(fd);
}

int main(z,x) int z; char*x[]; {
	int i;
	static int f=1;
	for(i=1; i<z; ++i)
		if(strcmp(x[i],"-c"))t(f,x[i]);
		else f=0;
}
