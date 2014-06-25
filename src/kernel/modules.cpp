#include "modules.hpp"
#include "locks.hpp"
#include "ministl.hpp"

lock mod_lock;

struct kernel_module{
	string filename;
	loaded_elf_module elf;
};

vector<kernel_module> *loaded_modules;

void init_modules(){
	init_lock(mod_lock);
	loaded_modules=new vector<kernel_module>();
}

void module_thread_start(void *p){
	((module_entry)p)(&MODULE_SYSCALL_TABLE);
}

void load_module(char *path){
	take_lock(mod_lock);
	file_handle file=fs_open(path);
	kernel_module mod;
	mod.filename=path;
	mod.elf=elf_load_module(file);
	loaded_modules->push_back(mod);
	release_lock(mod_lock);
	sch_new_thread(&module_thread_start, (void*)mod.elf.entry);
}