#ifndef _ELOADER_H
#define _ELOADER_H
#include <stdint.h>
#include <stddef.h>

struct EL_Module{
	uint32_t id;
	char *name;
	uintptr_t base;
	size_t limit;
};

#ifndef __cplusplus
typedef struct EL_Module EL_Module;
#define EL_DEFAULT(x)
#else
#define EL_DEFAULT(x) = x
extern "C" {
#endif

uint32_t EL_LoadLibrary(const char *path);
void *EL_GetSymbol(uint32_t lib, const char *symbol, size_t *size EL_DEFAULT(NULL));
void EL_CloseLibrary(uint32_t lib);
size_t EL_GetModuleCount();
EL_Module EL_GetModule(size_t idx);

#ifdef __cplusplus
}
#endif

#endif
