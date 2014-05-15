#ifndef _MODULE_STUBS_H
#define _MODULE_STUBS_H

#include "module_api.h"
#include <stdint.h>

#ifndef __cplusplus
	#include <stdbool.h>
#endif

inline void panic(char *msg){
	syscall(SYS_PANIC, (void*)msg);
}
inline void *malloc(size_t bytes){
	syscall(SYS_MALLOC, (void*)bytes);
}
inline void free(void *ptr){
	syscall(SYS_FREE, ptr);
}
inline void memset(void *ptr, char value, size_t num){
	struct params{void *ptr; char value; size_t num;} p;
	p.ptr=ptr; p.value=value; p.num=num;
	syscall(SYS_MEMSET, (void*)&p);
}
inline void memcpy(void *dst, void *src, size_t size){
	struct params{void *dst; void *src; size_t size;} p;
	p.dst=dst; p.src=src; p.size=size;
	syscall(SYS_MEMCPY, (void*)&p);
}
inline void memmove(void *dst, void *src, size_t size){
	struct params{void *dst; void *src; size_t size;} p;
	p.dst=dst; p.src=src; p.size=size;
	syscall(SYS_MEMMOVE, (void*)&p);
}
inline int strcmp(char *s1, char *s2){
	struct params{char *s1; char *s2} p;
	p.s1=s1; p.s2=s2;
	return syscall(SYS_STRCMP, (void*)&p);
}
inline void strncpy(char *dst, char *src, size_t num){
	struct params{char *dst; char *src; size_t num} p;
	p.dst=dst; p.src=src; p.num=num;
	syscall(SYS_STRNCPY, (void*)&p);
}
inline void init_lock(uint64_t *lock){
	syscall(SYS_INITLOCK, (void*)lock);
}
inline void take_lock(uint64_t *lock){
	syscall(SYS_TAKELOCK, (void*)lock);
}
inline bool try_take_lock(uint64_t *lock){
	return !!syscall(SYS_TRYLOCK, (void*)lock);
}
inline void dbgout(char *msg){
	syscall(SYS_DBGOUT, (void*)msg);
}

#endif
