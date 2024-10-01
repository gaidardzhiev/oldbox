CC=tcc

BINS=kill tty touch echo mount sync umount nice sleep tee wc yes rev ln cp basename true printf tr cat shell
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
