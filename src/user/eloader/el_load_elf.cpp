#include "el_load_elf.hpp"
#include "util.hpp"

const size_t Kernel_Boundary = 1024*1024*1024;
const size_t Page_Size = 4096;

void panic(const char *msg){
	bt_zero(msg);
	bt_exit(-1);
}

entrypoint load_elf_proc(bt_handle_t file){
	Elf32_Ehdr header=elf_read_header(file);
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.type==PT_LOAD){
			if(prog.vaddr < Kernel_Boundary) panic("ELOADER: Attempt to load process into kernel space!");
			size_t p=bt_fseek(file, prog.offset, FS_Set);
			if(p!=prog.offset){
				//dbgpf("ELOADER: Seek failure - expected: %i, got %i.\n", (int)prog.offset, (int)p);
				panic("ELOADER: Seek failed during program load!");
			}
			uint32_t base=prog.vaddr;
			uint32_t pages=(prog.memsz/Page_Size)+1;
			bt_alloc_at(pages, (void*)base);
			memset((void*)prog.vaddr, 0, prog.memsz);
			bt_mmap(file, p, (char*)prog.vaddr, prog.filesz);
		}
	}
	//dbgpf("ELF: Entry point: %x\n", header.entry);
	return (entrypoint)(header.entry);
}