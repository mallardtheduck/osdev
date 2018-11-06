#include "devfs.hpp"
#include "kernel.hpp"
#include <btos/ioctl.h>

void* const devfs_magic=(void*)0xDE7F5;
void* const devfs_dirmagic=(void*)0xDE7D19;

struct devfs_dirhandle{
	size_t pos;
	devfs_dirhandle(size_t p=0) : pos(p) {}
};

#define ddata ((devfs_dirhandle*)dirdata)


void *devfs_mount(char *){
	return devfs_magic;
}

bool devfs_unmount(void *mountdata){
	return (mountdata==devfs_magic);
}

void *devfs_open(void *, fs_path *path, fs_mode_flags){
	return drv_open(path->str);
}

bool devfs_close(void *filedata){
	return drv_close(filedata);
}

size_t devfs_read(void *filedata, size_t bytes, char *buf){
	return drv_read(filedata, bytes, buf);
}

size_t devfs_write(void *filedata, size_t bytes, char *buf){
	return drv_write(filedata, bytes, buf);
}

bt_filesize_t devfs_seek(void *filedata, bt_filesize_t pos, uint32_t flags){
	return drv_seek(filedata, pos, flags);
}

bool devfs_setsize(void *filedata, bt_filesize_t size){
	return false;
}

int devfs_ioctl(void *filedata, int fn, size_t bytes, char *buf){
    if(fn < 256 && fn != bt_ioctl::BlockSize){
        if(fn==bt_ioctl::DevType) return drv_get_type(filedata);
        else if(fn==bt_ioctl::DevDesc){
            memcpy(buf, drv_get_desc(filedata), bytes-1);
            buf[bytes-1]='\0';
            return strlen(drv_get_desc(filedata));
        }else return 0;
    }else return drv_ioctl(filedata, fn, bytes, buf);
}

void devfs_flush(void *){
}

void *devfs_open_dir(void *, fs_path *, fs_mode_flags){
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
		ret.id = (uint64_t)drv_get(name);
		ret.size=0;
		ret.type=FS_Device;
		ddata->pos++;
	}
	return ret;
}

bool devfs_write_dir(void *, directory_entry){
	return false;
}

size_t devfs_dirseek(void *dirdata, size_t pos, uint32_t flags){
	if(flags & FS_Relative) ddata->pos+=pos;
	else if(flags & FS_Backwards){
		int count = 0;
		char *name;
		void *drvi=drv_firstdevice(&name);
		while((drvi = drv_nextdevice(drvi, &name))) count++;
		ddata->pos = count - pos;
	} else if(flags == (FS_Backwards | FS_Relative)) ddata->pos-=pos;
	else ddata->pos=pos;
	return ddata->pos;
}

directory_entry devfs_stat(void *, fs_path *path){
	if(!path->next && strcmp(path->str, "")==0){
		directory_entry ret;
		ret.valid=true;
		strncpy(ret.filename, "/", 255);
		ret.size=0;
		ret.type=FS_Directory;
		return ret;
	}
	directory_entry ret;
	ret.valid=false;
	drv_device *dev=drv_get(path->str);
	if(dev){
		ret.valid=true;
		strncpy(ret.filename, path->str, 255);
		ret.id = (uint64_t)dev;
		ret.size=0;
		ret.type=FS_Device;
	}
	return ret;
}

bool devfs_format(char*, void*){
	return false;
}

fs_driver devfs_driver = {true, "DEVFS", false, devfs_mount, devfs_unmount,
							devfs_open, devfs_close, devfs_read, devfs_write, devfs_seek, devfs_setsize, devfs_ioctl, devfs_flush,
							devfs_open_dir, devfs_close_dir, devfs_read_dir, devfs_write_dir, devfs_dirseek,
							devfs_stat, devfs_format};

fs_driver devfs_getdriver(){
	return devfs_driver;
}
