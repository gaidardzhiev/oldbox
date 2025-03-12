#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

void u() {
	printf("usage:\n"
	"  ./test <option> <file/string>\n"
	"  ./test <string1> <option> <string2>\n"
	"options:\n"
	"  -e <file>			0 if <file> exists\n"
	"  -f <file>			0 if <file> is a regular file\n"
	"  -d <file>			0 if <file> is a directory\n"
	"  -s <file>			0 if <file> exists and has a size greater than zero\n"
	printf("  -z <string>			0 if <string> is empty\n");
	printf("  -n <string>			0 if <string> is not empty\n");
	printf("  <string1> = <string2>		0 if <string1> is equal to <string2>\n");
	printf("  <string1> != <string2>	0 if <string1> is not equal to <string2>\n");
}

int main(int z, char *x[]) {
	if (z < 2) {
		u();
		return 8;
	}
	if (strcmp(x[1], "-e") == 0 && z == 3) {
		struct stat b;
		if (stat(x[2], &b) == 0) {
			return 0;
		} else {
			return 1;
		}
	} else if (strcmp(x[1], "-f") == 0 && z == 3) {
		struct stat b;
		if (stat(x[2], &b) == 0 && S_ISREG(b.st_mode)) {
			return 0;
		} else {
			return 1;
		}
	} else if (strcmp(x[1], "-d") == 0 && z == 3) {
		struct stat b;
		if (stat(x[2], &b) == 0 && S_ISDIR(b.st_mode)) {
			return 0;
		} else {
			return 1;
		}
	} else if (strcmp(x[1], "-s") == 0 && z == 3) {
		struct stat b;
		if (stat(x[2], &b) == 0 && b.st_size > 0) {
			return 0;
		} else {
			return 1;
		}
	} else if (strcmp(x[1], "-z") == 0 && z == 3) {
		if (strlen(x[2]) == 0) {
			return 0;
		} else {
			return 1;
		}
	} else if (strcmp(x[1], "-n") == 0 && z == 3) {
		if (strlen(x[2]) > 0) {
			return 0;
		} else {
			return 1;
		}
	} else if (z == 4) {
		if (strcmp(x[2], "=") == 0) {
			if (strcmp(x[1], x[3]) == 0) {
				return 0;
			} else {
				return 1;
			}
		} else if (strcmp(x[2], "!=") == 0) {
			if (strcmp(x[1], x[3]) != 0) {
				return 0;
			} else {
				return 1;
			}
		} else {
			u();
			return 16;
		}
	} else {
		u();
		return 32;
	}
	return 0;
}
