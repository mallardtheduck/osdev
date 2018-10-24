#include "kernel.hpp"
#include "ministl.hpp"
#include <util/asprintf.h>

static map<uint16_t, module_api::kernel_extension*> *extensions;

char *extensions_infofs(){
	char *buffer=nullptr;
	asprintf(&buffer, "# id, name\n");
	for(map<uint16_t, module_api::kernel_extension*>::iterator i=extensions->begin(); i!=extensions->end(); ++i){
		reasprintf_append(&buffer, "%i, %s\n", (int)i->first, i->second->name);
	}
	return buffer;
}

void init_extensions(){
    extensions=new map<uint16_t, module_api::kernel_extension*>();
	infofs_register("EXTENSIONS", &extensions_infofs);
}

uint16_t add_extension(module_api::kernel_extension *ext){
    uint16_t ret=1;
    while(extensions->has_key(ret)) ++ret;
    (*extensions)[ret]=ext;
    return ret;
}

module_api::kernel_extension *get_extension(uint16_t ext){
    if(extensions->has_key(ext)) return (*extensions)[ext];
    else return NULL;
}

uint16_t get_extension_id(const char *name){
    for(map<uint16_t, module_api::kernel_extension*>::iterator i=extensions->begin(); i!=extensions->end(); ++i){
        if(strcmp(i->second->name, name)==0) return i->first;
    }
    return 0;
}

void user_call_extension(uint16_t ext_id, uint16_t fn, isr_regs *regs){
    if(extensions->has_key(ext_id) && (*extensions)[ext_id]->uapi_handler){
        (*extensions)[ext_id]->uapi_handler(fn, regs);
    }else{
		dbgpf("EXT: Unknown API extension: %i (PID: %i, EIP:%x)!\n", (int)ext_id, (int)proc_current_pid, regs->eip);
        regs->eax=(uint32_t)-1;
    }
}