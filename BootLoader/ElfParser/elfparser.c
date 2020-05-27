#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"

#define FILENAME  "task1.elf"

typedef struct
{
    uint_8t       ident[16];
	uint_16t      e_type;
	uint_16t      e_machine;
    uint_32t      e_version;
    uint_32t      e_entry;
    uint_32t      e_phoff;
    uint_32t      e_shoff;
    uint_32t      e_flags;
    uint_16t      e_ehsize;
    uint_16t      e_phentsize;
    uint_16t      e_phnum;
    uint_16t      e_shentsize;
    uint_16t      e_shnum;
    uint_16t      e_shstrndx;
 }ElfN_Ehdr;
typedef struct 
{
    uint_32t     p_type;
    uint_32t     p_offset;
    uint_32t     p_vaddr;
    uint_32t     p_paddr;
    uint_32t     p_filesz;
    uint_32t     p_memsz;
    uint_32t     p_flags;
    uint_32t     p_align;
} Elf32_Phdr;

int main(void)
{
	uint_8t buffer[1024*1024];
	void *FP = fopen(FILENAME,"rb");
	fseek(FP,0,SEEK_END);
	uint_32t size=ftell(FP);
	fseek(FP,0,SEEK_SET);
	fread(buffer,sizeof(uint_8t),size,FP);
	fclose (FP);
	
	ElfN_Ehdr  *header=(ElfN_Ehdr *)buffer;
	Elf32_Phdr *section_1=(Elf32_Phdr *)&buffer[header->e_phoff];
	Elf32_Phdr *section_2=(Elf32_Phdr *)&buffer[header->e_phoff+header->e_phentsize];
	Elf32_Phdr *section_3=(Elf32_Phdr *)&buffer[header->e_phoff+(2*header->e_phentsize)];
	printf("%x",buffer[section_1->p_offset]);

}
