#ifndef _STUBS_H
#define _STUBS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <utime.h>

int utime(const char *filename, const time_t *times);
int mknod(const char *pathname, mode_t mode, dev_t dev);
int lstat(const char *path, struct stat *buf);

#define major(x) 0
#define minor(x) 0
#define makedev(x, y) 0

#endif