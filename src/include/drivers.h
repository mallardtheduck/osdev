#ifndef _DRIVERS_H
#define _DRIVERS_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
namespace driver_types{
#endif
	const int TIMER		= 0x01;
	const int BUS		= 0x02;
	const int INPUT		= 0x10;
	const int IN_KEYBOARD 	= 0x11;
	const int IN_MOUSE	= 0x12;
	const int IN_GAME	= 0x13;
	const int IN_TOUCH	= 0x14;
	const int IN_TABLET = 0x15;
	const int VIDEO		= 0x20;
	const int VID_TEXT	= 0x21;
	const int STORAGE	= 0x30;
	const int STR_HDD	= 0x31;
	const int STR_OPTICAL	= 0x32;
	const int STR_SSD	= 0x33;
	const int STR_FLASH	= 0x34;
	const int STR_MEMCARD	= 0x35;
	const int STR_FLOPPY = 0x35;
	const int STR_TAPE	 = 0x36;
	const int NIC		= 0x40;
	const int NIC_ETHERNET	= 0x41;
	const int NIC_WIRELESS	= 0x42;
	const int AUDIO		= 0x50;
	const int AUD_OUTPUT	= 0x51;
	const int AUD_INPUT	= 0x52;
	const int IOPORT	= 0x60;
	const int IO_SERIAL	= 0x61;
	const int IO_PARALELL	= 0x62;
	const int IO_BLUETOOTH	= 0x63;
	const int PRINTER	= 0x70;
	const int PRN_TEXT	= 0x71;
	const int GRAPHICINPUT	= 0x80;
	const int GI_SCANNER	= 0x81;
	const int GI_STILLCAM	= 0x82;
	const int GI_VIDCAM	= 0x83;
	const int LCDSCREEN	= 0x90;
	const int BESPOKE	= 0xF0;
	const int USER		= 0xFF;
#ifdef __cplusplus
};
#endif

struct drv_driver{
	void *(*open)(void *id);
	bool (*close)(void *instance);
	int (*read)(void *instance, size_t bytes, char *buf);
	bool (*write)(void *instance, size_t bytes, char *buf);
	size_t (*seek)(void *instance, size_t pos, bool relative);
	int (*ioctl)(void *instance, int fn, size_t bytes, char *buf);
	int (*type)();
	char *(*desc)();
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
} __attribute__((packed));

#ifndef __cplusplus
typedef struct isr_regs isr_regs;
#endif

typedef void(*int_handler)(int, isr_regs*);

#endif