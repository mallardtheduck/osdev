#ifndef _MODULE_STUBS_H
#define _MODULE_STUBS_H

#include <stdint.h>
#include "module_api.h"
#include "drivers.h"

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

inline static void release_lock(uint64_t *lock){
	syscall(SYS_UNLOCK, (void*)lock);
}

inline static void dbgout(char *msg){
	syscall(SYS_DBGOUT, (void*)msg);
}

inline static void new_thread(void(*entry)(void*), void *param){
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

inline static void unblock(uint64_t id){
	syscall(SYS_UNBLOCK, (void*)&id);
}

inline static void add_device(drv_driver *driver){
	syscall(SYS_ADDDEVICE, (void*)driver);
}

inline static drv_driver *get_device(char *name){
	return (drv_driver*)syscall(SYS_GETDEVICE, (void*)name);
}

inline static drv_driver *get_first_device(){
	return (drv_driver*)syscall(SYS_FIRSTDEVICE, NULL);
}

inline static drv_driver *get_next_device(drv_driver *drv){
	return (drv_driver*)syscall(SYS_NEXTDEVICE, (void*)drv);
}

inline static void* devopen(char *name){
	return (void*)syscall(SYS_DEVOPEN, (void*)name);
}

inline static void devclose(void *handle){
	syscall(SYS_DEVCLOSE, handle);
}

inline static bool devread(void *handle, size_t bytes, char *buffer){
	struct params{void* handle; size_t bytes; char *buffer} p;
	p.handle=handle; p.bytes=bytes; p.buffer=buffer;
	return (bool)syscall(SYS_DEVREAD, (void*)&p);
}

inline static bool devwrite(void *handle, size_t bytes, char *buffer){
	struct params{void* handle; size_t bytes; char *buffer;} p;
	p.handle=handle; p.bytes=bytes; p.buffer=buffer;
	return (bool)syscall(SYS_DEVWRITE, (void*)&p);
}

inline static void devseek(void *handle, size_t pos, bool relative){
	struct params{void *handle; size_t pos; bool relative;} p;
	p.handle=handle; p.pos=pos; p.relative=relative;
	syscall(SYS_DEVSEEK, (void*)&p);
}

inline static int devioctl(void *handle, int fn, size_t bytes, char *buf){
	struct params{void *handle; int fn; size_t bytes; char *buf;} p;
	p.handle=handle; p.fn=fn; p.bytes=bytes; p.buf=buf;
	return syscall(SYS_DEVIOCTL, (void*)&p);
}

inline static int devtype(char *name){
	return syscall(SYS_DEVTYPE, (void*)name);
}

inline static char *devdesc(char *name){
	return (char*)syscall(SYS_DEVDESC, (void*)name);
}

inline static void handle_int(int intno, int_handler handler){
	struct params{int intno; int_handler handler;} p;
	p.intno=intno; p.handler=handler;
	syscall(SYS_HANDLEINT, (void*)&p);
}

inline static void handle_irq(int irqno, int_handler handler){
	struct params{int irqno; int_handler handler;} p;
	p.irqno=irqno; p.handler=handler;
	syscall(SYS_HANDLEIRQ, (void*)&p);
}

#endif
