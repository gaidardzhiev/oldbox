CC=tcc

BINS=kill tty touch echo mount sync umount nice sleep tee wc yes rev ln cp basename true printf tr cat shell pwd ps grep du rm ascii2hex hexdump false replace readelf strings ls xoda id toolbox cmp
all: $(BINS)

$(BINS): %: %.c
	$(CC) -w -o $@ $<

clean:
	rm $(BINS)

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
