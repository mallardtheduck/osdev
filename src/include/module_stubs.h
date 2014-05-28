#ifndef _MODULE_STUBS_H
#define _MODULE_STUBS_H

#include "module_api.h"
#include <stdint.h>

#ifndef __cplusplus
	#include <stdbool.h>
#endif

inline static void panic(char *msg){
	syscall(SYS_PANIC, (void*)msg);
}
inline static void *malloc(size_t bytes){
	return (void*)syscall(SYS_MALLOC, (void*)bytes);
}
inline static void free(void *ptr){
	syscall(SYS_FREE, ptr);
}
inline static void memset(void *ptr, char value, size_t num){
	struct params{void *ptr; char value; size_t num;} p;
	p.ptr=ptr; p.value=value; p.num=num;
	syscall(SYS_MEMSET, (void*)&p);
}
inline static void memcpy(void *dst, void *src, size_t size){
	struct params{void *dst; void *src; size_t size;} p;
	p.dst=dst; p.src=src; p.size=size;
	syscall(SYS_MEMCPY, (void*)&p);
}
inline static void memmove(void *dst, void *src, size_t size){
	struct params{void *dst; void *src; size_t size;} p;
	p.dst=dst; p.src=src; p.size=size;
	syscall(SYS_MEMMOVE, (void*)&p);
}
inline static int strcmp(char *s1, char *s2){
	struct params{char *s1; char *s2;} p;
	p.s1=s1; p.s2=s2;
	return syscall(SYS_STRCMP, (void*)&p);
}
inline static void strncpy(char *dst, char *src, size_t num){
	struct params{char *dst; char *src; size_t num;} p;
	p.dst=dst; p.src=src; p.num=num;
	syscall(SYS_STRNCPY, (void*)&p);
}
inline static void init_lock(uint64_t *lock){
	syscall(SYS_INITLOCK, (void*)lock);
}
inline static void take_lock(uint64_t *lock){
	syscall(SYS_TAKELOCK, (void*)lock);
}
inline static bool try_take_lock(uint64_t *lock){
	return !!syscall(SYS_TRYLOCK, (void*)lock);
}
inline static void dbgout(char *msg){
	syscall(SYS_DBGOUT, (void*)msg);
}

inline static void newthread(void(*entry)(void*), void *param){
	struct params{void(*entry)(void*); void *param;} p;
	p.entry=entry; p.param=param;
	syscall(SYS_NEWTHREAD, (void*)&p);
}

inline static void block(){
	syscall(SYS_BLOCK, NULL);
}

inline static void yield(){
	syscall(SYS_YIELD, NULL);
}

inline static uint64_t thread_id(){
	return *(uint64_t*)syscall(SYS_THREADID, NULL);
}

inline static void thread_priority(uint32_t p){
	syscall(SYS_PRIORITY, (void*)p);
}

inline static void end_thread(){
	syscall(SYS_ENDTHREAD, NULL);
}

inline static void unblock(uint32_t id){
	syscall(SYS_UNBLOCK, (void*)id);
}

#endif
