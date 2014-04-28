#ifndef _SERDBG_HPP
#define _SERDBG_HPP

#include "kernel.hpp"

void init_serial();
void serial_writestring(char *str);

extern char dbgbuf[256];

#define dbgout serial_writestring
#define dbgpf(...) do{sprintf(dbgbuf, __VA_ARGS__); dbgout(dbgbuf);}while(false)

#endif
