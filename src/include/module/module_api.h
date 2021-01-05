#ifndef _MODULE_API_H
#define	_MODULE_API_H

#ifndef KERNEL
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#endif

#include "drivers.h"
#include "../btos/fs_interface.h"
#include "../btos/bt_msg.h"
#include "handle.h"

#ifdef __cplusplus

#include "module_api.hpp"

#ifdef KERNEL
	#define MODAPI_NS module_api::
	namespace module_api{
#endif

#endif

typedef void(*thread_func)(void*);
typedef uint64_t thread_id_t;
typedef uint64_t bt_pid_t;
typedef uint32_t bt_handle_t;

typedef char* (*info_function)();
struct kernel_extension;

#ifdef MODAPI_NS
}
#endif

#ifndef __cplusplus
	typedef struct kernel_extension kernel_extension;
	#define API_NS
#else
	#define API_NS ::btos_api::
	#include "../dev/hwpnp.hpp"
	
	#ifdef MODAPI_NS
		namespace module_api{
	#endif
#endif

#define	ENV_Global 		(1<<0) //Use PID 0 (kernel) value instead
#define ENV_ReadOnly	(1<<1) //Not changeable by user-mode code
#define	ENV_Private 	(1<<2) //Not visible to user-mode code
#define ENV_NoInherit 	(1<<3) //Do not copy from parent to child

struct syscall_table{
	void (*panic)(const char *msg);
	void *(*malloc)(size_t bytes);
	void (*free)(void *ptr);
	void *(*realloc)(void *ptr, size_t new_size);
	void *(*memset)(void* ptr, int value, size_t num);
	void (*memcpy)(void *dst, const void *src, size_t size);
	void (*memmove)(void *dst, void *src, size_t size);
	int (*strcmp)(char *s1, char *s2);
	void (*strncpy)(char *dst, char *src, size_t num);
    uint32_t (*physaddr)(void *ptr);
    void *(*map_physical_pages)(uint32_t addr, size_t pages);
    void (*free_pages)(void *addr, size_t pages);
    void (*lock_low_memory)();
    void (*unlock_low_memory)();

	void (*init_lock)(lock *l);
	void (*take_lock)(lock *l);
    void (*take_lock_recursive)(lock *l);
	bool (*try_take_lock)(lock *l);
	void (*release_lock)(lock *l);

	void (*dbgout)(const char *msg);
	int (*vsprintf)(char *str, const char *fmt, va_list ap);
	int (*vsnprintf)(char *str, size_t size, const char *fmt, va_list ap);

	thread_id_t (*new_thread)(thread_func entry, void *param);
	void (*block)();
	void (*yield)();
	void (*yield_to)(bt_pid_t pid);
	thread_id_t (*thread_id)();
	void (*thread_priority)(uint32_t p_);
	void (*end_thread)();
	void (*unblock)(thread_id_t id);
	void (*thread_wait)(thread_id_t id);
	void (*thread_setblock)(bool(*blockcheck)(void*), void *param);
	void (*thread_abortable)(bool abortable);
	void (*thread_abort)(thread_id_t id);

	const char *(*add_device)(const char *name, drv_driver *driver, void *id);
	drv_device *(*get_device)(const char *name);
	void *(*get_first_device)(char **name);
	void *(*get_next_device)(void *itr, char **name);
	void *(*devopen)(const char *name);
	bool (*devclose)(void *handle);
	size_t (*devread)(void *handle, size_t bytes, char *buffer);
	size_t (*devwrite)(void *handle, size_t bytes, char *buffer);
	bt_filesize_t (*devseek)(void *handle, bt_filesize_t pos, uint32_t flags);
	int (*devioctl)(void *handle, int fn, size_t bytes, char *buffer);
	int (*devtype)(const char *name);
	char *(*devdesc)(const char *name);
	#ifdef __cplusplus
	void (*handle_int)(size_t intno, ISR_Routine handler);
	void (*handle_irq)(size_t irqno, ISR_Routine handler);
	#else
	void *handle_int;
	void *handle_irq;
	#endif
	void (*mask_irq)(size_t irqno);
	void (*unmask_irq)(size_t irqno);
	void (*irq_ack)(size_t irq_no);
	void (*handle_int_raw)(size_t intno, void *handler);
	void (*handle_irq_raw)(size_t irqno, void *handler);

	void (*add_filesystem)(fs_driver *fs);
	bool (*mount)(const char *name, const char *device, const char *fs);
	bool (*unmount)(const char *name);

	file_handle *(*fopen)(const char *path, fs_mode_flags mode);
	bool (*fclose)(file_handle *handle);
	size_t (*fread)(file_handle *handle, size_t bytes, char *buf);
	size_t (*fwrite)(file_handle *handle, size_t bytes, char *buf);
	bt_filesize_t (*fseek)(file_handle *handle, bt_filesize_t pos, uint32_t flags);
	bool (*fsetsize)(file_handle *handle, bt_filesize_t size);
	int (*fioctl)(file_handle *handle, int fn, size_t bytes, char *buf);
    void (*fflush)(file_handle *handle);

	dir_handle *(*diropen)(const char *path, fs_mode_flags mode);
	bool (*dirclose)(dir_handle *handle);
	directory_entry (*dirread)(dir_handle *handle);
	bool (*dirwrite)(dir_handle *handle, directory_entry entry);
	bool (*dirseek)(dir_handle *handle, size_t pos, uint32_t flags);
	directory_entry (*stat)(const char *path);

	void (*module_load)(const char *path, char *params);

	void (*setenv)(const char *name, char *value, uint8_t flags, bt_pid_t pid);
	char *(*getenv)(const char *name, bt_pid_t pid);

	bt_pid_t (*getpid)();
    bool (*setpid)(bt_pid_t pid);
	bt_pid_t (*spawn)(const char *exec, size_t argc, char **argv);
	void (*wait)(bt_pid_t pid);
    void (*kill)(bt_pid_t pid);
    int (*get_proc_status)(bt_pid_t pid);

	void (*infofs_register)(const char *name, info_function fn);

    uint16_t (*add_extension)(kernel_extension *ext);
    kernel_extension *(*get_extension)(uint16_t ext);
    uint16_t (*get_extension_id)(const char *name);
	
	uint64_t (*msg_send)(API_NS bt_msg_header *msg);
	size_t (*msg_getcontent)(API_NS bt_msg_header *msg, void *buffer, size_t buffersize);
	void (*msg_acknowledge)(API_NS bt_msg_header *msg, bool set_status);
	bool (*msg_recv_reply)(API_NS bt_msg_header *msg, uint64_t msg_id);
	API_NS bt_msg_header (*msg_recv_reply_block)(uint64_t msg_id);
	bool (*msg_query_recieved)(uint64_t id);
	
	bt_handle_t (*add_user_handle)(bt_handle_info info, bt_pid_t pid);
	bt_handle_info (*get_user_handle)(bt_handle_t h, bt_pid_t pid);
	void (*set_kvar)(const char *name, const char *value);
	size_t (*get_kvar)(const char *name, char *buffer, size_t size);
	
	#ifdef __cplusplus
	void (*pnp_register_driver)(btos_api::hwpnp::IDriver *driver);
	void (*pnp_unregister_driver)(btos_api::hwpnp::IDriver *driver);
	void (*pnp_add_device)(btos_api::hwpnp::IDevice *parent, const btos_api::hwpnp::DeviceID &id, size_t idx);
	btos_api::hwpnp::IDevice *(*pnp_resolve_device)(btos_api::hwpnp::IDevice *parent, const btos_api::hwpnp::DeviceID &id, size_t idx);
	void (*pnp_rescan_devices)();
	void (*pnp_set_root_device)(btos_api::hwpnp::IRootDevice *dev);
	btos_api::hwpnp::IDevice *(*pnp_get_parent)(btos_api::hwpnp::IDevice *dev);
	const char *(*pnp_get_node_name)(btos_api::hwpnp::IDeviceNode *node);
	IModuleAPI &(*GetNewAPI)();
	#else
	void *pnp_register_driver;
	void *pnp_unregister_driver;
	void *pnp_add_device;
	void *pnp_resolve_device;
	void *pnp_rescan_devices;
	void *pnp_set_root_device;
	void *pnp_get_parent;
	void *pnp_get_node_name;

	void *GetNewAPI;
	#endif
};

#ifndef __cplusplus
typedef struct syscall_table syscall_table;
#endif

#ifndef KERNEL
extern syscall_table *SYSCALL_TABLE;
#endif

#ifdef MODAPI_NS
}
#endif

#endif
