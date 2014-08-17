#include <stdlib.h>
#include "../../../../../include/btos_stubs.h"

size_t get_argc(){
	return bt_get_argc();
}

char **get_argv(){
	size_t argc=get_argc();
	char **ret=(char**)malloc(argc * sizeof(char*));
	size_t i;
	for(i=0; i<argc; ++i){
		ret[i]=(char*)malloc(128);
		size_t psize=bt_get_arg(i, ret[i], 128);
		if(psize > 128){
			free(ret[i]);
			ret[i]=(char*)malloc(psize);
			bt_get_arg(i, ret[i], psize);
		}
	}
	return ret;
}