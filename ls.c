#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

void ls(const char *path) {
	struct dirent *entry;
	struct stat fileStat;
	DIR *dp = opendir(path);
	if (dp == NULL) {
		perror("opendir");
		return;
	}
	while ((entry = readdir(dp)) != NULL) {
		char fullPath[2048];
		snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);
		if (stat(fullPath, &fileStat) < 0) {
			perror("stat");
			continue;
		}
		printf((S_ISDIR(fileStat.st_mode)) ? "d" : "_");
		printf((fileStat.st_mode & S_IRUSR) ? "r" : "_");
		printf((fileStat.st_mode & S_IWUSR) ? "w" : "_");
		printf((fileStat.st_mode & S_IXUSR) ? "x" : "_");
		printf((fileStat.st_mode & S_IRGRP) ? "r" : "_");
		printf((fileStat.st_mode & S_IWGRP) ? "w" : "_");
		printf((fileStat.st_mode & S_IXGRP) ? "x" : "_");
		printf((fileStat.st_mode & S_IROTH) ? "r" : "_");
		printf((fileStat.st_mode & S_IWOTH) ? "w" : "_");
		printf((fileStat.st_mode & S_IXOTH) ? "x" : "_");
		printf("	%ld ", fileStat.st_nlink);
		struct passwd *pw = getpwuid(fileStat.st_uid);
		struct group  *gr = getgrgid(fileStat.st_gid);
		printf("	%s %s ", pw->pw_name, gr->gr_name);
		printf("	%lld ", (long long)fileStat.st_size);
		printf("	%s\n", entry->d_name);
	}
	closedir(dp);
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		ls(argv[1]);
	} else {
		ls(".");
	}
	return 0;
}
