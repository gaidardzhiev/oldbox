#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mount.h>

#define MAX_ENTRIES 1024
#define NAME_SIZE 2048

struct mount_table {
	char mount_point[NAME_SIZE];
	char device[NAME_SIZE];
} mounts[MAX_ENTRIES];

int main(int argument_count, char **argument_values) {
	int read_only_flag;
	struct mount_table *current_mount;
	char *name_pointer;
	int mount_file;
	mount_file = open("/etc/mtab", O_RDONLY);
	read(mount_file, (char*)mounts, MAX_ENTRIES * 2 * NAME_SIZE);
	if(argument_count == 1) {
		for(current_mount = mounts; current_mount < &mounts[MAX_ENTRIES]; current_mount++)
			if(current_mount->mount_point[0]) printf("%s on %s\n", current_mount->device, current_mount->mount_point);
		exit(0);
	}
	if(argument_count < 3) {
		fprintf(stderr, "usage: mount <device> <mountpoint>\n");
		exit(1);
	}
	read_only_flag = 0;
	if(argument_count > 3) read_only_flag++;
//        if(mount(argument_values[1], argument_values[2], read_only_flag) < 0) {
	if(mount(argument_values[1], argument_values[2], "ext4", read_only_flag, NULL) < 0) {
		perror("mount");
		exit(1);
	}
	name_pointer = argument_values[1];
	while(*name_pointer++);
	name_pointer--;
	while(*--name_pointer == '/') *name_pointer = '\0';
	while(name_pointer > argument_values[1] && *--name_pointer != '/');
	if(*name_pointer == '/') name_pointer++;
	argument_values[1] = name_pointer;
	for(current_mount = mounts; current_mount < &mounts[MAX_ENTRIES]; current_mount++) {
		if(current_mount->mount_point[0] == 0) {
			for(name_pointer = current_mount->device; name_pointer < &current_mount->device[NAME_SIZE - 1];)
				if((*name_pointer++ = *argument_values[1]++) == 0) argument_values[1]--;
			for(name_pointer = current_mount->mount_point; name_pointer < &current_mount->mount_point[NAME_SIZE - 1];)
				if((*name_pointer++ = *argument_values[2]++) == 0) argument_values[2]--;
			current_mount = &mounts[MAX_ENTRIES];
			while((--current_mount)->mount_point[0] == 0);
			mount_file = creat("/etc/mtab", 0644);
			write(mount_file, (char*)mounts, (current_mount - mounts + 1) * 2 * NAME_SIZE);
			exit(0);
		}
	}
	exit(0);
}
