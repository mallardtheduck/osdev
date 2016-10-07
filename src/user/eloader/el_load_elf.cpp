#include "el_load_elf.hpp"
#include "util.hpp"
#include "el_malloc.hpp"
#include "libpath.hpp"

const size_t Kernel_Boundary = 1024*1024*1024;

void panic(const char *msg){
	bt_zero(msg);
	bt_exit(-1);
}

static size_t get_dynamic_entry_idx(Elf32_Dyn *dynamic, Elf32_Sword tag, size_t start = 0){
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

static void load_dynamic(bt_handle_t file, Elf32_Ehdr header, int phnum){
	Elf32_Dyn *dynamic = load_dynamic_section(file, header, phnum);
	size_t strtabidx = get_dynamic_entry_idx(dynamic, DT_STRTAB);
	if(strtabidx != (size_t)-1){
		char *strtaboff = (char*)dynamic[strtabidx].un.ptr;
		size_t nidx = 0;
		while(true){
			size_t neededidx = get_dynamic_entry_idx(dynamic, DT_NEEDED, nidx);
			if(neededidx != (size_t)-1 && dynamic[neededidx].tag == DT_NEEDED){
				nidx = neededidx + 1;
				Elf32_Dyn &needed = dynamic[neededidx];
				char neededpath[BT_MAX_PATH] = {0};
				strncpy(neededpath, (char*)strtaboff + needed.un.ptr, BT_MAX_PATH);
				bt_handle_t lib = open_lib(neededpath);
				if(lib){
					
				}
			}else break;
		}
	}
	free(dynamic);
}

entrypoint load_elf_proc(bt_handle_t file){
	Elf32_Ehdr header=elf_read_header(file);
	int dynsection = 0;
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.type==PT_DYNAMIC){
			dynsection = i;
		}
		if(prog.type==PT_LOAD){
			if(prog.vaddr < Kernel_Boundary) panic("ELOADER: Attempt to load process into kernel space!");
			size_t p=bt_fseek(file, prog.offset, FS_Set);
			if(p!=prog.offset){
				panic("ELOADER: Seek failed during program load!");
			}
			uint32_t base=prog.vaddr;
			uint32_t pages=(prog.memsz/Page_Size)+1;
			bt_alloc_at(pages, (void*)base);
			memset((void*)prog.vaddr, 0, prog.memsz);
			bt_mmap(file, p, (char*)prog.vaddr, prog.filesz);
		}
	}
	if(dynsection) load_dynamic(file, header, dynsection);
	return (entrypoint)(header.entry);
}