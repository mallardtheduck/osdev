#ifndef _DRIVERS_H
#define _DRIVERS_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include <btos/devices.h>
#include <btos/fs_interface.h>

struct drv_driver{
	void *(*open)(void *id);
	bool (*close)(void *instance);
	size_t (*read)(void *instance, size_t bytes, char *buf);
	size_t (*write)(void *instance, size_t bytes, char *buf);
	bt_filesize_t (*seek)(void *instance, bt_filesize_t pos, uint32_t flags);
	int (*ioctl)(void *instance, int fn, size_t bytes, char *buf);
	int (*type)(void *id);
	char *(*desc)(void *id);
};

#ifndef __cplusplus
typedef struct drv_driver drv_driver;
#endif

struct drv_device{
	drv_driver driver;
	void *id;
};

#ifndef __cplusplus
typedef struct drv_device drv_device;
#endif

struct isr_regs {
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t interrupt_number, error_code;
	uint32_t eip, cs, eflags;
	uint32_t useresp, userss;
} __attribute__((packed));

#ifndef __cplusplus
typedef struct isr_regs isr_regs;
#endif

typedef void(*int_handler)(int, isr_regs*);

#endif