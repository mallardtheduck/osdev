#include "kernel.hpp"
#include "strutil.hpp"

#define hasflag(x, y) (((x) & (y)) == (y))

aligned_memory al_alloc(size_t bytes, size_t align){
	aligned_memory ret;
	void *ptr=malloc(bytes+align);
	ret.alloc=ptr;
	if(align!=0){
		uint32_t pre=((uint32_t)ptr/align)*align;
		ret.aligned=(void*)(pre+align);
	}else{
		ret.aligned=ptr;
	}
	return ret;
}

void al_free(aligned_memory al){
	free(al.alloc);
}

Elf32_Ehdr elf_read_header(file_handle &file){
	Elf32_Ehdr ret;
	fs_seek(file, 0, 0);
	fs_read(file, sizeof(ret), (char*)&ret);
	return ret;
}

bool elf_verify_header(const Elf32_Ehdr &header){
	char expected[]={0x7f, 'E', 'L', 'F'};
	for(size_t i=0; i<sizeof(expected); ++i){
		if(header.ident[i]!=expected[i]){
			return false;
		}
	}
	if(header.ident[EI_CLASS] != ELFCLASS32) {
		panic("(ELF) Unsupported ELF File Class.\n");
		return false;
	}
	if(header.ident[EI_DATA] != ELFDATA2LSB) {
		panic("(ELF) Unsupported ELF File byte order.\n");
		return false;
	}
	if(header.machine != EM_386) {
		panic("(ELF) Unsupported ELF File target.\n");
		return false;
	}
	if(header.ident[EI_VERSION] != EV_CURRENT) {
		panic("(ELF) Unsupported ELF File version.\n");
		return false;
	}
	if(header.type != ET_REL && header.type != ET_EXEC) {
		panic("(ELF) Unsupported ELF File type.\n");
		return false;
	}
	return true;
}

Elf32_Shdr elf_read_sectionheader(file_handle &file, const Elf32_Ehdr &header, size_t index){
	size_t offset=header.shoff+(index*sizeof(Elf32_Shdr));
	Elf32_Shdr ret;
	fs_seek(file, offset, false);
	fs_read(file, sizeof(ret), (char*)&ret);
	return ret;
}

Elf32_Phdr elf_read_progheader(file_handle &file, const Elf32_Ehdr &header, size_t index){
	size_t offset=header.phoff+(index*sizeof(Elf32_Phdr));
	Elf32_Phdr ret;
	fs_seek(file, offset, false);
	fs_read(file, sizeof(ret), (char*)&ret);
	return ret;
}

size_t elf_get_stringoffset(file_handle &file, const Elf32_Ehdr &header){
	if(header.shstrndx == SHN_UNDEF) return 0;
	return elf_read_sectionheader(file, header, header.shstrndx).offset;
}

Elf32_Rel elf_read_rel(file_handle &file, const Elf32_Shdr &section, size_t index){
	Elf32_Rel ret;
	fs_seek(file, section.offset+(sizeof(Elf32_Rel)*index), false);
	fs_read(file, sizeof(ret), (char*)&ret);
	return ret;
}

bool elf_getstring(file_handle &file, const Elf32_Ehdr &header, size_t offset, char *buf, size_t bufsize){
	size_t strpos=elf_get_stringoffset(file, header);
	if(strpos){
		size_t readpos=strpos + offset;
		fs_seek(file, readpos, false);
		fs_read(file, bufsize, buf);
		return true;
	}else{
		return false;
	}
}

size_t elf_getsize(file_handle &file){
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

size_t elf_getbase(file_handle &file){
	size_t base=0xFFFFFF;
	Elf32_Ehdr header=elf_read_header(file);
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.vaddr<base) base=prog.vaddr;
	}
	return base;
}

Elf32_Addr elf_symbol_value(file_handle &file, const Elf32_Ehdr &header, size_t symbol){
	for(size_t i=0; i<header.shnum; ++i){
		Elf32_Shdr section=elf_read_sectionheader(file, header, i);
		if(section.type==SHT_SYMTAB){
			size_t offset=section.offset+(symbol * sizeof(Elf32_Sym));
			Elf32_Sym symbolentry;
			fs_seek(file, offset, false);
			fs_read(file, sizeof(symbolentry), (char*)&symbolentry);
			return symbolentry.value;
		}
	}
	return 0;
}

void elf_do_reloc_module(file_handle &file, const Elf32_Ehdr &header, Elf32_Shdr &section, void *base){
	size_t n_relocs=section.size/sizeof(Elf32_Rel);
	for(size_t i=0; i<n_relocs; ++i){
		Elf32_Rel rel=elf_read_rel(file, section, i);
		Elf32_Addr symval=elf_symbol_value(file, header, ELF32_R_SYM(rel.info));
		if(symval) symval+=(uint32_t)base;
		/*dbgpf("ELF: Reloc: offset: %x, info: %x, symbol: %i (%x), type: %i\n",
			rel.offset, rel.info, ELF32_R_SYM(rel.info), symval, ELF32_R_TYPE(rel.info));*/
		uint32_t *ref=(uint32_t*)((char*)base+rel.offset);
		uint32_t newval=-1;
		switch(ELF32_R_TYPE(rel.info)){
			case R_386_NONE:
				break;
			case R_386_32:
				newval=*ref+(size_t)base;
				//dbgpf("ELF: Value %x (originally %x) at %x\n", newval, *ref, ref);
                *ref=newval;
				break;
			case R_386_PC32:
				newval=*ref;
				//dbgpf("ELF: Value %x (originally %x) at %x\n", newval, *ref, ref);
				*ref=newval;
				break;
		}
	}
}

loaded_elf_module elf_load_module(file_handle &file){
	loaded_elf_module ret;
	Elf32_Ehdr header=elf_read_header(file);
	size_t ramsize=elf_getsize(file);
	ret.mem=al_alloc(ramsize, 4096); //TODO: Proper alignment calculation
	ret.entry=(module_entry)((char*)ret.mem.aligned+header.entry);
	memset(ret.mem.aligned, 0, ramsize);
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.type==PT_LOAD){
            //amm_mmap((char*)ret.mem.aligned+prog.vaddr, file, prog.offset, prog.filesz);
			fs_seek(file, prog.offset, false);
			fs_read(file, prog.filesz, (char*)ret.mem.aligned+prog.vaddr);
		}
	}
	for(int i=0; i<header.shnum; ++i){
		Elf32_Shdr section=elf_read_sectionheader(file, header, i);
		if(section.type==SHT_REL){
			char buf[128];
			elf_getstring(file, header, section.name, buf, 128);
			string name(buf);
			if(starts_with(name, ".rel.text") || starts_with(name, ".rel.data") || starts_with(name, ".rel.rodata")){
				elf_do_reloc_module(file, header, section, ret.mem.aligned);
			}
		}
	}
	return ret;
}

loaded_elf_proc elf_load_proc(pid_t pid, file_handle &file){
	loaded_elf_proc ret;
	pid_t oldpid=proc_current_pid;
	if(!proc_switch(pid)){
        panic("(ELF) Proccess not found during executable load!");
    }
	Elf32_Ehdr header=elf_read_header(file);
	//TODO: Better RAM allocation...
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.type==PT_LOAD){
			if(prog.vaddr < VMM_KERNELSPACE_END) panic("ELF: Attempt to load process into kernel space!");
			size_t p=fs_seek(file, prog.offset, false);
			if(p!=prog.offset){
				dbgpf("ELF: Seek failure - expected: %i, got %i.\n", (int)prog.offset, (int)p);
				panic("(ELF) Seek failed during program load!");
			}
			uint32_t base=prog.vaddr;
			uint32_t pages=(prog.memsz/VMM_PAGE_SIZE)+1;
			vmm_alloc_at(pages, base);
			memset((void*)prog.vaddr, 0, prog.memsz);
			//size_t b=fs_read(file, prog.filesz, (char*)prog.vaddr);
            amm_mmap((char*)prog.vaddr, file, p, prog.filesz);
			/*if(b!=prog.filesz){
				dbgpf("ELF: Read failure - expected: %i, got %i.\n", prog.filesz, b);
				panic("(ELF) Read failed during program load!");
			}*/
		}
	}
	ret.entry=(proc_entry)(header.entry);
	dbgpf("ELF: Entry point: %x\n", header.entry);
	proc_switch(oldpid);
	return ret;
}