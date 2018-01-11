#include "elf.hpp"
#include "liballoc.h"

Elf32_Ehdr elf_read_header(bt_handle_t file){
	Elf32_Ehdr ret;
	bt_fseek(file, 0, FS_Set);
	bt_fread(file, sizeof(ret), (char*)&ret);
	return ret;
}

Elf32_Shdr elf_read_sectionheader(bt_handle_t file, const Elf32_Ehdr &header, size_t index){
	size_t offset=header.shoff+(index*sizeof(Elf32_Shdr));
	Elf32_Shdr ret;
	bt_fseek(file, offset, FS_Set);
	bt_fread(file, sizeof(ret), (char*)&ret);
	return ret;
}

Elf32_Phdr elf_read_progheader(bt_handle_t file, const Elf32_Ehdr &header, size_t index){
	size_t offset=header.phoff+(index*sizeof(Elf32_Phdr));
	Elf32_Phdr ret;
	bt_fseek(file, offset, FS_Set);
	bt_fread(file, sizeof(ret), (char*)&ret);
	return ret;
}

size_t elf_get_stringoffset(bt_handle_t file, const Elf32_Ehdr &header){
	if(header.shstrndx == SHN_UNDEF) return 0;
	return elf_read_sectionheader(file, header, header.shstrndx).offset;
}

Elf32_Rel elf_read_rel(bt_handle_t file, const Elf32_Shdr &section, size_t index){
	Elf32_Rel ret;
	bt_fseek(file, section.offset+(sizeof(Elf32_Rel)*index), FS_Set);
	bt_fread(file, sizeof(ret), (char*)&ret);
	return ret;
}

bool elf_getstring(bt_handle_t file, const Elf32_Ehdr &header, size_t offset, char *buf, size_t bufsize){
	size_t strpos=elf_get_stringoffset(file, header);
	if(strpos){
		size_t readpos=strpos + offset;
		bt_fseek(file, readpos, FS_Set);
		bt_fread(file, bufsize, buf);
		return true;
	}else{
		return false;
	}
}

size_t get_dynamic_entry_idx(Elf32_Dyn *dynamic, Elf32_Sword tag, size_t start){
	size_t i = start;
	while(dynamic[i].tag != 0){
		if(dynamic[i].tag == tag) return i;
		++i;
	}
	return -1;
}

Elf32_Dyn* load_dynamic_section(bt_handle_t file, Elf32_Ehdr header, int phnum){
	Elf32_Phdr prog=elf_read_progheader(file, header, phnum);
	Elf32_Dyn *dynamic = (Elf32_Dyn*)malloc(prog.filesz);
	bt_fseek(file, prog.offset, FS_Set);
	bt_fread(file, prog.filesz, (char*)dynamic);
	return dynamic;
}

Elf32_Addr elf_symbol_value(bt_handle_t file, const Elf32_Ehdr &header, size_t symbol){
	for(size_t i=0; i<header.shnum; ++i){
		Elf32_Shdr section=elf_read_sectionheader(file, header, i);
		if(section.type==SHT_SYMTAB){
			size_t offset=section.offset+(symbol * sizeof(Elf32_Sym));
			Elf32_Sym symbolentry;
			bt_fseek(file, offset, FS_Set);
			bt_fread(file, sizeof(symbolentry), (char*)&symbolentry);
			return symbolentry.value;
		}
	}
	return 0;
}

size_t elf_hash(const char *pname)
{
	const unsigned char *name = (const unsigned char*)pname;
    size_t h = 0, g;
 
        while (*name)
        {
             h = (h << 4) + *name++;
             if ((g = h & 0xf0000000))
                  h ^= g >> 24;
                   h &= ~g;
        }
        return h;
}
