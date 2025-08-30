CC=tcc

BINS=kill tty touch echo mount sync umount nice sleep tee wc yes rev ln cp basename true printf tr cat shell pwd ps grep du rm ascii2hex hexdump false replace readelf strings ls xoda id oldbox cmp tree kmsg file magic mem test clear lsblk
all: $(BINS)

$(BINS): %: %.c
	$(CC) -o $@ $<

clean:
	rm $(BINS)
	[ ! -f prand ] || rm prand

.SILENT: man
man:
	echo basename.c - strip file name affixes
	echo cp.c - copy or moves files
	echo echo.c - print arguments
	echo kill.c - terminate a process
	echo ln.c - make links between files
	echo mount.c - mount a filesystem
	echo nice.c - execute a utility at an altered scheduling priority
	echo printf.c - format and print data
	echo rev.c - reverse lines characterwise
	echo sleep.c - suspend execution for an interval
	echo sync.c - commit filesystem caches to disk
	echo tee.c - pipe fitting
	echo touch.c - set modification date of a file
	echo true.c - do nothing successfully
	echo tty.c - print the file name of the terminal connected to stdin
	echo umount.c - unmount filesystem
	echo wc.c - display a count of lines words and characters in a file
	echo yes.c - output a string repeatedly until killed
	echo tr.c - transliterate data stream
	echo cat.c - concatenate files and print on the stdout
	echo shell.c - simple command-line shell
	echo pwd.c - print the path of the current directory
	echo ps.c - process status information
	echo grep.c - global regular expression print
	echo du.c - estimate file space usage
	echo rm.c - remove files
	echo ascii2hex.c - convert ASCII characters to their hexadecimal representation
	echo hexdump.c - display file content in hex
	echo false.c - do nothing unsuccessfully
	echo replace.c - regular expression pattern locator and change executor
	echo readelf.c - display information about ELF files
	echo strings.c - print sequences of printable characters
	echo ls.c - list directory contents
	echo xoda.c - dump files in hex octal decimal or ASCII
	echo id.c - print real and effective user and group IDs
	echo cmp.c - compare files byte by byte
	echo tree.c - list directories in a tree-like format
	echo kmsg.c - print messages from the kernel ring buffer
	echo file.c - determine file type by the magic bytes signature
	echo magic.c - read the first 16 bytes of a file in hex and ascii for magic signature inspection
	echo mem.c - print the memory layout of a process
	echo test.c - evaluate conditional expressions and returns 0 if true or 1 if false
	echo clear.c - clear the terminal screen
	echo lsblk.c - list block devices

install:
	cp oldbox /usr/bin/oldbox
	cp oldbox.1 /usr/share/man/man1/

.SILENT: prand
prand:
	echo prand.c - produces high-quality randomness using RDRAND CPU instruction that generates entropy directly from hardware using thermal noise and other physical phenomena
	grep -q "rdrand" /proc/cpuinfo && gcc -march=native -o prand prand.c || echo no RDRAND instruction...
