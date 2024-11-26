#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void fusage() {
	printf("usage: kill <SIG> <PID>\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	int sign = SIGTERM;
	int error = 0;
	if (argc < 2) {
		fusage();
	}
	if (argv[1][0] == '-') {
		sign = atoi(argv[1] + 1);
		argc--;
		argv++;
	}
	argv++;
	while (argc > 1) {
		int pid = atoi(*argv);
		if (pid <= 0) {
			fusage();
		}
		if (kill(pid, sign) < 0) {
			perror("error sending signal");
			error = 1;
		}
		argc--;
		argv++;
	}
	return error;
}
