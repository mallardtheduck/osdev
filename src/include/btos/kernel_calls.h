#ifndef _BTOS_STUBS_H
#define _BTOS_STUBS_H

#include "btos_api.h"
#include "bt_msg.h"
#include "atoms.h"

#ifdef __cplusplus
namespace btos_api{
//#define EXTERN_C extern "C"
#else
#include <stdbool.h>
//#define EXTERN_C
#endif

EXTERN_C uint32_t btos_call(uint32_t fn, uint32_t p1, uint32_t p2, uint32_t p3);

EXTERN_C void bt_zero(const char *string);
EXTERN_C void *bt_alloc_pages(size_t pages);
EXTERN_C void *bt_alloc_at(size_t pages, void *ptr);
EXTERN_C void bt_free_pages(void *address, size_t pages);

EXTERN_C void bt_closehandle(bt_handle h);
EXTERN_C bool bt_queryhandle(bt_handle h);

EXTERN_C bt_handle_t bt_create_shm(uint32_t flags);
EXTERN_C uint64_t bt_shm_id(bt_handle_t h);
EXTERN_C bt_handle_t bt_shm_map(uint64_t id, void *addr, uint32_t offset, size_t pages, uint32_t flags);

EXTERN_C size_t bt_get_argc();
EXTERN_C size_t bt_get_arg(size_t index, char *buf, size_t size);

EXTERN_C bt_lockhandle bt_create_lock();
EXTERN_C void bt_lock(bt_lockhandle lock);
EXTERN_C bool bt_try_lock(bt_lockhandle lock);
EXTERN_C void bt_unlock(bt_lockhandle lock);
EXTERN_C void bt_destroy_lock(bt_lockhandle lock);

EXTERN_C bt_handle_t bt_create_atom(uint64_t ini_val);
EXTERN_C uint64_t bt_modify_atom(bt_handle_t a, ENUM_NAME(bt_atom_modify) mod, uint64_t val);
EXTERN_C uint64_t bt_wait_atom(bt_handle_t a, ENUM_NAME(bt_atom_compare) cmp, uint64_t val);
EXTERN_C uint64_t bt_cmpxchg_atom(bt_handle_t a, uint64_t cmp, uint64_t xchg);
EXTERN_C uint64_t bt_read_atom(bt_handle_t a);

EXTERN_C bt_threadhandle bt_new_thread(void (*entry)(void*), void *param, void *stack);
EXTERN_C void bt_wait_thread(bt_threadhandle thread);
EXTERN_C void bt_block_thread();
EXTERN_C void bt_unblock_thread(bt_threadhandle thread);
EXTERN_C bt_threadhandle bt_get_thread();
EXTERN_C void bt_end_thread();
EXTERN_C void bt_yield();
EXTERN_C void bt_thread_abort(bt_threadhandle thread);

EXTERN_C bool bt_mount(const char *name, const char *device, const char *filesystem);
EXTERN_C bool bt_unmount(const char *name);
EXTERN_C bt_filehandle bt_fopen(const char *path, uint32_t flags);
EXTERN_C bool bt_fclose(bt_filehandle file);
EXTERN_C size_t bt_fwrite(bt_filehandle file, size_t bytes, const char *buffer);
EXTERN_C size_t bt_fread(bt_filehandle file, size_t bytes, char *buffer);
EXTERN_C size_t bt_fioctl(bt_filehandle file, int function, size_t bytes, char *buffer);
EXTERN_C bt_filesize_t bt_fseek(bt_filehandle file, bt_filesize_t bytes, uint32_t flags);
EXTERN_C bool bt_fsetsize(bt_filehandle file, bt_filesize_t size);
EXTERN_C bool bt_format(const char *fs, const char *device, void *options);
EXTERN_C void bt_fflush(bt_filehandle file);
EXTERN_C bt_handle bt_mmap(bt_filehandle file, size_t offset, char *ptr, size_t size);
EXTERN_C bt_dirhandle bt_dopen(const char *path, uint32_t flags);
EXTERN_C bool bt_dclose(bt_dirhandle dir);
EXTERN_C bool bt_dwrite(bt_dirhandle dir, bt_directory_entry entry);
EXTERN_C bt_directory_entry bt_dread(bt_dirhandle dir);
EXTERN_C size_t bt_dseek(bt_dirhandle dir, size_t bytes, uint32_t flags);
EXTERN_C bt_directory_entry bt_stat(const char *path);

EXTERN_C bool bt_load_module(const char *path, const char *params);

EXTERN_C size_t bt_getenv(const char *name, char *buffer, size_t size);
EXTERN_C bool bt_setenv(const char *name, const char *value, uint32_t flags);

EXTERN_C bt_pid bt_spawn(const char *path, size_t argc, char **argv);
EXTERN_C int bt_wait(bt_pid pid);
EXTERN_C bool bt_kill(bt_pid pid);
EXTERN_C bt_priority bt_prioritize(bt_pid pid, bt_priority priority);
EXTERN_C void bt_exit(int retval);
EXTERN_C bt_pid bt_getpid();
EXTERN_C ENUM_NAME(bt_proc_status) bt_get_proc_status(bt_pid pid);

EXTERN_C uint64_t bt_send(bt_msg_header msg);
EXTERN_C bt_msg_header bt_recv(bool block);
EXTERN_C void bt_next_msg(bt_msg_header *msg);
EXTERN_C size_t bt_msg_content(bt_msg_header *header, void *buf, size_t size);
EXTERN_C void bt_msg_ack(bt_msg_header *header);
EXTERN_C void bt_subscribe(ENUM_NAME(bt_kernel_messages) msg);
EXTERN_C void bt_unsubscribe(ENUM_NAME(bt_kernel_messages) msg);
EXTERN_C void bt_msgwait();
EXTERN_C bt_msg_header bt_recv_filtered(bt_msg_filter filter);
EXTERN_C void bt_next_msg_filtered(bt_msg_header *msg, bt_msg_filter filter);
EXTERN_C bool bt_query_msg(uint64_t id);

EXTERN_C uint16_t bt_query_extension(const char *name);

EXTERN_C void bt_multi_call(bt_syscall_item *items, size_t count);

#ifdef __cplusplus
}
#endif
#endif
