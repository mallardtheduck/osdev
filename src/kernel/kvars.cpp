#include "kernel.hpp"
#include "ministl.hpp"
#include "locks.hpp"

static map<string, string> *kvars;
static lock kvar_lock;

static char *kvars_infofs(){
	hold_lock hl(kvar_lock);
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# name, value\n");
	for(auto i = kvars->begin(); i != kvars->end(); ++i){
		sprintf(&buffer[strlen(buffer)],"\"%s\", \"%s\"\n", i->first.c_str(), i->second.c_str());
	}
    return buffer;
}

void init_kvars(){
	init_lock(kvar_lock);
	kvars = new map<string, string>;
	infofs_register("KVARS", kvars_infofs);
}

void set_kvar(const string &name, const string &value){
	hold_lock hl(kvar_lock);
	(*kvars)[name] = value;
}

string get_kvar(const string &name){
	hold_lock hl(kvar_lock);
	if(kvars->has_key(name)) return (*kvars)[name];
	else return "";
}

bool is_kvar_set(const string &name){
	hold_lock hl(kvar_lock);
	return kvars->has_key(name);
}