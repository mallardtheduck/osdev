#include "elf.hpp"

#include <string>
#include <vector>
#include <unistd.h>

#define EI_NIDENT	16

static const std::string resc_section_name = "resc";

typedef uint32_t Elf32_Addr;
typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef int32_t  Elf32_Sword;
typedef uint32_t Elf32_Word;

struct Elf32_Ehdr{
    unsigned char	e_ident[EI_NIDENT];
    Elf32_Half		e_type;
    Elf32_Half		e_machine;
    Elf32_Word		e_version;
    Elf32_Addr		e_entry;
    Elf32_Off		e_phoff;
    Elf32_Off		e_shoff;
    Elf32_Word		e_flags;
    Elf32_Half		e_ehsize;
    Elf32_Half		e_phentsize;
    Elf32_Half		e_phnum;
    Elf32_Half		e_shentsize;
    Elf32_Half		e_shnum;
    Elf32_Half		e_shstrndx;
};

struct Elf32_Shdr{
    Elf32_Word		sh_name;
    Elf32_Word		sh_type;
    Elf32_Word		sh_flags;
    Elf32_Addr		sh_addr;
    Elf32_Off		sh_offset;
    Elf32_Word		sh_size;
    Elf32_Word		sh_link;
    Elf32_Word		sh_info;
    Elf32_Word		sh_addralign;
    Elf32_Word		sh_entsize;
};

static std::vector<char> read_data(int fd, Elf32_Off offset, Elf32_Word size){
	std::vector<char> ret;
	ret.resize(size);
	lseek(fd, offset, SEEK_SET);
	read(fd, (void*)ret.data(), size);
	return ret;
}

static std::vector<Elf32_Shdr> read_section_table(int fd, Elf32_Ehdr hdr){
	std::vector<Elf32_Shdr> ret;
	lseek(fd, hdr.e_shoff, SEEK_SET);
	for(size_t i = 0; i < hdr.e_shnum; ++i){
		Elf32_Shdr shdr;
		read(fd, (void*)&shdr, hdr.e_shentsize);
		ret.push_back(shdr);
	}
	return ret;
}

static std::string section_name(const Elf32_Shdr &s, const std::vector<char> &strings){
	return strings.data() + s.sh_name;
}

ElfRescInfo GetElfRescInfo(int fd){
	Elf32_Ehdr hdr;
	auto bytes = read(fd, (void*)&hdr, sizeof(hdr));
	if(bytes != sizeof(hdr)) return {};
	
	auto sections = read_section_table(fd, hdr);
	if(sections.size() > hdr.e_shstrndx){
		auto stringSec = sections[hdr.e_shstrndx];
		auto strings = read_data(fd, stringSec.sh_offset, stringSec.sh_size);
		
		for(const auto &s : sections){
			if(section_name(s, strings) == resc_section_name) return ElfRescInfo(s.sh_offset, s.sh_size);
		}
	}
	return {};
}