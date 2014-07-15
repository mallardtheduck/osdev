#ifndef _MODULE_STUBS_H
#define _MODULE_STUBS_H

#include <stdint.h>
#include <stdarg.h>
#include "module_api.h"

#ifndef __cplusplus
	#include <stdbool.h>
#else
	#pragma GCC diagnostic ignored "-Wwrite-strings"
#endif

extern char dbgbuf[256];
#define dbgpf(...) do{sprintf(dbgbuf, __VA_ARGS__); dbgout(dbgbuf);}while(false)
#define sprintf(buf, string, ...) SYSCALL_TABLE->sprintf(buf, string, __VA_ARGS__)

inline static void panic(char *msg){
	SYSCALL_TABLE->panic(msg);
}
inline static void *malloc(size_t bytes){
	return SYSCALL_TABLE->malloc(bytes);
}
inline static void free(void *ptr){
	SYSCALL_TABLE->free(ptr);
}
inline static void *memset(void *ptr, int value, size_t num){
	return SYSCALL_TABLE->memset(ptr, value, num);
}
inline static void memcpy(void *dst, void *src, size_t size){
	SYSCALL_TABLE->memcpy(dst, src, size);
}
inline static void memmove(void *dst, void *src, size_t size){
	SYSCALL_TABLE->memmove(dst, src, size);
}
inline static int strcmp(const char *s1, const char *s2){
	return SYSCALL_TABLE->strcmp((char*)s1, (char*)s2);
}
inline static void strncpy(char *dst, const char *src, size_t num){
	SYSCALL_TABLE->strncpy(dst, (char*)src, num);
}
inline static void init_lock(lock *l){
	SYSCALL_TABLE->init_lock(l);
}
inline static void take_lock(lock *l){
	SYSCALL_TABLE->take_lock(l);
}
inline static bool try_take_lock(lock *l){
	return SYSCALL_TABLE->try_take_lock(l);
}

inline static void release_lock(lock *l){
	SYSCALL_TABLE->release_lock(l);
}

inline static void dbgout(char *msg){
	SYSCALL_TABLE->dbgout(msg);
}

inline static void new_thread(thread_func entry, void *param){
	SYSCALL_TABLE->new_thread(entry, param);
}

inline static void block(){
	SYSCALL_TABLE->block();
}

inline static void yield(){
	SYSCALL_TABLE->yield();
}

inline static uint64_t thread_id(){
	return SYSCALL_TABLE->thread_id();
}

inline static void thread_priority(uint32_t p){
	SYSCALL_TABLE->thread_priority(p);
}

inline static void end_thread(){
	SYSCALL_TABLE->end_thread();
}

inline static void unblock(uint64_t id){
	SYSCALL_TABLE->unblock(id);
}

inline static void add_device(char *name, drv_driver *driver){
	SYSCALL_TABLE->add_device(name, driver);
}

inline static drv_driver *get_device(char *name){
	return SYSCALL_TABLE->get_device(name);
}

inline static void *get_first_device(char **name){
	return SYSCALL_TABLE->get_first_device(name);
}

inline static void *get_next_device(void *itr, char **name){
	return SYSCALL_TABLE->get_next_device(itr, name);
}

inline static void* devopen(char *name){
	return SYSCALL_TABLE->devopen(name);
}

inline static bool devclose(void *handle){
	return SYSCALL_TABLE->devclose(handle);
}

inline static bool devread(void *handle, size_t bytes, char *buffer){
	return SYSCALL_TABLE->devread(handle, bytes, buffer);
}

inline static bool devwrite(void *handle, size_t bytes, char *buffer){
	return SYSCALL_TABLE->devwrite(handle, bytes, buffer);
}

inline static void devseek(void *handle, size_t pos, bool relative){
	SYSCALL_TABLE->devseek(handle, pos, relative);
}

inline static int devioctl(void *handle, int fn, size_t bytes, char *buf){
	return SYSCALL_TABLE->devioctl(handle, fn, bytes, buf);
}

inline static int devtype(char *name){
	return SYSCALL_TABLE->devtype(name);
}

inline static char *devdesc(char *name){
	return SYSCALL_TABLE->devdesc(name);
}

inline static void handle_int(int intno, int_handler handler){
	SYSCALL_TABLE->handle_int(intno, handler);
}

inline static void handle_irq(int irqno, int_handler handler){
	SYSCALL_TABLE->handle_irq(irqno, handler);
}

inline static void add_filesystem(fs_driver *fs){
	SYSCALL_TABLE->add_filesystem(fs);
}

inline static bool mount(char *name, char *device, char *fs){
	return SYSCALL_TABLE->mount(name, device, fs);
}

inline static bool unmount(char *name){
	return SYSCALL_TABLE->unmount(name);
}

inline static file_handle *fopen(char *path){
	return SYSCALL_TABLE->fopen(path);
}

inline static bool fclose(file_handle *handle){
	return SYSCALL_TABLE->fclose(handle);
}

inline static int fread(file_handle *handle, size_t bytes, char *buf){
	return SYSCALL_TABLE->fread(handle, bytes, buf);
}

inline static bool fwrite(file_handle *handle, size_t bytes, char *buf){
	return SYSCALL_TABLE->fwrite(handle, bytes, buf);
}

inline static bool fseek(file_handle *handle, size_t pos, bool relative){
	return SYSCALL_TABLE->fseek(handle, pos, relative);
}

inline static int fioctl(file_handle *handle, int fn, size_t bytes, char *buf){
	return SYSCALL_TABLE->fioctl(handle, fn, bytes, buf);
}

inline static file_handle *fcreate(char *path){
	return SYSCALL_TABLE->fcreate(path);
}

inline static dir_handle *diropen(char *path){
	return SYSCALL_TABLE->diropen(path);
}

inline static bool dirclose(dir_handle *handle){
	return SYSCALL_TABLE->dirclose(handle);
}

inline static directory_entry dirread(dir_handle *handle){
	return SYSCALL_TABLE->dirread(handle);
}

inline static bool dirwrite(dir_handle *handle, directory_entry entry){
	return SYSCALL_TABLE->dirwrite(handle, entry);
}

inline static bool dirseek(dir_handle *handle, size_t pos, bool relative){
	return SYSCALL_TABLE->dirseek(handle, pos, relative);
}

inline static dir_handle *dircreate(char *path){
	return SYSCALL_TABLE->dircreate(path);
}

inline static directory_entry stat(char *path){
	return SYSCALL_TABLE->stat(path);
}

inline static void module_load(char *path){
	SYSCALL_TABLE->module_load(path);
}

inline static void setenv(char *name, char *value, uint8_t flags, pid_t pid){
	SYSCALL_TABLE->setenv(name, value, flags, pid);
}

inline static char *getenv(char *name, pid_t pid){
	return SYSCALL_TABLE->getenv(name, pid);
}

#endif
