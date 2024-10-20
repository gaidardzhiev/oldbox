#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 2048
#define MAX_ARG_LENGTH 128

void execute_command(char*command)
{
	char*args[MAX_ARG_LENGTH];
	pid_t pid,wpid;
	int status;
	char*token=strtok(command," \n");
	int i=0;
	while(token!=NULL&&i<MAX_ARG_LENGTH-1) {
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
int main()
{
	char command[MAX_CMD_LENGTH];
	while(1) {
		printf("shell# ");
		if(fgets(command,sizeof(command),stdin)==NULL) {
			break;
		}
		if(strcmp(command,"exit\n")==0) {
			break;
		}
		execute_command(command);
	}
	return 0;
}
