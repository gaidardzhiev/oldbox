# A Modular `*nix` Utility Suite

Oldbox is a collection of essential `*nix` command line utilities implemented as **individual, standalone binaries**, unlike BusyBox which consolidates many utilities into a single static binary. This modular approach gives users fine grained control over installation, customization, and maintenance of each tool.

## Overview

- Each utility is compiled separately, rather than being combined into one executable.
- Designed for simplicity and minimal dependencies while preserving POSIX compatible behavior.
- Offers flexibility to install, update, or replace individual commands without rebuilding or managing symbolic links.
- Ideal for lightweight `*nix` environments or embedded systems where modularity is preferred.

## Included Utilities

```
basename.c - strip file name affixes
cp.c - copy or moves files
echo.c - print arguments
kill.c - terminate a process
ln.c - make links between files
mount.c - mount a filesystem
nice.c - execute a utility at an altered scheduling priority
printf.c - format and print data
rev.c - reverse lines characterwise
sleep.c - suspend execution for an interval
sync.c - commit filesystem caches to disk
tee.c - pipe fitting
touch.c - set modification date of a file
true.c - do nothing successfully
tty.c - print the file name of the terminal connected to stdin
umount.c - unmount filesystem
wc.c - display a count of lines words and characters in a file
yes.c - output a string repeatedly until killed
tr.c - transliterate data stream
cat.c - concatenate files and print on the stdout
shell.c - simple command-line shell
pwd.c - print the path of the current directory
ps.c - process status information
grep.c - global regular expression print
du.c - estimate file space usage
rm.c - remove files
ascii2hex.c - convert ASCII characters to their hexadecimal representation
hexdump.c - display file content in hex
false.c - do nothing unsuccessfully
replace.c - regular expression pattern locator and change executor
readelf.c - display information about ELF files
strings.c - print sequences of printable characters
ls.c - list directory contents
xoda.c - dump files in hex octal decimal or ASCII
id.c - print real and effective user and group IDs
cmp.c - compare files byte by byte
tree.c - list directories in a tree-like format
kmsg.c - print messages from the kernel ring buffer
file.c - determine file type by the magic bytes signature
magic.c - read the first 16 bytes of a file in hex and ascii for magic signature inspection
mem.c - print the memory layout of a process
test.c - evaluate conditional expressions and returns 0 if true or 1 if false
clear.c - clear the terminal screen
oldbox.c - simple command dispatcher for the utilities
```


## Motivation

- **Modularity:** Install and update only the tools you need.
- **Simplicity:** Easier to develop and maintain individual utilities.
- **No symlink or argv dispatching:** Avoid complexity found in single binary solutions
- **POSIX compatibility:** Each tool aims to behave similarly to its standard `*nix` counterpart.

## Building

```
git clone https://github.com/gaidardzhiev/oldbox
cd oldbox
./build_tooolchain.sh
make
make install
```

---

## License

This project is licensed under the GPL3 License.

---
