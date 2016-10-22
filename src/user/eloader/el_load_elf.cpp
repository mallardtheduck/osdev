#include "el_load_elf.hpp"
#include "util.hpp"
#include "el_malloc.hpp"
#include "libpath.hpp"

static void load_dynamic(bt_handle_t file, Elf32_Ehdr header, int phnum, const char *name, intptr_t base);

const size_t Kernel_Boundary = 1024*1024*1024;

struct loaded_module{
	char *name;
	Elf32_Dyn *dynamic;
	intptr_t base;
};

loaded_module *loaded_modules = NULL;
size_t loaded_module_count = 0;

void panic(const char *msg){
	bt_zero(msg);
	bt_exit(-1);
}

static void add_module(const char *name, Elf32_Dyn *dynsection, intptr_t base){
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
	module.dynamic = dynsection;
	module.base = base;
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
		if(prog.type==PT_DYNAMIC){
			dynsection = i;
		}
		if(prog.type==PT_LOAD){
            bt_mmap(file, prog.offset, (char*)mem+prog.vaddr, prog.filesz);
		}
	}
	if(dynsection) load_dynamic(file, header, dynsection, name, (intptr_t)mem);
}

static void load_dynamic(bt_handle_t file, Elf32_Ehdr header, int phnum, const char *name, intptr_t base){
	Elf32_Dyn *dynamic = load_dynamic_section(file, header, phnum);
	add_module(name, dynamic, base);
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
							load_elf_library(lib, needed);
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

static Elf32_Sym hash_lookup(const char *symbol, const loaded_module &module){
	size_t hashtbl_idx = get_dynamic_entry_idx(module.dynamic, DT_HASH);
	uint32_t *hashtbl = (uint32_t*)(module.dynamic[hashtbl_idx].un.ptr + module.base);
	size_t bucket_count = hashtbl[0];
	size_t chain_count = hashtbl[1];
	uint32_t *bucket_table = &hashtbl[2];
	uint32_t *chain_table = &bucket_table[bucket_count];
	size_t symtab_idx = get_dynamic_entry_idx(module.dynamic, DT_SYMTAB);
	Elf32_Sym *symtab = (Elf32_Sym*)(module.base + module.dynamic[symtab_idx].un.ptr);
	size_t strtab_idx = get_dynamic_entry_idx(module.dynamic, DT_STRTAB);
	char *strtab = (char*)(module.base + module.dynamic[strtab_idx].un.ptr);
	size_t symhash = elf_hash(symbol);
	size_t bucket_idx = (symhash % bucket_count);
	size_t chain_idx = bucket_table[bucket_idx];
	while(chain_idx < chain_count){
		Elf32_Sym symbol_entry = symtab[chain_idx];
		char *symname = strtab + symbol_entry.name;
		if(strcmp(symbol, symname)==0){
			if(symbol_entry.shndx != SHN_UNDEF){
				return symbol_entry;
			}else{
				Elf32_Sym ret;
				ret.shndx = SHN_UNDEF;
				return ret;
			}
		}
		chain_idx = chain_table[chain_idx];
	}
	Elf32_Sym ret;
	ret.shndx = SHN_UNDEF;
	return ret;
}

static intptr_t get_symbol(const loaded_module &module, size_t symbol, size_t *sym_size=NULL){
	puts("get_symbol\n");
	size_t symtab_idx = get_dynamic_entry_idx(module.dynamic, DT_SYMTAB);
	Elf32_Sym *symtab = (Elf32_Sym*)(module.base + module.dynamic[symtab_idx].un.ptr);
	size_t strtab_idx = get_dynamic_entry_idx(module.dynamic, DT_STRTAB);
	char *strtab = (char*)(module.base + module.dynamic[strtab_idx].un.ptr);
	char *symname = strtab + symtab[symbol].name;
	puts(symname);
	puts("\n");
	for(size_t i=0; i<loaded_module_count; ++i){
		loaded_module &cmod = loaded_modules[i];
		Elf32_Sym entry = hash_lookup(symname, cmod);
		if(entry.shndx != SHN_UNDEF) {
			if(sym_size) *sym_size = entry.size;
			return (entry.value + cmod.base);
		}
	}
	return 0;
}

static void relocate_module_rel(const loaded_module &module, Elf32_Addr ptr, size_t sz){
	puts("relocate_module_rel\n");
	Elf32_Rel *relptr = (Elf32_Rel*)(module.base + ptr);
	size_t len = sz / sizeof(Elf32_Rel);
	for(size_t i = 0; i < len; ++i){
		Elf32_Rel &rel = relptr[i];
		uint32_t *ref=(uint32_t*)(module.base+rel.offset);
		switch(ELF32_R_TYPE(rel.info)){
			case R_386_NONE: break;
			case R_386_32:{
				intptr_t symbol = get_symbol(module, ELF32_R_SYM(rel.info));
				uint32_t val = symbol + *ref;
				*ref = val;
				break;
			}
			case R_386_PC32:{
				intptr_t symbol = get_symbol(module, ELF32_R_SYM(rel.info));
				uint32_t val = symbol + *ref - module.base;
				*ref = val;
				break;
			}
			case R_386_COPY:{
				size_t sym_size = 0;
				void *addr = (void*)get_symbol(module, ELF32_R_SYM(rel.info), &sym_size);
				memcpy(ref, addr, sym_size);
				break;
			}
			case R_386_GLOB_DATA:
			case R_386_JMP_SLOT:{
				*ref = get_symbol(module, ELF32_R_SYM(rel.info));
				break;
			}
			case R_386_RELATIVE:{
				*ref += module.base;
				break;
			}
			default:
				puts("Unsupported relocation!\n");
		}
	}
}

static void relocate_module_rela(const loaded_module &module, Elf32_Addr ptr, size_t sz){
	puts("relocate_module_rela\n");
	Elf32_Rela *relptr = (Elf32_Rela*)(module.base + ptr);
	size_t len = sz / sizeof(Elf32_Rela);
	for(size_t i = 0; i < len; ++i){
		Elf32_Rela &rela = relptr[i];
		uint32_t *ref=(uint32_t*)(module.base+rela.offset);
		switch(ELF32_R_TYPE(rela.info)){
			case R_386_NONE: break;
			case R_386_32:{
				intptr_t symbol = get_symbol(module, ELF32_R_SYM(rela.info));
				uint32_t val = symbol + rela.addend;
				*ref = val;
				break;
			}
			case R_386_PC32:{
				intptr_t symbol = get_symbol(module, ELF32_R_SYM(rela.info));
				uint32_t val = symbol + rela.addend - module.base;
				*ref = val;
				break;
			}
			case R_386_COPY:{
				*ref = *(uint32_t*)get_symbol(module, ELF32_R_SYM(rela.info));
				break;
			}
			case R_386_GLOB_DATA:
			case R_386_JMP_SLOT:{
				*ref = get_symbol(module, ELF32_R_SYM(rela.info));
				break;
			}
			case R_386_RELATIVE:{
				*ref = module.base + rela.addend;
				break;
			}
			default:
				puts("Unsupported relocation!\n");
		}
		if(ELF32_R_TYPE(rela.info) == R_386_NONE) break;
		++i;
	}
}

void dynamic_link(){
	puts("dynamic_link\n");
	for(size_t i=0; i<loaded_module_count; ++i){
		loaded_module &module = loaded_modules[i];
		puts("Module: ");
		puts(module.name);
		puts("\n");
		Elf32_Dyn *&dynamic = module.dynamic;
		size_t idx=0;
		while(dynamic[idx].tag != 0){
			Elf32_Dyn &current = dynamic[idx];
			switch(current.tag){
				case DT_REL:{
					size_t rel_sz_idx = get_dynamic_entry_idx(dynamic, DT_RELSZ);
					size_t rel_sz = dynamic[rel_sz_idx].un.val;
					relocate_module_rel(module, current.un.ptr, rel_sz);
					break;
				}
				case DT_RELA:{
					size_t rela_sz_idx = get_dynamic_entry_idx(dynamic, DT_RELASZ);
					size_t rela_sz = dynamic[rela_sz_idx].un.val;
					relocate_module_rela(module, current.un.ptr, rela_sz);
					break;
				}
				case DT_JMPREL:{
					size_t jmprel_sz_idx = get_dynamic_entry_idx(dynamic, DT_PLTRELSZ);
					size_t jmprel_type_idx = get_dynamic_entry_idx(dynamic, DT_PLTREL);
					size_t jmprel_sz = dynamic[jmprel_sz_idx].un.val;
					size_t jmprel_type = dynamic[jmprel_type_idx].un.val;
					if(jmprel_type == DT_REL) relocate_module_rel(module, current.un.ptr, jmprel_sz);
					else if(jmprel_type == DT_RELA) relocate_module_rela(module, current.un.ptr, jmprel_sz);
				}
			}
			++idx;
		}
	}
	puts("dynamic_link done\n");
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
	if(dynsection) {
		load_dynamic(file, header, dynsection, "MAIN", 0);
		dynamic_link();
	}
	return (entrypoint)(header.entry);
}