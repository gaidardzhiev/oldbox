/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int z, char **x) {
	char*tty=ttyname(STDIN_FILENO);
	if (z==2&&strcmp(x[1],"-s")==0) {
	} else {
		printf("%s\n",tty?tty:"not a tty");
	}
	return tty?EXIT_SUCCESS:EXIT_FAILURE;
}
