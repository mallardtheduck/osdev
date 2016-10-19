#include "el_load_elf.hpp"
#include "util.hpp"
#include "el_malloc.hpp"
#include "libpath.hpp"

static void load_dynamic(bt_handle_t file, Elf32_Ehdr header, int phnum, const char *name);

const size_t Kernel_Boundary = 1024*1024*1024;

struct loaded_module{
	char *name;
	Elf32_Dyn *dynsection;
};

loaded_module *loaded_modules = NULL;
size_t loaded_module_count = 0;

Elf32_Dyn **loaded_dynamic_sections = NULL;
size_t dynamic_section_count = 0;

void panic(const char *msg){
	bt_zero(msg);
	bt_exit(-1);
}

static void add_module(const char *name, Elf32_Dyn *dynsection){
	++loaded_module_count;
	if(loaded_module_count==1){
		loaded_modules = (loaded_module*)malloc(sizeof(loaded_module));
	}else{
		loaded_modules = (loaded_module*)realloc(loaded_modules, sizeof(loaded_module) * loaded_module_count);
	}
	size_t strSize = strlen(name) + 1;
	char *newstring = (char*)malloc(strSize);
	memset(newstring, 0, strSize);
	strncpy(newstring, name, strSize);
	loaded_module &module = loaded_modules[loaded_module_count - 1];
	module.name = newstring;
	module.dynsection = dynsection;
}

static bool is_loaded(const char *name){
	for(size_t i=0; i<loaded_module_count; ++i){
		if(strcmp(name, loaded_modules[i].name) == 0) return true;
	}
	return false;
}

static size_t elf_getsize(bt_handle_t file){
	size_t limit=0;
	size_t base=0xFFFFFF;
	Elf32_Ehdr header=elf_read_header(file);
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.vaddr+prog.memsz>limit) limit=(prog.vaddr+prog.memsz);
		if(prog.vaddr<base) base=prog.vaddr;
	}
	return limit-base;
}

static void load_elf_library(bt_handle_t file, const char *name){
	Elf32_Ehdr header=elf_read_header(file);
	size_t ramsize=elf_getsize(file);
	size_t pages=ramsize/4096;
	if(pages * 4096 < ramsize) ++pages;
	void *mem=bt_alloc_pages(pages);
	memset(mem, 0, ramsize);
	int dynsection = 0;
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.type==PT_LOAD){
            bt_mmap(file, prog.offset, (char*)mem+prog.vaddr, prog.filesz);
		}
	}
	if(dynsection) load_dynamic(file, header, dynsection, name);
}

static void load_dynamic(bt_handle_t file, Elf32_Ehdr header, int phnum, const char *name){
	Elf32_Dyn *dynamic = load_dynamic_section(file, header, phnum);
	add_module(name, dynamic);
	size_t strtabidx = get_dynamic_entry_idx(dynamic, DT_STRTAB);
	if(strtabidx != (size_t)-1){
		char *strtaboff = (char*)dynamic[strtabidx].un.ptr;
		size_t nidx = 0;
		while(dynamic[nidx].tag != 0){
			Elf32_Dyn &current = dynamic[nidx];
			switch(current.tag){
				case DT_NEEDED:{
					char needed[BT_MAX_PATH] = {0};
					strncpy(needed, (char*)strtaboff + current.un.ptr, BT_MAX_PATH);
					if(!is_loaded(needed)){
						bt_handle_t lib = open_lib(needed);
						if(lib){
							load_elf_library(lib, name);
						}else{
							puts("ELOADER: Library not found: ");
							puts(needed);
							puts("\n");
						}
					}
					break;
				}
				default:
					break;			
			}
			++nidx;
		}
	}
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
	if(dynsection) load_dynamic(file, header, dynsection, "MAIN");
	return (entrypoint)(header.entry);
}