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
	asm("int $0x80" : "=a"(ret) : "a"(fn), "b"(p1), "c"(p2), "d"(p3) : );
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

#endif