#include "el_load_elf.hpp"
#include "libpath.hpp"
#include <eloader/eloader.h>

using namespace btos_api;

static loaded_module *getmodule(uint32_t id){
	for(size_t i = 0; i < loaded_module_count; ++i){
		if(loaded_modules[i].id == id) return &loaded_modules[i];
	}
	return NULL;
}

uint32_t EL_LoadLibrary(const char *path){
	char *full_path = NULL;
	bt_handle_t lib = open_lib(path, &full_path);
	uint32_t ret = 0;
	if(lib) ret = load_elf_library(lib, path, full_path, true);
	return ret;
}

void *EL_GetSymbol(uint32_t lib, const char *symbol, size_t *size){
	loaded_module *mod = getmodule(lib);
	if(!mod && lib != 0) return NULL;
	if(!mod && lib == 0) mod = getmodule(1);
	intptr_t addr = get_symbol_by_name(*mod, symbol, size);
	if(lib != 0 && (addr < mod->base || (size_t)addr > mod->base + mod->limit)) return NULL;
	return (void*)addr;
}


void EL_CloseLibrary(uint32_t lib){
	(void)lib;
}

size_t EL_GetModuleCount(){
	return loaded_module_count;
}

EL_Module EL_GetModule(size_t idx){
	EL_Module ret = {0, (char*)"", 0, 0};
	if(idx < loaded_module_count){
		loaded_module *mod = &loaded_modules[idx];
		ret.id = mod->id;
		ret.name = mod->name;
		ret.base = mod->base;
		ret.limit = mod->limit;
	}
	return ret;
}

void init_api(){
	add_symbol_override("EL_LoadLibrary", (intptr_t)&EL_LoadLibrary);
	add_symbol_override("EL_GetSymbol", (intptr_t)&EL_GetSymbol);
	add_symbol_override("EL_CloseLibrary", (intptr_t)&EL_CloseLibrary);
	add_symbol_override("EL_GetModuleCount", (intptr_t)&EL_GetModuleCount);
	add_symbol_override("EL_GetModule", (intptr_t)&EL_GetModule);
}
