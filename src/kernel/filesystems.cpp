#include "kernel.hpp"
#include "filesystems.hpp"
#include "ministl.hpp"
#include "locks.hpp"

map<string, fs_mountpoint> *fs_mounts;
map<string, fs_driver> *fs_drivers;

lock fs_lock;

void fs_init(){
	dbgout("FS: Init\n");
	init_lock(fs_lock);
	take_lock(fs_lock);
	fs_mounts=new map<string, fs_mountpoint>();
	fs_drivers=new map<string, fs_driver>();
	release_lock(fs_lock);
	fs_registerfs(initfs_getdriver());
	fs_registerfs(devfs_getdriver());
	fs_mount("INIT", NULL, "INITFS");
	printf("FS: Mounted INITFS on INIT:\n");
	fs_mount("DEV", NULL, "DEVFS");
	printf("FS: Mounted DEVFS on DEV:\n");
	directory_entry root=fs_stat("INIT:");
	if(!root.valid) panic("(FS) Cannot stat root of INIT:!\n");
	dbgpf("FS: Root size: %i, type: 0x%x.\n", root.size, root.type);
	dir_handle dir=fs_open_dir("INIT:");
	while(true){
		directory_entry entry=fs_read_dir(dir);
		if(!entry.valid) break;
		dbgpf("FS: %s %i 0x%x\n", entry.filename, entry.size, entry.type);
	}
	fs_close_dir(dir);
}

fs_driver &getfs(char *name){
	hold_lock hl(fs_lock);
	return (*fs_drivers)[name];
}

fs_mountpoint &getmount(char *name){
	hold_lock hl(fs_lock);
	return (*fs_mounts)[name];
}

void fs_registerfs(const fs_driver &driver){
	hold_lock hl(fs_lock);
	string name=driver.name;
	(*fs_drivers)[name]=driver;
}

fs_mountpoint &getpathmount(char *path){
	char mountname[9]={0};
	for(int i=0; i<8 && path[i]!='\0' && path[i]!=':'; ++i){
		mountname[i]=path[i];
	}
	return getmount(mountname);
}

char *getfspath(char *path){
	char *ret=path;
	while(*ret++!='\0'){
		if(*ret==':') return ++ret;
	}
	return NULL;
}

bool fs_mount(char *name, char *device, char *fs){
	fs_driver driver=getfs(fs);
	if(driver.valid){
		hold_lock hl(fs_lock);
		if(driver.needs_device){
			//TODO: Device drivers...
			return false;
		}else{
			fs_mountpoint &mount=(*fs_mounts)[name];
			mount.valid=true;
			strncpy(mount.name, name, 9);
			mount.driver=driver;
			mount.mountdata=driver.mount(device);
			dbgpf("FS: Mounted %s on %s (%s).\n", device?device:"NULL", name, fs);
		}
	}
	return false;
}

bool fs_unmount(char *name){
	fs_mountpoint mount=getmount(name);
	if(mount.valid){
		hold_lock hl(fs_lock);
		//TODO: Check for open files...
		mount.driver.unmount(mount.mountdata);
		mount.valid=false;
		fs_mounts->erase(name);
		dbgpf("FS: Unmounted %s.\n", name);
		return true;
	} else {
		return false;
	}
}

file_handle fs_open(char *path){
	dbgpf("FS: OPEN %s.\n", path);
	file_handle ret;
	char *fspath=getfspath(path);
	if(!fspath){
		ret.valid=false;
		return ret;
	}
	fs_mountpoint &mount=getpathmount(path);
	if(!mount.valid){
		ret.valid=false;
		return ret;
	}
	void *filedata=mount.driver.open(mount.mountdata, fspath);
	if(!filedata){
		dbgout("FS: Open failed in FS driver.\n");
		ret.valid=false;
		return ret;
	}
	ret.mount=&mount;
	ret.filedata=filedata;
	ret.pos=0; //TODO: Open modes?
	ret.valid=true;
	dbgpf("FS: Opened %s.\n", path);
	return ret;
}

bool fs_close(file_handle &file){
	if(!file.valid) return false;
	file.valid=false;
	bool ret=file.mount->driver.close(file.filedata);
	if(ret) dbgout("FS: Closed a file.\n");
	return ret;
}

int fs_read(file_handle &file, size_t bytes, char *buf){
	if(!file.valid) return -1;
	int read=file.mount->driver.read(file.filedata, file.pos, bytes, buf);
	file.pos+=read;
	return read;
}

bool fs_write(file_handle &file, size_t bytes, char *buf){
	if(!file.valid) return false;
	bool ok=file.mount->driver.read(file.filedata, file.pos, bytes, buf);
	if(ok) file.pos+=bytes;
	return ok;
}

bool fs_seek(file_handle &file, int32_t pos, bool relative){
	if(!file.valid) return false;
	if(relative) file.pos+=pos;
	else file.pos=pos;
	return true;
}

int fs_ioctl(file_handle &file, int fn, size_t bytes, char *buf){
	if(!file.valid) return false;
	return file.mount->driver.ioctl(file.filedata, fn, bytes, buf);
}

dir_handle fs_open_dir(char *path){
	dir_handle ret;
	char *fspath=getfspath(path);
	if(!fspath){
		ret.valid=false;
		return ret;
	}
	fs_mountpoint &mount=getpathmount(path);
	if(!mount.valid){
		ret.valid=false;
		return ret;
	}
	void *dirdata=mount.driver.open_dir(mount.mountdata, fspath);
	if(!dirdata){
		dbgout("FS: Directory open failed in FS driver.\n");
		ret.valid=false;
		return ret;
	}
	ret.dirdata=dirdata;
	ret.mount=&mount;
	ret.pos=0;
	ret.valid=true;
	dbgpf("FS: Opened directory %s.\n", path);
	return ret;
}

bool fs_close_dir(dir_handle &dir){
	if(!dir.valid) return false;
	dir.valid=false;
	bool ret=dir.mount->driver.close_dir(dir.dirdata);
	if(ret) dbgout("FS: Closed a directory.\n");
	return ret;
}

directory_entry fs_read_dir(dir_handle &dir){
	directory_entry ret;
	if(!dir.valid){
		ret.valid=false;
		return ret;
	}
	ret=dir.mount->driver.read_dir(dir.dirdata, dir.pos);
	if(ret.valid) dir.pos++;
	return ret;
}

bool fs_write_dir(dir_handle &dir, directory_entry entry){
	if(!dir.valid) return false;
	bool ret=dir.mount->driver.write_dir(dir.dirdata, entry, dir.pos);
	if(ret) dir.pos++;
	return ret;
}

bool fs_seek_dir(dir_handle &dir, size_t pos, bool relative){
	if(!dir.valid) return false;
	if(relative) dir.pos+=pos;
	else dir.pos=pos;
	return true;
}

directory_entry fs_stat(char *path){
	directory_entry ret;
	char *fspath=getfspath(path);
	if(!fspath){
		ret.valid=false;
		return ret;
	}
	fs_mountpoint &mount=getpathmount(path);
	if(!mount.valid){
		ret.valid=false;
		return ret;
	}
	return mount.driver.stat(mount.mountdata, fspath);
}
