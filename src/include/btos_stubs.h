#ifndef _BTOS_STUBS_H
#define _BTOS_STUBS_H

#include "btos_api.h"

#ifdef __cplusplus
using namespace btos_api;
#else
#include <stdbool.h>
#endif

inline static uint32_t btos_call(uint32_t fn, uint32_t p1, uint32_t p2, uint32_t p3){
	uint32_t ret=0;
	asm volatile("int $0x80" : "=a"(ret) : "a"(fn), "b"(p1), "c"(p2), "d"(p3) : );
	return ret;
}

inline static void bt_zero(const char *string){
	btos_call(0, (uint32_t)string, 0, 0);
}

inline static void *bt_alloc_pages(size_t pages){
	return (void*)btos_call(BT_ALLOC_PAGES, pages, 0, 0);
}

inline static void bt_free_pages(void *address, size_t pages){
	btos_call(BT_FREE_PAGES, (uint32_t)address, pages, 0);
}

inline static bt_lockhandle bt_create_lock(){
	return (bt_lockhandle)btos_call(BT_CREATE_LOCK, 0, 0, 0);
}

inline static void bt_lock(bt_lockhandle lock){
	btos_call(BT_LOCK, lock, 0, 0);
}

inline static bool bt_try_lock(bt_lockhandle lock){
	return (bool)btos_call(BT_TRY_LOCK, lock, 0, 0);
}

inline static void bt_unlock(bt_lockhandle lock){
	btos_call(BT_UNLOCK, lock, 0, 0);
}

inline static void bt_destroy_lock(bt_lockhandle lock){
	btos_call(BT_DESTROY_LOCK, lock, 0, 0);
}

inline static bool bt_mount(const char *name, const char *device, const char *filesystem){
	return btos_call(BT_MOUNT, (uint32_t)name, (uint32_t)device, (uint32_t)filesystem);
}

inline static bool bt_unmount(const char *name){
	return btos_call(BT_UNMOUNT, (uint32_t)name, 0, 0);
}

inline static bt_filehandle bt_fopen(const char *path, uint32_t flags){
	return btos_call(BT_FOPEN, (uint32_t)path, flags, 0);
}

inline static bool bt_fclose(bt_filehandle file){
	return btos_call(BT_FCLOSE, file, 0, 0);
}

inline static size_t bt_fwrite(bt_filehandle file, size_t bytes, const char *buffer){
	return btos_call(BT_FWRITE, file, bytes, (uint32_t)buffer);
}

inline static size_t bt_fread(bt_filehandle file, size_t bytes, char *buffer){
	return btos_call(BT_FREAD, file, bytes, (uint32_t)buffer);
}

inline static size_t bt_fioctl(bt_filehandle file, int function, size_t bytes, char *buffer){
	bt_fioctl_buffer buf = {.size=bytes, .buffer=buffer};
	return btos_call(BT_FIOCTL, file, function, (uint32_t)&buf);
}

inline static size_t bt_fseek(bt_filehandle file, size_t bytes, uint32_t flags){
	return btos_call(BT_FSEEK, file, bytes, flags);
}

inline static bt_dirhandle bt_dopen(const char *path, uint32_t flags){
	return btos_call(BT_DOPEN, (uint32_t)path, flags, 0);
}

inline static bool bt_dclose(bt_dirhandle dir){
	return btos_call(BT_DCLOSE, dir, 0, 0);
}

inline static bool bt_dwrite(bt_dirhandle dir, directory_entry entry){
	return btos_call(BT_DWRITE, dir, (uint32_t)&entry, 0);
}

inline static directory_entry bt_dread(bt_dirhandle dir){
	directory_entry ret;
	btos_call(BT_DREAD, dir, (uint32_t)&ret, 0);
	return ret;
}

inline static size_t bt_dseek(bt_dirhandle dir, size_t bytes, uint32_t flags){
	return btos_call(BT_DSEEK, dir, bytes, flags);
}

inline static directory_entry bt_stat(const char *path){
	directory_entry ret;
	btos_call(BT_STAT, (uint32_t)path, (uint32_t)&ret, 0);
	return ret;
}

inline static bool bt_load_module(const char *path, const char *params){
	return btos_call(BT_LOAD_MODULE, (uint32_t)path, (uint32_t)params, 0);
}

inline static size_t bt_getenv(const char *name, char *buffer, size_t size){
	return btos_call(BT_GETENV, (uint32_t)name, (uint32_t)buffer, size);
}

inline static bool bt_setenv(const char *name, char *value, uint32_t flags){
	return btos_call(BT_SETENV, (uint32_t)name, (uint32_t)value, flags);
}

inline static bt_pid bt_spawn(const char *path, size_t argc, char **argv){
	return btos_call(BT_SPAWN, (uint32_t)path, argc, (uint32_t)argv);
}

inline static void bt_wait(bt_pid pid){
	btos_call(BT_WAIT, pid, 0, 0);
}

inline static bool bt_kill(bt_pid pid){
	return btos_call(BT_KILL, pid, 0, 0);
}

inline static bt_priority bt_prioritize(bt_pid pid, bt_priority priority){
	return btos_call(BT_PRIORITIZE, pid, priority, 0);
}

inline static void bt_exit(int retval){
	btos_call(BT_EXIT, (uint32_t)retval, 0, 0);
}

inline static bt_pid bt_getpid(){
	return btos_call(BT_GETPID, 0, 0, 0);
}

#endif