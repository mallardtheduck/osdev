#include "elf.hpp"

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