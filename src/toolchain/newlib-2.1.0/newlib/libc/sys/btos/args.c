#include "../../../../../include/btos_stubs.h"

#define ARGS_MAX 4096
#define ARGC_MAX 512

static char argsbuffer[ARGS_MAX]={0};
static char *argsptr[ARGC_MAX]={0};

size_t get_argc(){
	return bt_get_argc();
}

char **get_argv(){
	size_t bufferused=0;
	size_t argc=get_argc();
	if(argc >  ARGC_MAX) argc=ARGC_MAX;
	size_t i;
	for(i=0; i < argc; ++i){
		if(bufferused >= ARGS_MAX) break;
		size_t psize=bt_get_arg(i, &argsbuffer[bufferused], ARGS_MAX-bufferused);
		argsptr[i]=&argsbuffer[bufferused];
		bufferused+=psize+1;
	}
	return argsptr;
}