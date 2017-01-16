#include "stubs.h"

int utime(const char *filename, const time_t *times){
	(void)filename; (void)times;
	return 0;
}

int mknod(const char *pathname, mode_t mode, dev_t dev){
	(void)pathname; (void)mode; (void)dev;
	return -1;
}

/*int lstat(const char *path, struct stat *buf){
	return stat(path, buf);
}*/