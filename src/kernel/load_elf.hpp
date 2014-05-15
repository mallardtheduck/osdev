#ifndef _LOAD_ELF_HPP
#define _LOAD_ELF_HPP

#include "kernel.hpp"

const size_t ELF_NIDENT=16;

typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Word;
typedef int32_t  Elf32_Sword;

enum Elf_Ident {
	EI_MAG0		= 0, // 0x7F
	EI_MAG1		= 1, // 'E'
	EI_MAG2		= 2, // 'L'
	EI_MAG3		= 3, // 'F'
	EI_CLASS	= 4, // Architecture (32/64)
	EI_DATA		= 5, // Byte Order
	EI_VERSION	= 6, // ELF Version
	EI_OSABI	= 7, // OS Specific
	EI_ABIVERSION	= 8, // OS Specific
	EI_PAD		= 9  // Padding
};

enum Elf_Type {
	ET_NONE		= 0, // Unkown Type
	ET_REL		= 1, // Relocatable File
	ET_EXEC		= 2  // Executable File
};

enum ShT_Types {
	SHT_NULL	= 0,   // Null section
	SHT_PROGBITS	= 1,   // Program information
	SHT_SYMTAB	= 2,   // Symbol table
	SHT_STRTAB	= 3,   // String table
	SHT_RELA	= 4,   // Relocation (w/ addend)
	SHT_NOBITS	= 8,   // Not present in file
	SHT_REL		= 9,   // Relocation (no addend)
};
 
enum ShT_Attributes {
	SHF_WRITE	= 0x01, // Writable section
	SHF_ALLOC	= 0x02  // Exists in memory
};

enum PhT_Types{
	PT_NULL		=0,
	PT_LOAD		=1,
	PT_DYNAMIC	=2,
	PT_INTERP	=3,
	PT_NOTE		=4,
	PT_SHLIB	=5,
	PT_PHDR		=6,
	PT_TLS		=7,
	PT_LOOS		=0x60000000,
	PT_HIOS		=0x6fffffff,
	PT_LOPROC	=0x70000000,
	PT_HIPROC	=0x7fffffff
};

const Elf32_Half EM_386=3;  	// x86 Machine Type
const Elf32_Word EV_CURRENT=1;  // ELF Current Version

const uint8_t ELFDATA2LSB=1;  // Little Endian
const uint8_t ELFCLASS32=1;   // 32-bit Architecture

const Elf32_Half SHN_UNDEF=0;

struct Elf32_Ehdr{
	uint8_t		ident[ELF_NIDENT];
	Elf32_Half	type;
	Elf32_Half	machine;
	Elf32_Word	version;
	Elf32_Addr	entry;
	Elf32_Off	phoff;
	Elf32_Off	shoff;
	Elf32_Word	flags;
	Elf32_Half	ehsize;
	Elf32_Half	phentsize;
	Elf32_Half	phnum;
	Elf32_Half	shentsize;
	Elf32_Half	shnum;
	Elf32_Half	shstrndx;
} __attribute__((packed));

struct  Elf32_Shdr{
	Elf32_Word	name;
	Elf32_Word	type;
	Elf32_Word	flags;
	Elf32_Addr	addr;
	Elf32_Off	offset;
	Elf32_Word	size;
	Elf32_Word	link;
	Elf32_Word	info;
	Elf32_Word	addralign;
	Elf32_Word	entsize;
} __attribute__((packed));

struct Elf32_Phdr{
	Elf32_Word		type;
	Elf32_Off		offset;
	Elf32_Addr		vaddr;
	Elf32_Addr		paddr;
	Elf32_Word		filesz;
	Elf32_Word		memsz;
	Elf32_Word		flags;
	Elf32_Word		align;
} __attribute__((packed));

struct aligned_memory{
	void *alloc;
	void *aligned;
};

typedef int (*syscall_vector)(int, void*);
typedef int (*module_entry)(syscall_vector);

struct loaded_elf{
	aligned_memory mem;
	module_entry entry;
};

void elf_test();
size_t elf_getsize(file_handle &file);
loaded_elf elf_load(file_handle &file);

#endif
