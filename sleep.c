#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
	int c, n = 0;
	char *i;
	if (argc < 2) {
		fprintf(stderr, "usage: sleep <sec> \n");
		return EXIT_FAILURE;
	}
	i = argv[1];
	while ((c = *i++)) {
		if (c < '0' || c > '9') {
			fprintf(stderr, "error: invalid character...\n");
			return EXIT_FAILURE;
		}
		n = n * 10 + (c - '0');
	}
	sleep(n);
	return EXIT_SUCCESS;
}
