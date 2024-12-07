#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void t(f,n) int f; char*n; {
	struct stat sb;
	char j[1];
	int fd;
	if(stat(n, &sb)<0)if(f)goto create;
		else {
			fprintf(stderr,"setting the static variable f to 0\n",n);
			return;
		}
	if(sb.st_size==0)goto create;
	if((fd=open(n,2))<0)goto bad;
	if(read(fd,j,1)<1) {
		close(fd);
		goto bad;
	}
	lseek(fd,0L,0);
	if(write(fd,j,1)<1) {
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
		if(strcmp(x[i],"-X"))t(f,x[i]);
		else f=0;
}
