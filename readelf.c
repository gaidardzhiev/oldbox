#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

void elf(Elf64_Ehdr *h) {
	printf("ELF header:\n");
	printf("  magic:   %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",
	       h->e_ident[0], h->e_ident[1], h->e_ident[2], h->e_ident[3],
	       h->e_ident[4], h->e_ident[5], h->e_ident[6], h->e_ident[7],
	       h->e_ident[8], h->e_ident[9], h->e_ident[10], h->e_ident[11],
	       h->e_ident[12], h->e_ident[13], h->e_ident[14], h->e_ident[15]);
	printf("  type:                             %u\n", h->e_type);
	printf("  machine:                          %u\n", h->e_machine);
	printf("  version:                          %u\n", h->e_version);
	printf("  entry point address:              0x%lx\n", h->e_entry);
	printf("  start of program headers:         %u (bytes into file)\n", h->e_phoff);
	printf("  start of section headers:         %u (bytes into file)\n", h->e_shoff);
	printf("  flags:                            %u\n", h->e_flags);
	printf("  size of this header:              %u (bytes)\n", h->e_ehsize);
	printf("  size of program headers:           %u (bytes)\n", h->e_phentsize);
	printf("  number of program headers:         %u\n", h->e_phnum);
	printf("  size of section headers:           %u (bytes)\n", h->e_shentsize);
	printf("  number of section headers:         %u\n", h->e_shnum);
	printf("  section header string table index: %u\n", h->e_shstrndx);
}

//void psh(int fd, Elf64_Ehdr *h) {
//	Elf64_Shdr sh;
//	lseek(fd, h->e_shoff, SEEK_SET);
//	printf("\nsection headers:\n");
//	for (int i = 0; i < h->e_shnum; i++) {
//		read(fd, &sh, sizeof(sh))

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "usage: %s <ELF_file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0) {
		perror("error opening file");
		return EXIT_FAILURE;
	}
	Elf64_Ehdr h;
	read(fd, &h, sizeof(h));
	if (h.e_ident[0] != ELFMAG0 || h.e_ident[1] != ELFMAG1 ||
	    h.e_ident[2] != ELFMAG2 || h.e_ident[3] != ELFMAG3) {
		fprintf(stderr, "not a valid ELF file\n");
		close(fd);
		return EXIT_FAILURE;
	}
	elf(&h);
//	psh(fd, &header);
	close(fd);
	return EXIT_SUCCESS;
}
