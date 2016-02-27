#ifndef _DRIVERMGR_HPP
#define _DRIVERMGR_HPP

#include <module/drivers.h>

void drv_init();
void drv_add_device(char *name, drv_driver *driver, void *id);
drv_device *drv_get(const char *name);
void *drv_firstdevice(char**);
void *drv_nextdevice(void*,char**);

void *drv_open(const char *driver);
bool drv_close(void *instance);
size_t drv_read(void *instance, size_t bytes, char *buf);
size_t drv_write(void *instance, size_t bytes, char *buf);
bt_filesize_t drv_seek(void *instance, bt_filesize_t pos, uint32_t flags);
int drv_ioctl(void *instance, int fn, size_t bytes, char *buf);	
int drv_get_type(const char *driver);
int drv_get_type(void *instance);
char *drv_get_desc(const char *driver);
char *drv_get_desc(void *instance);

#endif
