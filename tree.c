/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void t(const char *b, char *p) {
	struct dirent *dp;
	DIR *d = opendir(b);
	if (!d) {
		return;
	}
	while ((dp = readdir(d)) != NULL) {
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
			continue;
		}
		printf("%s|____%s\n", p, dp->d_name);
		char a[1024];
		snprintf(a, sizeof(a), "%s/%s", b, dp->d_name);
		if (dp->d_type == DT_DIR) {
			strcat(p, "   ");
			t(a, p);
			p[strlen(p) - 3] = '\0';
		}
	}
	closedir(d);
}

int main(int z, char *x[]) {
	const char *a = (z > 1) ? x[1] : ".";
	printf("%s\n",a);
	char p[1024] = "";
	t(a, p);
	return 0;
}
