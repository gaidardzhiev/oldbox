#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

int main(int z, char *x[]) {
	int n = 10;
	if (z > 1 && x[1][0] == '-') {
		n = atoi(&x[1][1]);
		z--;
		x++;
	}
	if (z < 2) {
		fputs("usage: nice <opt> <cmd <arg>...>>\n", stderr);
		exit(EXIT_FAILURE);
	}
	if (setpriority(PRIO_PROCESS, 0, n) == -1) {
		perror("failed");
		exit(EXIT_FAILURE);
	}
	execvp(x[1], x + 1);
	perror(x[1]);
	exit(EXIT_FAILURE);
}
