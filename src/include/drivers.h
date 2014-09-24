#ifndef _DRIVERS_H
#define _DRIVERS_H

#ifndef __cplusplus
#include <stdbool.h>
#endif

#ifdef __cplusplus
namespace driver_types{
#endif
	static const int TIMER		= 0x01;
	static const int BUS		= 0x02;
	static const int INPUT		= 0x10;
	static const int IN_KEYBOARD 	= 0x11;
	static const int IN_MOUSE	= 0x12;
	static const int IN_GAME	= 0x13;
	static const int IN_TOUCH	= 0x14;
	static const int IN_TABLET = 0x15;
	static const int VIDEO		= 0x20;
	static const int VID_TEXT	= 0x21;
	static const int STORAGE	= 0x30;
	static const int STR_HDD	= 0x31;
	static const int STR_OPTICAL	= 0x32;
	static const int STR_SSD	= 0x33;
	static const int STR_FLASH	= 0x34;
	static const int STR_MEMCARD	= 0x35;
	static const int STR_FLOPPY = 0x35;
	static const int STR_TAPE	 = 0x36;
	static const int STR_PART	= 0x37;
	static const int NIC		= 0x40;
	static const int NIC_ETHERNET	= 0x41;
	static const int NIC_WIRELESS	= 0x42;
	static const int AUDIO		= 0x50;
	static const int AUD_OUTPUT	= 0x51;
	static const int AUD_INPUT	= 0x52;
	static const int IOPORT	= 0x60;
	static const int IO_SERIAL	= 0x61;
	static const int IO_PARALELL	= 0x62;
	static const int IO_BLUETOOTH	= 0x63;
	static const int PRINTER	= 0x70;
	static const int PRN_TEXT	= 0x71;
	static const int GRAPHICINPUT	= 0x80;
	static const int GI_SCANNER	= 0x81;
	static const int GI_STILLCAM	= 0x82;
	static const int GI_VIDCAM	= 0x83;
	static const int LCDSCREEN	= 0x90;
    static const int TERMINAL   = 0xA0;
	static const int BESPOKE	= 0xF0;
	static const int USER		= 0xFF;
#ifdef __cplusplus
};
#endif

struct drv_driver{
	void *(*open)(void *id);
	bool (*close)(void *instance);
	size_t (*read)(void *instance, size_t bytes, char *buf);
	size_t (*write)(void *instance, size_t bytes, char *buf);
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