#ifndef _MODULE_API_H
#define	_MODULE_API_H

#ifndef KERNEL
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#endif

#include "drivers.h"
#include "fs_interface.h"

typedef volatile uint64_t lock;
typedef void(*thread_func)(void*);
typedef uint64_t thread_id_t;
typedef uint64_t pid_t;

struct syscall_table{
	void (*panic)(char *msg);
	void *(*malloc)(size_t bytes);
	void (*free)(void *ptr);
	void *(*memset)(void* ptr, int value, size_t num);
	void (*memcpy)(void *dst, void *src, size_t size);
	void (*memmove)(void *dst, void *src, size_t size);
	int (*strcmp)(char *s1, char *s2);
	void (*strncpy)(char *dst, char *src, size_t num);

	void (*init_lock)(lock *l);
	void (*take_lock)(lock *l);
	bool (*try_take_lock)(lock *l);
	void (*release_lock)(lock *l);

	void (*dbgout)(char *msg);
	void (*sprintf)(char *buf, char *fmt, ...);

	void (*new_thread)(thread_func entry, void *param);
	void (*block)();
	void (*yield)();
	thread_id_t (*thread_id)();
	void (*thread_priority)(uint32_t p_);
	void (*end_thread)();
	void (*unblock)(thread_id_t id);

	void (*add_device)(char *name, drv_driver *driver);
	drv_driver *(*get_device)(char *name);
	void *(*get_first_device)(char **name);
	void *(*get_next_device)(void *itr, char **name);
	void *(*devopen)(char *name);
	bool (*devclose)(void *handle);
	int (*devread)(void *handle, size_t bytes, char *buffer);
	bool (*devwrite)(void *handle, size_t bytes, char *buffer);
	void (*devseek)(void *handle, size_t pos, bool relative);
	int (*devioctl)(void *handle, int fn, size_t bytes, char *buffer);
	int (*devtype)(char *name);
	char *(*devdesc)(char *name);
	void (*handle_int)(size_t intno, int_handler handler);
	void (*handle_irq)(size_t irqno, int_handler handler);

	void (*add_filesystem)(fs_driver *fs);
	bool (*mount)(char *name, char *device, char *fs);
	bool (*unmount)(char *name);

	file_handle *(*fopen)(char *path);
	bool (*fclose)(file_handle *handle);
	int (*fread)(file_handle *handle, size_t bytes, char *buf);
	bool (*fwrite)(file_handle *handle, size_t bytes, char *buf);
	bool (*fseek)(file_handle *handle, size_t pos, bool relative);
	int (*fioctl)(file_handle *handle, int fn, size_t bytes, char *buf);
	file_handle *(*fcreate)(char *path);

	dir_handle *(*diropen)(char *path);
	bool (*dirclose)(dir_handle *handle);
	directory_entry (*dirread)(dir_handle *handle);
	bool (*dirwrite)(dir_handle *handle, directory_entry entry);
	bool (*dirseek)(dir_handle *handle, size_t pos, bool relative);
	dir_handle *(*dircreate)(char *path);
	directory_entry (*stat)(char *path);

	void (*module_load)(char *path);

	void (*setenv)(char *name, char *value, uint8_t flags, pid_t pid);
	char *(*getenv)(char *name, pid_t pid);

	pid_t (*getpid)();
};

#ifndef __cplusplus
typedef struct syscall_table syscall_table;
#endif

#ifndef KERNEL
extern syscall_table *SYSCALL_TABLE;
#endif

#endif
