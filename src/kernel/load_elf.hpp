#ifndef _LOAD_ELF_HPP
#define _LOAD_ELF_HPP

#include "kernel.hpp"
#include "syscalls.hpp"

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

enum RtT_Types {
	R_386_NONE		= 0, // No relocation
	R_386_32		= 1, // Symbol + Offset
	R_386_PC32		= 2,  // Symbol + Offset - Section Offset
	R_386_GOT32		= 3,
	R_386_GOTPC		= 10,
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

struct Elf32_Rel {
	Elf32_Addr	offset;
	Elf32_Word	info;
} __attribute__((packed));

struct  Elf32_Rela {
	Elf32_Addr	offset;
	Elf32_Word	info;
	Elf32_Sword	addend;
} __attribute__((packed));

struct Elf32_Sym {
	Elf32_Word	name;
	Elf32_Addr	value;
	Elf32_Word	size;
	unsigned char	info;
	unsigned char	other;
	Elf32_Half	shndx;
} __attribute__((packed));

const int STN_UNDEF=0;

#define ELF32_R_SYM(i)	((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

#define DO_386_32(S, A)	((S) + (A))
#define DO_386_PC32(S, A, P)	((S) + (A) - (P))

struct aligned_memory{
	void *alloc;
	void *aligned;
};

namespace module_api{
	struct syscall_table;
};

typedef int (*module_entry)(module_api::syscall_table*, char*);

struct loaded_elf_module{
	aligned_memory mem;
	module_entry entry;
};

typedef void (*proc_entry)();

struct loaded_elf_proc{
	void *mem;
	proc_entry entry;
};


void elf_test();
size_t elf_getsize(file_handle &file);
loaded_elf_module elf_load_module(file_handle &file);
loaded_elf_proc elf_load_proc(pid_t pid, file_handle &file);

#endif
