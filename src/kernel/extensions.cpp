#include "kernel.hpp"
#include "ministl.hpp"

static map<uint16_t, module_api::kernel_extension*> *extensions;

void init_extensions(){
    extensions=new map<uint16_t, module_api::kernel_extension*>();
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