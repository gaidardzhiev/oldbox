#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MCL 2048
#define MAL 128

void ec(char*c) {
	char*args[MAL];
	pid_t pid,wpid;
	int status;
	char*token=strtok(c," \n");
	int i=0;
	while(token!=NULL&&i<MAL-1) {
		args[i++]=token;
		token=strtok(NULL," \n");
	}
	args[i]=NULL;
	if((pid=fork())==-1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if(pid==0) {
		if(execvp(args[0],args)==-1) {
			perror("exec");
			exit(EXIT_FAILURE);
		}
	} else {
		do {
			wpid=waitpid(pid, &status,WUNTRACED);
		} while(!WIFEXITED(status)&&!WIFSIGNALED(status));
	}
}

int main() {
	char c[MCL];
	while(1) {
		printf("shell# ");
		if(fgets(c,sizeof(c),stdin)==NULL) {
			break;
		}
		if(strcmp(c,"exit\n")==0) {
			break;
		}
		ec(c);
	}
	return 0;
}
