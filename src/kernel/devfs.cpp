#include "devfs.hpp"
#include "kernel.hpp"

void* const devfs_magic=(void*)0xDE7F5;
void* const devfs_dirmagic=(void*)0xDE7D19;

struct devfs_dirhandle{
	size_t pos;
	devfs_dirhandle(size_t p=0) : pos(p) {}
};

#define ddata ((devfs_dirhandle*)dirdata)

/*struct fs_driver{
  	bool valid;
  	char name[9];
  	bool needs_device;
  	void *(*mount)(char *device);
  	bool (*unmount)(void *mountdata);
  	void *(*open)(void *mountdata, fs_path *path);
  	bool (*close)(void *filedata);
  	int (*read)(void *filedata, size_t bytes, char *buf);
  	bool (*write)(void *filedata, size_t bytes, char *buf);
  	bool (*seek)(void *filedata, int pos, bool relative);
  	int (*ioctl)(void *filedata, int fn, size_t bytes, char *buf);
  	void *(*open_dir)(void *mountdata, fs_path *path);
  	bool (*close_dir)(void *dirdata);
  	directory_entry (*read_dir)(void *dirdata);
  	bool (*write_dir)(void *dirdata, directory_entry entry);
  	bool (*dirseek)(void *dirdata, int pos, bool relative);
  	directory_entry (*stat)(void *mountdata, fs_path *path);
  };*/

void *devfs_mount(char *){
	return devfs_magic;
}

bool devfs_unmount(void *mountdata){
	return (mountdata==devfs_magic);
}

void *devfs_open(void *, fs_path *path){
	return drv_open(path->str);
}

bool devfs_close(void *filedata){
	return drv_close(filedata);
}

int devfs_read(void *filedata, size_t bytes, char *buf){
	return drv_read(filedata, bytes, buf);
}

bool devfs_write(void *filedata, size_t bytes, char *buf){
	return drv_write(filedata, bytes, buf);
}

bool devfs_seek(void *filedata, int pos, bool relative){
	drv_seek(filedata, pos, relative);
	return true;
}

int devfs_ioctl(void *filedata, int fn, size_t bytes, char *buf){
	return drv_ioctl(filedata, fn, bytes, buf);
}

void *devfs_open_dir(void *, fs_path *){
	return (void*)new devfs_dirhandle();
}

bool devfs_close_dir(void *dirdata){
	delete ddata;
	return true;
}

directory_entry devfs_read_dir(void *dirdata){
	char *name;
	void *drvi=drv_firstdevice(&name);
	directory_entry ret;
	ret.valid=false;
	for(size_t i=0; i<ddata->pos; ++i){
		drvi=drv_nextdevice(drvi, &name);
	}
	if(drvi){
		ret.valid=true;
		strncpy(ret.filename, name, 255);
		ret.size=0;
		ret.type=FS_Device;
		ddata->pos++;
	}
	return ret;
}

bool devfs_write_dir(void *, directory_entry){
	return false;
}

bool devfs_dirseek(void *dirdata, int pos, bool relative){
	if(relative) ddata->pos+=pos;
	else ddata->pos=pos;
	return true;
}

directory_entry devfs_stat(void *, fs_path *path){
	directory_entry ret;
	ret.valid=false;
	drv_driver drv=*drv_get(path->str);
	if(drv.open!=NULL){
		ret.valid=true;
		strncpy(ret.filename, path->str, 255);
		ret.size=0;
		ret.type=FS_Device;
	}
	return ret;
}

fs_driver devfs_driver = {true, "DEVFS", false, devfs_mount, devfs_unmount,
							devfs_open, devfs_close, devfs_read, devfs_write, devfs_seek, devfs_ioctl,
							devfs_open_dir, devfs_close_dir, devfs_read_dir, devfs_write_dir, devfs_dirseek,
							devfs_stat};

fs_driver devfs_getdriver(){
	return devfs_driver;
}
