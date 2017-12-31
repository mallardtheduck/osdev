#include <btos_module.h>
#include "cmdline.hpp"

cmdLine parse_cmd(const char *c){
	cmdLine cl = {nullptr, 0, nullptr};
	char* buf = (char*)malloc(BT_MAX_PATH);
	if(!buf) panic("(TERM) Allocation failed!");
	memset(buf, 0, BT_MAX_PATH);
	size_t i = 0;
	bool escape = false;
	bool quote = false;
	while(c && *c){
		if(escape) buf[i] = *c;
		else if(quote && *c != '"') buf[i] = *c;
		else if(*c == '\\') escape = true;
		else if(*c == '"') quote = !quote;
		else if((*c == ' ' && i) || i == BT_MAX_PATH - 1){
			if(!cl.cmd) cl.cmd = buf;
			else{
				char **nargv = (char**)malloc((cl.argc + 1) * sizeof(char*));
				if(!nargv) panic("(BOOT) Allocation failed!");
				memcpy(nargv, cl.argv, sizeof(char*) * cl.argc);
				nargv[cl.argc] = buf;
				if(cl.argv) free(cl.argv);
				cl.argv = nargv;
				++cl.argc;
			}
			buf = (char*)malloc(BT_MAX_PATH);
			if(!buf) panic("(BOOT) Allocation failed!");
			memset(buf, 0, BT_MAX_PATH);
			i = -1;
			escape=quote=false;
		}else{
			buf[i] = *c;
		}
		++i; ++c;
	}
	if(i){
		char **nargv = (char**)malloc((cl.argc + 1) * sizeof(char*));
		if(!nargv) panic("(BOOT) Allocation failed!");
		memcpy(nargv, cl.argv, sizeof(char*) * cl.argc);
		nargv[cl.argc] = buf;
		if(cl.argv) free(cl.argv);
		cl.argv = nargv;
		++cl.argc;
	}else{
		free(buf);
	}
	return cl;
};

void free_cmd(cmdLine c){
	if(c.cmd) free(c.cmd);
	for(size_t i = 0; i < c.argc; ++i){
		free(c.argv[i]);
	}
	if(c.argv) free(c.argv);
}