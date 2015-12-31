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

extern syscall_table *SYSCALL_TABLE;
extern char dbgbuf[256];

#define USE_SYSCALL_TABLE syscall_table *SYSCALL_TABLE
#define USE_DEBUG_PRINTF char dbgbuf[256]

#define dbgpf(...) do{sprintf(dbgbuf, __VA_ARGS__); dbgout(dbgbuf);}while(false)
#define sprintf(...) SYSCALL_TABLE->sprintf(__VA_ARGS__)

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

inline static uint32_t physaddr(void *ptr){
    return SYSCALL_TABLE->physaddr(ptr);
}

inline static void init_lock(lock *l){
	SYSCALL_TABLE->init_lock(l);
}
inline static void take_lock(lock *l){
	SYSCALL_TABLE->take_lock(l);
}

inline static void take_lock_recursive(lock *l){
    SYSCALL_TABLE->take_lock_recursive(l);
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

inline static thread_id_t new_thread(thread_func entry, void *param){
	return SYSCALL_TABLE->new_thread(entry, param);
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

inline static void thread_wait(uint64_t id){
	SYSCALL_TABLE->thread_wait(id);
}

inline static void thread_setblock(bool(*blockcheck)(void*), void *param){
	SYSCALL_TABLE->thread_setblock(blockcheck, param);
}

inline static void thread_abortable(bool abortable){
	SYSCALL_TABLE->thread_abortable(abortable);
}

inline static void thread_abort(thread_id_t id){
	SYSCALL_TABLE->thread_abort(id);
}

inline static void add_device(char *name, drv_driver *driver, void *id){
	SYSCALL_TABLE->add_device(name, driver, id);
}

inline static drv_device *get_device(const char *name){
	return SYSCALL_TABLE->get_device(name);
}

inline static void *get_first_device(char **name){
	return SYSCALL_TABLE->get_first_device(name);
}

inline static void *get_next_device(void *itr, char **name){
	return SYSCALL_TABLE->get_next_device(itr, name);
}

inline static void* devopen(const char *name){
	return SYSCALL_TABLE->devopen(name);
}

inline static bool devclose(void *handle){
	return SYSCALL_TABLE->devclose(handle);
}

inline static size_t devread(void *handle, size_t bytes, char *buffer){
	return SYSCALL_TABLE->devread(handle, bytes, buffer);
}

inline static size_t devwrite(void *handle, size_t bytes, char *buffer){
	return SYSCALL_TABLE->devwrite(handle, bytes, buffer);
}

inline static size_t devseek(void *handle, size_t pos, bool relative){
	return SYSCALL_TABLE->devseek(handle, pos, relative);
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

inline static void mask_irq(size_t irqno){
	SYSCALL_TABLE->mask_irq(irqno);
}

inline static void unmask_irq(size_t irqno){
	SYSCALL_TABLE->unmask_irq(irqno);
}

inline static void irq_ack(size_t irq){
	SYSCALL_TABLE->irq_ack(irq);
}

inline static void add_filesystem(fs_driver *fs){
	SYSCALL_TABLE->add_filesystem(fs);
}

inline static bool mount(const char *name, const char *device, const char *fs){
	return SYSCALL_TABLE->mount(name, device, fs);
}

inline static bool unmount(const char *name){
	return SYSCALL_TABLE->unmount(name);
}

inline static file_handle *fopen(const char *path, fs_mode_flags mode){
	return SYSCALL_TABLE->fopen(path, mode);
}

inline static bool fclose(file_handle *handle){
	return SYSCALL_TABLE->fclose(handle);
}

inline static size_t fread(file_handle *handle, size_t bytes, char *buf){
	return SYSCALL_TABLE->fread(handle, bytes, buf);
}

inline static size_t fwrite(file_handle *handle, size_t bytes, char *buf){
	return SYSCALL_TABLE->fwrite(handle, bytes, buf);
}

inline static size_t fseek(file_handle *handle, size_t pos, bool relative){
	return SYSCALL_TABLE->fseek(handle, pos, relative);
}

inline static int fioctl(file_handle *handle, int fn, size_t bytes, char *buf){
	return SYSCALL_TABLE->fioctl(handle, fn, bytes, buf);
}

inline static dir_handle *diropen(const char *path, fs_mode_flags mode){
	return SYSCALL_TABLE->diropen(path, mode);
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

inline static directory_entry stat(const char *path){
	return SYSCALL_TABLE->stat(path);
}

inline static void module_load(const char *path, char *params){
	SYSCALL_TABLE->module_load(path, params);
}

inline static void setenv(const char *name, char *value, uint8_t flags, pid_t pid){
	SYSCALL_TABLE->setenv(name, value, flags, pid);
}

inline static char *getenv(const char *name, pid_t pid){
	return SYSCALL_TABLE->getenv(name, pid);
}

inline static pid_t getpid(){
    return SYSCALL_TABLE->getpid();
}

inline static void setpid(pid_t pid){
    SYSCALL_TABLE->setpid(pid);
}

inline static pid_t spawn(const char *exec, size_t argc, char **argv){
	return SYSCALL_TABLE->spawn(exec, argc, argv);
}

inline static void wait(pid_t pid){
	SYSCALL_TABLE->wait(pid);
}

inline static void kill(pid_t pid){
    SYSCALL_TABLE->kill(pid);
}

inline static void infofs_register(const char *name, info_function fn){
	SYSCALL_TABLE->infofs_register(name, fn);
}

inline static uint16_t add_extension(kernel_extension *ext){
    return SYSCALL_TABLE->add_extension(ext);
}

inline static kernel_extension *get_extension(uint16_t ext){
    return SYSCALL_TABLE->get_extension(ext);
}

inline static uint16_t get_extension_id(const char *name){
    return SYSCALL_TABLE->get_extension_id(name);
}

inline static uint64_t msg_send(API_NS bt_msg_header *msg){
	return SYSCALL_TABLE->msg_send(msg);
}

inline static size_t msg_getcontent(API_NS bt_msg_header *msg, void *buffer, size_t buffersize){
	return SYSCALL_TABLE->msg_getcontent(msg, buffer, buffersize);
}

inline static void msg_acknowledge(API_NS bt_msg_header *msg, bool set_status){
	SYSCALL_TABLE->msg_acknowledge(msg, set_status);
}

inline static void msg_recv_reply(API_NS bt_msg_header *msg, uint64_t msg_id){
	SYSCALL_TABLE->msg_recv_reply(msg, msg_id);
}

inline static API_NS bt_msg_header msg_recv_reply_block(uint64_t msg_id){
	return SYSCALL_TABLE->msg_recv_reply_block(msg_id);
}

inline static bool msg_query_recieved(uint64_t id){
	return SYSCALL_TABLE->msg_query_recieved(id);
}

inline static bt_handle_t add_user_handle(bt_handle_info info, pid_t pid){
	return SYSCALL_TABLE->add_user_handle(info, pid);
}

inline static bt_handle_info get_user_handle(bt_handle_t h, pid_t pid){
	return SYSCALL_TABLE->get_user_handle(h, pid);
}

#endif
