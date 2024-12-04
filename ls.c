#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void ls(const char *p) {
	struct dirent *e;
	struct stat s;
	DIR *dp = opendir(p);
	if (dp == NULL) {
		perror("opendir");
		return;
	}
	while ((e = readdir(dp)) != NULL) {
		char f[65536];
		snprintf(f, sizeof(f), "%s/%s", p, e->d_name);
		if (stat(f, &s) < 0) {
			perror("stat");
			continue;
		}
		printf((S_ISDIR(s.st_mode)) ? "d" : "_");
		printf((s.st_mode & S_IRUSR) ? "r" : "_");
		printf((s.st_mode & S_IWUSR) ? "w" : "_");
		printf((s.st_mode & S_IXUSR) ? "x" : "_");
		printf((s.st_mode & S_IRGRP) ? "r" : "_");
		printf((s.st_mode & S_IWGRP) ? "w" : "_");
		printf((s.st_mode & S_IXGRP) ? "x" : "_");
		printf((s.st_mode & S_IROTH) ? "r" : "_");
		printf((s.st_mode & S_IWOTH) ? "w" : "_");
		printf((s.st_mode & S_IXOTH) ? "x" : "_");
		printf("	%ld ", s.st_nlink);
		struct passwd *pw = getpwuid(s.st_uid);
		struct group  *gr = getgrgid(s.st_gid);
		printf("	%s %s ", pw->pw_name, gr->gr_name);
		printf("	%lld ", (long long)s.st_size);
		printf("	%s\n", e->d_name);
	}
	closedir(dp);
}

int main(int z, char *x[]) {
	if (z > 1) {
		ls(x[1]);
	} else {
		ls(".");
	}
	return 0;
}
