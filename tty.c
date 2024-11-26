#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
	char*tty=ttyname(STDIN_FILENO);
	if (argc==2&&strcmp(argv[1],"-s")==0) {
	} else {
		printf("%s\n",tty?tty:"not a tty");
	}
	return tty?EXIT_SUCCESS:EXIT_FAILURE;
}
