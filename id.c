#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

void u() {
	uid_t ui = getuid();
	gid_t gi = getgid();
	struct passwd *p = getpwuid(ui);
	struct group *u = getgrgid(gi);
	printf("uid=%d [%s]\ngid=%d [%s]\n", ui, p->pw_name, gi, u->gr_name);
}

void e() {
	uid_t e = geteuid();
	struct passwd *p = getpwuid(e);
	printf("euid=%d [%s]\n", e, p->pw_name);
}

void g() {
	gid_t f[32];
	int n = 32;
	getgrouplist(getpwuid(getuid())->pw_name, getgid(), f, &n);
	printf("groups=");
	for (int i = 0; i < n; i++) {
		struct group *gr = getgrgid(f[i]);
		if (gr != NULL) {
			printf("%d [%s]", f[i], gr->gr_name);
			if (i < n - 1) {
				printf("\n");
			}
		}
	}
	printf("\n");
}

int main() {
	u();
	e();
	g();
	return 0;
}
