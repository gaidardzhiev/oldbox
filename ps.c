#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#define LENGTH 512
#define PROC "/proc"
int is_number(const char*str){while(*str){if(!isdigit(*str))return 0;str++;}return 1;}void read_process_info(const char*pid){char path[LENGTH];snprintf(path,sizeof(path),"%s/%s/stat",PROC,pid);FILE*file=fopen(path,"r");if(!file)return;char cmd[LENGTH];int ppid,pgrp,tty_nr;fscanf(file,"%*d %s %*c %d %d %d %*d %*d %*d %*d %*d %*d %*d %*d %*d",cmd,&ppid,&pgrp,&tty_nr);fclose(file);char tty[10];snprintf(tty,sizeof(tty),"%d",tty_nr);printf("%s\t%s\t%s\n",pid,tty,cmd);}int main(){DIR*dir=opendir(PROC);struct dirent*entry;if(!dir){perror("opendir");return EXIT_FAILURE;}printf("pid\ttty\tcmd\n");while((entry=readdir(dir))!=NULL){if(is_number(entry->d_name)){read_process_info(entry->d_name);}}closedir(dir);return EXIT_SUCCESS;}

