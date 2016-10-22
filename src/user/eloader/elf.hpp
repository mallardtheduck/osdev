#ifndef _ELF_HPP
#define _ELF_HPP

#include <stddef.h>
#include <stdint.h>

#include <btos.h>

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
	EI_DATA		= 5, // Byte Ordera
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
	R_386_PLT32		= 4,
	R_386_COPY		= 5,
	R_386_GLOB_DATA = 6,
	R_386_JMP_SLOT	= 7,
	R_386_RELATIVE	= 8,
	R_386_GOTOFF	= 9,
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

typedef struct Elf32_Rel El32_Rel;

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


struct Elf32_Dyn{
	Elf32_Sword	tag;
   	union {
   		Elf32_Word	val;
   		Elf32_Addr	ptr;
	} un;
} __attribute__((packed));

enum Dyn_Tags{
	DT_NULL		=0,
	DT_NEEDED	=1,
	DT_PLTRELSZ	=2,
	DT_PLTGOT	=3,
	DT_HASH		=4,
	DT_STRTAB	=5,
	DT_SYMTAB	=6,
	DT_RELA		=7,
	DT_RELASZ	=8,
	DT_RELAENT	=9,
	DT_STRSZ	=10,
	DT_SYMENT	=11,
	DT_INIT		=12,
	DT_FINI		=13,
	DT_SONAME	=14,
	DT_RPATH 	=15,
	DT_SYMBOLIC	=16,
	DT_REL		=17,
	DT_RELSZ	=18,
	DT_RELENT	=19,
	DT_PLTREL	=20,
	DT_DEBUG	=21,
	DT_TEXTREL	=22,
	DT_JMPREL	=23,
	DT_ENCODING	=32,
	OLD_DT_LOOS	=0x60000000,
	DT_LOOS		=0x6000000d,
	DT_HIOS		=0x6ffff000,
	DT_VALRNGLO	=0x6ffffd00,
	DT_VALRNGHI	=0x6ffffdff,
	DT_ADDRRNGLO=0x6ffffe00,
	DT_ADDRRNGHI=0x6ffffeff,
	DT_VERSYM	=0x6ffffff0,
	DT_RELACOUNT=0x6ffffff9,
	DT_RELCOUNT	=0x6ffffffa,
	DT_FLAGS_1	=0x6ffffffb,
	DT_VERDEF	=0x6ffffffc,
	DT_VERDEFNUM=0x6ffffffd,
	DT_VERNEED	=0x6ffffffe,
	DT_VERNEEDNUM=0x6fffffff,
	OLD_DT_HIOS =0x6fffffff,
	DT_LOPROC	=0x70000000,
	DT_HIPROC	=0x7fffffff,
};

const int STN_UNDEF=0;

#define ELF32_R_SYM(i)	((i)>>8)
#define ELF32_R_TYPE(i)   ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

#define DO_386_32(S, A)	((S) + (A))
#define DO_386_PC32(S, A, P)	((S) + (A) - (P))

Elf32_Ehdr elf_read_header(bt_handle_t file);
Elf32_Shdr elf_read_sectionheader(bt_handle_t file, const Elf32_Ehdr &header, size_t index);
Elf32_Phdr elf_read_progheader(bt_handle_t file, const Elf32_Ehdr &header, size_t index);
size_t elf_get_stringoffset(bt_handle_t file, const Elf32_Ehdr &header);
Elf32_Rel elf_read_rel(bt_handle_t file, const Elf32_Shdr &section, size_t index);
bool elf_getstring(bt_handle_t file, const Elf32_Ehdr &header, size_t offset, char *buf, size_t bufsize);
size_t get_dynamic_entry_idx(Elf32_Dyn *dynamic, Elf32_Sword tag, size_t start = 0);
Elf32_Dyn* load_dynamic_section(bt_handle_t file, Elf32_Ehdr header, int phnum);
size_t elf_hash(const char *name);

#endif
