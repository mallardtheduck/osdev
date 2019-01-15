#include "kernel.hpp"
#include "locks.hpp"
#include "ministl.hpp"
#include <util/asprintf.h>
#include "strutil.hpp"

lock mod_lock;

struct kernel_module{
	string filename;
	string params;
	loaded_elf_module elf;
    file_handle file;
};

vector<kernel_module> *loaded_modules;

char *modules_infofs(){
	char *buffer=nullptr;
	asprintf(&buffer, "# address, path, parameters\n");
	for(size_t i=0; i<loaded_modules->size(); ++i){
		reasprintf_append(&buffer, "%p, \"%s\", \"%s\"\n", (*loaded_modules)[i].elf.mem.aligned, (*loaded_modules)[i].filename.c_str(),
			(*loaded_modules)[i].params.c_str());
	}
	return buffer;
}

void init_modules(){
	init_lock(mod_lock);
	loaded_modules=new vector<kernel_module>();
	infofs_register("MODULES", &modules_infofs);
}

/*void module_thread_start(void *p){
	((module_entry)p)(&MODULE_SYSCALL_TABLE);
}*/

void load_module(const char *path, char *params){
    take_lock_exclusive(mod_lock);
    for(auto &m : *loaded_modules){
    	if(to_upper(m.filename) == to_upper(path)){
    		dbgpf("MOD: Module '%s' already loaded!\n", path);
    		release_lock(mod_lock);
    		return;
    	}
    }
	file_handle file=fs_open(path, FS_Read);
	if(!file.valid){
		dbgpf("MOD: Could not open '%s'!\n", path);
        release_lock(mod_lock);
		return;
	}
	kernel_module mod;
	mod.filename=path;
	mod.params=(params)?params:"";
	mod.elf=elf_load_module(file);
    mod.file=file;
	loaded_modules->push_back(mod);
	release_lock(mod_lock);
	//sch_new_thread(&module_thread_start, (void*)mod.elf.entry);
	//if(!mod.elf.entry) panic("(MOD) Module has no entry point!");
	mod.elf.entry(&MODULE_SYSCALL_TABLE, params);
}