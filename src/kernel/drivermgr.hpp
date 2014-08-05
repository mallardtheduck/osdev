#ifndef _DRIVERMGR_HPP
#define _DRIVERMGR_HPP

#include <drivers.h>

void drv_init();
void drv_add_device(char *name, drv_driver *driver, void *id);
drv_device *drv_get(char *name);
void *drv_firstdevice(char**);
void *drv_nextdevice(void*,char**);

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
