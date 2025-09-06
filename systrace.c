/*
 * Copyright (C) 2025 Ivan Gaydardzhiev
 * Licensed under the GPL-3.0-only
 */

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#ifdef __arm__
struct pt_regs_arm32 {
	unsigned long uregs[18];
};
#define ARM_r0  0
#define ARM_r1  1
#define ARM_r2  2
#define ARM_r3  3
#define ARM_r4  4
#define ARM_r5  5
#define ARM_r6  6
#define ARM_r7  7
#define ARM_pc  15

const char *sysn(long scno) {
	switch (scno) {
	case 0: return "restart_syscall";
	case 1: return "exit";
	case 2: return "fork";
	case 3: return "read";
	case 4: return "write";
	case 5: return "open";
	case 6: return "close";
	case 7: return "waitpid";
	case 8: return "creat";
	case 9: return "link";
	case 10: return "unlink";
	case 11: return "execve";
	case 12: return "chdir";
	case 13: return "time";
	case 14: return "mknod";
	case 15: return "chmod";
	case 16: return "lchown";
	case 18: return "stat";
	case 19: return "lseek";
	case 20: return "getpid";
	case 21: return "mount";
	case 22: return "umount";
	case 23: return "setuid";
	case 24: return "getuid";
	case 25: return "stime";
	case 26: return "ptrace";
	case 27: return "alarm";
	case 28: return "fstat";
	case 29: return "pause";
	case 30: return "utime";
	case 31: return "stty";
	case 32: return "gtty";
	case 33: return "access";
	case 34: return "nice";
	case 35: return "sync";
	case 36: return "kill";
	case 37: return "rename";
	case 38: return "mkdir";
	case 39: return "rmdir";
	case 40: return "dup";
	case 41: return "pipe";
	case 42: return "times";
	case 43: return "brk";
	case 44: return "setgid";
	case 45: return "getgid";
	case 46: return "signal";
	case 47: return "geteuid";
	case 48: return "getegid";
	case 49: return "acct";
	case 50: return "fchdir";
	case 51: return "smmap";
	case 52: return "bdflush";
	case 53: return "sysfs";
	case 54: return "personality";
	case 55: return "setfsuid";
	case 56: return "setfsgid";
	case 57: return "pivot_root";
	case 58: return "mincore";
	case 59: return "madvise";
	case 60: return "getdents";
	case 61: return "fcntl";
	case 62: return "unused";
	case 63: return "flock";
	case 64: return "fsync";
	case 65: return "async_sched";
	case 66: return "sync_file_range";
	case 67: return "sendfile";
	case 68: return "truncate";
	case 69: return "ftruncate";
	case 70: return "fchmod";
	case 71: return "fchown";
	case 72: return "getpriority";
	case 73: return "setpriority";
	case 74: return "statfs";
	case 75: return "fstatfs";
	case 76: return "ioprio_set";
	case 77: return "ioprio_get";
	case 78: return "quota";
	case 79: return "capget";
	case 80: return "capset";
	case 81: return "sigaltstack";
	case 82: return "sendfile64";
	case 83: return "getdents64";
	case 84: return "fadvise64";
	case 85: return "fallocate";
	case 86: return "timer_create";
	case 87: return "timer_settime";
	case 88: return "timer_gettime";
	case 89: return "timer_getoverrun";
	case 90: return "timer_delete";
	case 91: return "clock_settime";
	case 92: return "clock_gettime";
	case 93: return "clock_getres";
	case 94: return "clock_nanosleep";
	case 95: return "exit_group";
	case 96: return "epoll_create";
	case 97: return "epoll_ctl";
	case 98: return "epoll_wait";
	case 99: return "remap_file_pages";
	case 100: return "set_tid_address";
	case 101: return "timer_gettime";
	case 102: return "timer_settime";
	case 103: return "timer_delete";
	case 104: return "utimensat";
	case 105: return "signalfd";
	case 106: return "fallocate";
	case 107: return "timerfd_create";
	case 108: return "eventfd";
	case 109: return "timerfd_settime";
	case 110: return "timerfd_gettime";
	case 111: return "accept4";
	case 112: return "signalfd4";
	case 113: return "eventfd2";
	case 114: return "epoll_create1";
	case 115: return "dup3";
	case 116: return "pipe2";
	case 117: return "inotify_init1";
	case 118: return "preadv";
	case 119: return "pwritev";
	case 120: return "rt_tgsigqueueinfo";
	case 121: return "perf_event_open";
	case 122: return "recvmmsg";
	case 123: return "fanotify_init";
	case 124: return "fanotify_mark";
	case 125: return "prlimit64";
	case 126: return "name_to_handle_at";
	case 127: return "open_by_handle_at";
	case 128: return "clock_adjtime";
	case 129: return "syncfs";
	case 130: return "sendmmsg";
	case 131: return "setns";
	case 132: return "getcpu";
	case 133: return "process_vm_readv";
	case 134: return "process_vm_writev";
	default: {
		static char unknown[32];
		snprintf(unknown, sizeof(unknown), "syscall_%ld", scno);
		return unknown;
	}
	}
}
#endif

#ifdef __x86_64__
struct pt_regs_x86_64 {
	unsigned long r15;
	unsigned long r14;
	unsigned long r13;
	unsigned long r12;
	unsigned long rbp;
	unsigned long rbx;
	unsigned long r11;
	unsigned long r10;
	unsigned long r9;
	unsigned long r8;
	unsigned long rax;
	unsigned long rcx;
	unsigned long rdx;
	unsigned long rsi;
	unsigned long rdi;
	unsigned long orig_rax;
	unsigned long rip;
	unsigned long cs;
	unsigned long eflags;
	unsigned long rsp;
	unsigned long ss;
};
#define X86_64_ORIG_RAX  15
#define X86_64_RDI       14
#define X86_64_RSI       13
#define X86_64_RDX       12
#define X86_64_RCX       11
#define X86_64_R8        9
#define X86_64_R9        10

const char *sysn(long scno) {
	switch (scno) {
	case 0: return "read";
	case 1: return "write";
	case 2: return "open";
	case 3: return "close";
	case 4: return "stat";
	case 5: return "fstat";
	case 6: return "lstat";
	case 7: return "poll";
	case 8: return "lseek";
	case 9: return "mmap";
	case 10: return "mprotect";
	case 11: return "munmap";
	case 12: return "brk";
	case 13: return "rt_sigaction";
	case 14: return "rt_sigprocmask";
	case 15: return "rt_sigreturn";
	case 16: return "ioctl";
	case 17: return "pread64";
	case 18: return "pwrite64";
	case 19: return "readv";
	case 20: return "writev";
	case 21: return "access";
	case 22: return "pipe";
	case 23: return "select";
	case 24: return "sched_yield";
	case 25: return "mremap";
	case 26: return "msync";
	case 27: return "mincore";
	case 28: return "madvise";
	case 29: return "shmget";
	case 30: return "shmat";
	case 31: return "shmctl";
	case 32: return "dup";
	case 33: return "dup2";
	case 34: return "pause";
	case 35: return "nanosleep";
	case 36: return "getitimer";
	case 37: return "alarm";
	case 38: return "setitimer";
	case 39: return "getpid";
	case 40: return "sendfile";
	case 41: return "socket";
	case 42: return "connect";
	case 43: return "accept";
	case 44: return "sendto";
	case 45: return "recvfrom";
	case 46: return "sendmsg";
	case 47: return "recvmsg";
	case 48: return "shutdown";
	case 49: return "bind";
	case 50: return "listen";
	case 51: return "getsockname";
	case 52: return "getpeername";
	case 53: return "socketpair";
	case 54: return "setsockopt";
	case 55: return "getsockopt";
	case 56: return "clone";
	case 57: return "fork";
	case 58: return "vfork";
	case 59: return "execve";
	case 60: return "exit";
	case 61: return "wait4";
	case 62: return "kill";
	case 63: return "uname";
	case 64: return "semget";
	case 65: return "semop";
	case 66: return "semctl";
	case 67: return "shmdt";
	case 68: return "msgget";
	case 69: return "msgsnd";
	case 70: return "msgrcv";
	case 71: return "msgctl";
	case 72: return "fcntl";
	case 73: return "flock";
	case 74: return "fsync";
	case 75: return "fdatasync";
	case 76: return "truncate";
	case 77: return "ftruncate";
	case 78: return "getdents";
	case 79: return "getcwd";
	case 80: return "chdir";
	case 81: return "fchdir";
	case 82: return "rename";
	case 83: return "mkdir";
	case 84: return "rmdir";
	case 85: return "creat";
	case 86: return "link";
	case 87: return "unlink";
	case 88: return "symlink";
	case 89: return "readlink";
	case 90: return "chmod";
	case 91: return "fchmod";
	case 92: return "chown";
	case 93: return "fchown";
	case 94: return "lchown";
	case 95: return "umask";
	case 96: return "gettimeofday";
	case 97: return "getrlimit";
	case 98: return "getrusage";
	case 99: return "sysinfo";
	case 100: return "times";
	// add more x86_64 syscalls as desired
	default: {
		static char unknown[32];
		snprintf(unknown, sizeof(unknown), "syscall_%ld", scno);
		return unknown;
	}
	}
}
#endif

static const char *sign(int sig) {
	if (sig == 133) return "SIGSYS";
	const char *name = strsignal(sig);
	if (!name) return "Unknown";
	return name;
}

void p(long scno, unsigned long args[7], int entering) {
	if (entering) {
		printf("syscall enter: %s(%#lx, %#lx, %#lx, %#lx, %#lx, %#lx, %#lx)\n",
			sysn(scno),
			args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
	} else {
		printf("syscall exit: %s\n", sysn(scno));
	}
}

int main(int x, char *z[]) {
	pid_t child;
	int status;
	long scno = 0;
	int in_syscall = 0;
	if (x < 2) {
		fprintf(stderr, "usage: %s ./program <args>\n", z[0]);
		return 1;
	}
	child = fork();
	if (child == 0) {
		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
			perror("ptrace TRACEME");
			exit(1);
		}
		kill(getpid(), SIGSTOP);
		execvp(z[1], &z[1]);
		perror("execvp");
		exit(1);
	} else if (child > 0) {
#ifdef __arm__
		struct pt_regs_arm32 regs;
#endif
#ifdef __x86_64__
		struct pt_regs_x86_64 regs;
#endif
		if (waitpid(child, &status, 0) == -1) {
			perror("waitpid");
			return 1;
		}
		if (WIFEXITED(status)) {
			printf("child exited prematurely\n");
			return 1;
		}
		printf("child stopped, setting PTRACE options...\n");
		if (ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD) == -1) {
			perror("ptrace SETOPTIONS");
			return 1;
		}
		if (ptrace(PTRACE_SYSCALL, child, 0, 0) == -1) {
			perror("ptrace SYSCALL (start)");
			return 1;
		}
		while (1) {
			if (waitpid(child, &status, 0) == -1) {
				perror("waitpid");
				break;
			}
			if (WIFEXITED(status)) {
				printf("tracee exited with status %d\n", WEXITSTATUS(status));
				break;
			}
			if (WIFSIGNALED(status)) {
				printf("tracee killed by signal %d\n", WTERMSIG(status));
				break;
			}
			if (WIFSTOPPED(status)) {
				int sig = WSTOPSIG(status);
				printf("tracee stopped by signal %d (%s)\n", sig, sign(sig));
				if (sig == (SIGTRAP | 0x80)) {
#ifdef __arm__
					if (ptrace(PTRACE_GETREGS, child, NULL, &regs.uregs) == -1) {
						perror("ptrace GETREGS");
						break;
					}
					scno = regs.uregs[ARM_r7];
					unsigned long args[7] = {
						regs.uregs[ARM_r0], regs.uregs[ARM_r1], regs.uregs[ARM_r2], regs.uregs[ARM_r3],
						regs.uregs[ARM_r4], regs.uregs[ARM_r5], regs.uregs[ARM_r6]
					};
#endif
#ifdef __x86_64__
					if (ptrace(PTRACE_GETREGS, child, NULL, &regs) == -1) {
						perror("ptrace GETREGS");
						break;
					}
					scno = regs.orig_rax;
					unsigned long args[7] = {
						regs.rdi, regs.rsi, regs.rdx, regs.rcx,
						regs.r8, regs.r9, 0
					};
#endif
					if (!in_syscall) {
						printf("==> syscall enter:\n");
						p(scno, args, 1);
						in_syscall = 1;
					} else {
						long retval;
#ifdef __arm__
						retval = regs.uregs[ARM_r0];
#endif
#ifdef __x86_64__
						retval = regs.rax;
#endif
						printf("==> syscall exit:\n");
						p(scno, args, 0);
						printf("	return value = %ld\n", retval);
						in_syscall = 0;
					}
				} else {
					printf("non syscall signal, delivering to tracee\n");
					if (ptrace(PTRACE_SYSCALL, child, 0, sig) == -1) {
						perror("ptrace SYSCALL with signal");
						break;
					}
					continue;
				}
			}
			if (ptrace(PTRACE_SYSCALL, child, 0, 0) == -1) {
				perror("ptrace SYSCALL");
				break;
			}
		}
	} else {
		perror("fork");
		return 1;
	}
	return 0;
}
