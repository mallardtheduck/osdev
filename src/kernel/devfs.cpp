#include "devfs.hpp"
#include "kernel.hpp"

void* const devfs_magic=(void*)0xDE7F5;
void* const devfs_dirmagic=(void*)0xDE7D19;

/*struct fs_driver{
	bool valid;
	char name[9];
	bool needs_device;
	void *(*mount)(char *device);
	bool (*unmount)(void *mountdata);
	void *(*open)(void *mountdata, char *path);
	bool (*close)(void *filedata);
	int (*read)(void *filedata, size_t pos, size_t bytes, char *buf);
	bool (*write)(void *filedata, size_t pos, size_t bytes, char *buf);
	int (*ioctl)(void *filedata, int fn, size_t bytes, char *buf);
	void *(*open_dir)(void *mountdata, char *path);
	bool (*close_dir)(void *dirdata);
	directory_entry (*read_dir)(void *dirdata, size_t pos);
	bool (*write_dir)(void *dirdata, directory_entry entry, size_t pos);
	directory_entry (*stat)(void *mountdata, char *path);
};*/

void *devfs_mount(char *){
	return devfs_magic;
}

bool devfs_unmount(void *mountdata){
	return (mountdata==devfs_magic);
}

void *devfs_open(void *, char *path){
	return drv_open(path);
}

bool devfs_close(void *filedata){
	return drv_close(filedata);
}

int devfs_read(void *filedata, size_t pos, size_t bytes, char *buf){
	drv_seek(filedata, pos, false);
	return drv_read(filedata, bytes, buf);
}

bool devfs_write(void *filedata, size_t pos, size_t bytes, char *buf){
	drv_seek(filedata, pos, false);
	return drv_write(filedata, bytes, buf);
}

int devfs_ioctl(void *filedata, int fn, size_t bytes, char *buf){
	return drv_ioctl(filedata, fn, bytes, buf);
}

void *devfs_open_dir(void *, char *){
	return devfs_dirmagic;
}

bool devfs_close_dir(void *dirdata){
	return (dirdata==devfs_dirmagic);
}

directory_entry devfs_read_dir(void *, size_t pos){
	char *name;
	void *drvi=drv_firstdevice(&name);
	directory_entry ret;
	ret.valid=false;
	for(size_t i=0; i<pos; ++i){
		drvi=drv_nextdevice(drvi, &name);
	}
	if(drvi){
		ret.valid=true;
		strncpy(ret.filename, name, 255);
		ret.size=0;
		ret.type=direntry_types::Device;
	}
	return ret;
}

bool devfs_write_dir(void *, directory_entry, size_t){
	return false;
}

directory_entry devfs_stat(void *, char *path){
	directory_entry ret;
	ret.valid=false;
	drv_driver drv=*drv_get(path);
	if(drv.open!=NULL){
		ret.valid=true;
		strncpy(ret.filename, path, 255);
		ret.size=0;
		ret.type=direntry_types::Device;
	}
	return ret;
}

fs_driver devfs_driver = {true, "DEVFS", false, devfs_mount, devfs_unmount, devfs_open, devfs_close, devfs_read, devfs_write, devfs_ioctl, devfs_open_dir, devfs_close_dir, devfs_read_dir, devfs_write_dir, devfs_stat};

fs_driver devfs_getdriver(){
	return devfs_driver;
}
