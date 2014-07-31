#ifndef _BTOS_STUBS_H
#define _BTOS_STUBS_H

#include "btos_api.h"

#ifdef __cplusplus
using namespace btos_api;
#endif

typedef _Bool bool;

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

#endif