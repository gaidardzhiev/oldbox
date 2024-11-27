#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int c, char *v[]) {
	const char *d = "/home/src/1v4n/toolbox/";
	if (c < 2) {
		printf("usage: %s <echo|cat|cp|basename|kill|ln|mount|nice|printf|rev|sleep|sync|tee|touch|tr|true|tty|umount|wc|yes|shell|pwd|ps|grep|du|rm|ascii2hex|hexdump|false|replace|readelf|strings|ls|xoda|id> <options>\n",v[0]);
		return 1;
	}
	char t[2048];
	snprintf (t, sizeof (t), "%s/%s", d, v[1]);
	for (int i=2; i < c; i++) {
		strcat(t, " ");
		strcat(t, v[i]);
	}
	if (strcmp(v[1], "printf") == 0) {
		strcat(t, " \"\\n\"");
	}
	system(t);
	return 0;
}
