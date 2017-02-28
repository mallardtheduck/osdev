#include <eloader/eloader.h>

uint32_t EL_LoadLibrary(const char *path){
	(void)path;
	return 0;
}

void *EL_GetSymbol(uint32_t lib, const char *symbol, size_t *size){
	(void)lib; (void)symbol; (void)size;
	return NULL;
}
void EL_CloseLibrary(uint32_t lib){
	(void)lib;
}

size_t EL_GetModuleCount(){
	return 0;
}

EL_Module EL_GetModule(size_t idx){
	(void)idx;
	EL_Module mod = {0, "", 0, 0};
	return mod;
}
