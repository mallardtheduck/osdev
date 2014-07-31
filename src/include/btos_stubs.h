#ifndef _BTOS_STUBS_H
#define _BTOS_STUBS_H

#include "btos_api.h"

inline static uint32_t btos_call(uint32_t fn, uint32_t p1, uint32_t p2, uint32_t p3){
	uint32_t ret=0;
	asm("int $0x80" : "=a"(ret) : "a"(fn), "b"(p1), "c"(p2), "d"(p3) : );
	return ret;
}

#endif