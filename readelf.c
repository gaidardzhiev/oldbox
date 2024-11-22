#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <fcntl.h>
#include <unistd.h>

void print_elf_header(Elf64_Ehdr *header) {
	printf("ELF header:\n");
	printf("  magic:   %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x\n",
	       header->e_ident[0], header->e_ident[1], header->e_ident[2], header->e_ident[3],
	       header->e_ident[4], header->e_ident[5], header->e_ident[6], header->e_ident[7],
	       header->e_ident[8], header->e_ident[9], header->e_ident[10], header->e_ident[11],
	       header->e_ident[12], header->e_ident[13], header->e_ident[14], header->e_ident[15]);
	printf("  type:                             %u\n", header->e_type);
	printf("  machine:                          %u\n", header->e_machine);
	printf("  version:                          %u\n", header->e_version);
	printf("  entry point address:              0x%lx\n", header->e_entry);
	printf("  start of program headers:         %u (bytes into file)\n", header->e_phoff);
	printf("  start of section headers:         %u (bytes into file)\n", header->e_shoff);
	printf("  flags:                            %u\n", header->e_flags);
	printf("  size of this header:              %u (bytes)\n", header->e_ehsize);
	printf("  size of program headers:           %u (bytes)\n", header->e_phentsize);
	printf("  number of program headers:         %u\n", header->e_phnum);
	printf("  size of section headers:           %u (bytes)\n", header->e_shentsize);
	printf("  number of section headers:         %u\n", header->e_shnum);
	printf("  section header string table index: %u\n", header->e_shstrndx);
}

//void print_section_headers(int fd, Elf64_Ehdr *header)
//{
//	Elf64_Shdr section_header;
//	lseek(fd, header->e_shoff, SEEK_SET);
//	printf("\nsection headers:\n");
//	for (int i = 0; i < header->e_shnum; i++) {
//		read(fd, &section_header, sizeof(section_header));
//		printf("  [%2d] %20s\n", i, section_header.sh_name);
//	}
//}

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
	Elf64_Ehdr header;
	read(fd, &header, sizeof(header));
	if (header.e_ident[0] != ELFMAG0 || header.e_ident[1] != ELFMAG1 ||
	    header.e_ident[2] != ELFMAG2 || header.e_ident[3] != ELFMAG3) {
		fprintf(stderr, "not a valid ELF file\n");
		close(fd);
		return EXIT_FAILURE;
	}
	print_elf_header(&header);
//	print_section_headers(fd, &header);
	close(fd);
	return EXIT_SUCCESS;
}
