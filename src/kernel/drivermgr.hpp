#ifndef _DRIVERMGR_HPP
#define _DRIVERMGR_HPP

namespace driver_types{
	const int TIMER		= 0x01;
	const int BUS		= 0x02;
	const int INPUT		= 0x10;
	const int IN_KEYBOARD 	= 0x11;
	const int IN_MOUSE	= 0x12;
	const int VIDEO		= 0x20;
	const int VID_TEXT	= 0x21;
	const int STORAGE	= 0x30;
	const int STR_HDD	= 0x31;
	const int STR_OPTICAL	= 0x32;
	const int STR_SSD	= 0x33;
	const int STR_FLASH	= 0x34;
	const int STR_MEMCARD	= 0x35;
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
};

struct drv_driver{
	void *(*open)();
	bool (*close)(void *instance);
	int (*read)(void *instance, size_t bytes, char *buf);
	bool (*write)(void *instance, size_t bytes, char *buf);
	void (*seek)(void *instance, size_t pos, bool relative);
	int (*ioctl)(void *instance, int fn, size_t bytes, char *buf);
	int (*type)();
	char *(*desc)();
};

void drv_init();
void drv_add_device(char *name, drv_driver *driver);
drv_driver drv_get(char *name);

void *drv_open(char *driver);
bool drv_close(void *instance);
int drv_read(void *instance, size_t bytes, char *buf);
bool drv_write(void *instance, size_t bytes, char *buf);
void drv_seek(void *instance, size_t pos, bool relative);	
int drv_ioctl(void *instance, int fn, size_t bytes, char *buf);	
int drv_get_type(char *driver);
int drv_get_type(void *instance);
char *drv_get_desc(char *driver);
char *drv_get_desc(void *instance);

#endif
