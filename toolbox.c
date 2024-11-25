#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	const char *dir = "/home/src/1v4n/tools/";
	if (argc < 2) {
		printf("usage: %s <echo|cat|cp|basename|kill|ln|mount|nice|printf|rev|sleep|sync|tee|touch|tr|true|tty|umount|wc|yes|shell|pwd|ps|grep|du|rm|ascii2hex|hexdump|false|replace|readelf|strings|ls|xoda|id> <options>\n", argv[0]);
		return 1;
	}
	char command[2048];
	snprintf (command, sizeof (command), "%s/%s", dir, argv[1]);
	for (int i=2; i < argc; i++) {
		strcat(command, " ");
		strcat(command, argv[i]);
	}
	if (strcmp(argv[1], "printf") == 0) {
		strcat(command, " \"\\n\"");
	}
	system(command);
	return 0;
}
