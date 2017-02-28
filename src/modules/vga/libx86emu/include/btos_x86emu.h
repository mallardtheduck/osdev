#ifndef _BTOS_X86EMU_H
#define _BTOS_X86EMU_H

#define BTOS_MODULE_NO_IO
#include <btos_module.h>

#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

void *calloc(size_t n, size_t sz);
char *strcat(char *dest, const char *src);
int abs(int i);

typedef int time_t;

time_t time(time_t *t);

#define x86emu_log(...) ((void)0)

#endif
