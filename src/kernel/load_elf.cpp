#include "kernel.hpp"
#include "elf_format.hpp"

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

Elf32_Ehdr elf_read_header(IFileHandle &file){
	Elf32_Ehdr ret;
	file.Seek(0, FS_Set);
	file.Read(sizeof(ret), (char*)&ret);
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

Elf32_Shdr elf_read_sectionheader(IFileHandle &file, const Elf32_Ehdr &header, size_t index){
	size_t offset=header.shoff+(index*sizeof(Elf32_Shdr));
	Elf32_Shdr ret;
	file.Seek(offset, FS_Set);
	file.Read(sizeof(ret), (char*)&ret);
	return ret;
}

Elf32_Phdr elf_read_progheader(IFileHandle &file, const Elf32_Ehdr &header, size_t index){
	size_t offset=header.phoff+(index*sizeof(Elf32_Phdr));
	Elf32_Phdr ret;
	file.Seek(offset, FS_Set);
	file.Read(sizeof(ret), (char*)&ret);
	return ret;
}

size_t elf_get_stringoffset(IFileHandle &file, const Elf32_Ehdr &header){
	if(header.shstrndx == SHN_UNDEF) return 0;
	return elf_read_sectionheader(file, header, header.shstrndx).offset;
}

Elf32_Rel elf_read_rel(IFileHandle &file, const Elf32_Shdr &section, size_t index){
	Elf32_Rel ret;
	file.Seek(section.offset+(sizeof(Elf32_Rel)*index), FS_Set);
	file.Read(sizeof(ret), (char*)&ret);
	return ret;
}

bool elf_getstring(IFileHandle &file, const Elf32_Ehdr &header, size_t offset, char *buf, size_t bufsize){
	size_t strpos=elf_get_stringoffset(file, header);
	if(strpos){
		size_t readpos=strpos + offset;
		file.Seek(readpos, FS_Set);
		file.Read(bufsize, buf);
		return true;
	}else{
		return false;
	}
}

size_t elf_getsize(IFileHandle &file){
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

size_t elf_getbase(IFileHandle &file){
	size_t base=0xFFFFFF;
	Elf32_Ehdr header=elf_read_header(file);
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.vaddr<base) base=prog.vaddr;
	}
	return base;
}

void elf_do_reloc_module(IFileHandle &file, const Elf32_Ehdr &header, Elf32_Shdr &section, void *base){
	size_t n_relocs=section.size/sizeof(Elf32_Rel);
	for(size_t i=0; i<n_relocs; ++i){
		Elf32_Rel rel=elf_read_rel(file, section, i);
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

loaded_elf_module elf_load_module(IFileHandle &file){
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
			file.Seek(prog.offset, FS_Set);
			file.Read(prog.filesz, (char*)ret.mem.aligned+prog.vaddr);
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

loaded_elf_proc elf_load_proc(bt_pid_t pid, IFileHandle &file){
	loaded_elf_proc ret;
	bt_pid_t oldpid=CurrentProcess().ID();
	if(!GetProcessManager().SwitchProcess(pid)){
        panic("(ELF) Proccess not found during executable load!");
    }
	Elf32_Ehdr header=elf_read_header(file);
	//TODO: Better RAM allocation...
	for(int i=0; i<header.phnum; ++i){
		Elf32_Phdr prog=elf_read_progheader(file, header, i);
		if(prog.type==PT_LOAD){
			if(prog.vaddr < MM2::MM2_Kernel_Boundary) panic("ELF: Attempt to load process into kernel space!");
			size_t p=file.Seek(prog.offset, FS_Set);
			if(p!=prog.offset){
				dbgpf("ELF: Seek failure - expected: %i, got %i.\n", (int)prog.offset, (int)p);
				panic("(ELF) Seek failed during program load!");
			}
			uint32_t base=prog.vaddr;
			uint32_t pages=(prog.memsz/MM2::MM2_Page_Size)+1;
			MM2::current_pagedir->alloc_pages_at(pages, (void*)base);
			memset((void*)prog.vaddr, 0, prog.memsz);
			//size_t b=file.Read(prog.filesz, (char*)prog.vaddr);
            MM2::mm2_mmap((char*)prog.vaddr, file, p, prog.filesz);
			/*if(b!=prog.filesz){
				dbgpf("ELF: Read failure - expected: %i, got %i.\n", (int)prog.filesz, (int)b);
				panic("(ELF) Read failed during program load!");
			}*/
		}
	}
	ret.entry=(proc_entry)(header.entry);
	dbgpf("ELF: Entry point: %lx\n", header.entry);
	if(!GetProcessManager().SwitchProcess(oldpid)){
		panic("(LOAD) Process swtich failed!");
	}
	return ret;
}

class ElfModule : public ILoadedElf{
private:
	loaded_elf_module mod;
public:
	ElfModule(IFileHandle &file) : mod(elf_load_module(file)) {}

	void Execute(const char *mod_params = nullptr) override{
		mod.entry(nullptr /*SYSCALL_TABLE*/, (char*)mod_params);
	};

	ProcessEntryPoint GetEntryPoint(){
		return nullptr;
	}

	~ElfModule(){
		al_free(mod.mem);
	}
};

ILoadedElf *LoadElfModule(IFileHandle &file){
	return new ElfModule(file);
}

class ElfProcess : public ILoadedElf{
private:
	loaded_elf_proc proc;
public:
	ElfProcess(bt_pid_t pid, IFileHandle &file) : proc(elf_load_proc(pid, file)) {}

	void Execute(const char */*mod_params*/ = nullptr) override{
		//Do nothing
	};

	ProcessEntryPoint GetEntryPoint() override{
		return (ProcessEntryPoint)proc.entry;
	}
};


ILoadedElf *LoadElfProcess(bt_pid_t pid, IFileHandle &file){
	return new ElfProcess(pid, file);
}