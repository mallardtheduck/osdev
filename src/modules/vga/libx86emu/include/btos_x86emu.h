#ifndef _BTOS_X86EMU_H
#define _BTOS_X86EMU_H

#define BTOS_MODULE_NO_IO
#include <btos_module.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

#include "x86emu.h"

EXTERN_C_BEGIN

#define x86emu_log(x, ...) dbgpf(__VA_ARGS__)

void *calloc(size_t n, size_t sz);
char *strcat(char *dest, const char *src);
int abs(int i);

typedef int time_t;

time_t time(time_t *t);

unsigned btos_x86emu_memio_handler(x86emu_t *emu, u32 addr, u32 *val, unsigned type);
typedef void *(*map_address_fn)(uint32_t addr);
void set_map_callback(map_address_fn fn);

EXTERN_C_END

#endif
