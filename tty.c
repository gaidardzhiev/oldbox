#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char*ttyName=ttyname(STDIN_FILENO);
	if (argc==2&&strcmp(argv[1],"-s")==0) {
	} else {
		printf("%s\n",ttyName?ttyName:"not a tty");
	}
	return ttyName?EXIT_SUCCESS:EXIT_FAILURE;
}
