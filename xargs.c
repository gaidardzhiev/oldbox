/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define O int main(int z,char*x[]){if(z<2){fprintf(stderr,"usage: %s <command> <args>\n",x[0]);exit(1);}char in[1024];char *p[512+z];int c=0,i;
#define B for(i=1;i<z&&i<512;i++)p[c++]=x[i];
#define F while(fgets(in,sizeof(in),stdin)){
#define U char *tok=strtok(in," \t\n");while(tok){
#define S if(c==512+z-1){p[c]=NULL;pid_t pid=fork();if(pid==0){execvp(p[0],p);perror("execvp");exit(127);}else if(pid>0){int s;waitpid(pid,&s,0);}else{perror("fork");exit(1);}c=z-1;}
#define C p[c++]=tok;tok=strtok(NULL," \t\n");}
#define A }
#define T if(c>z-1){p[c]=NULL;pid_t pid=fork();if(pid==0){execvp(p[0],p);perror("execvp");exit(127);}else if(pid>0){int status;waitpid(pid,&status,0);}else{perror("fork");exit(1);}}
#define E return 0;}

O B F U S C A T E
