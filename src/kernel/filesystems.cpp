#include "kernel.hpp"
#include "fs_interface.hpp"

#define FS_MAX 64

fs_mountpoint fs_mounts[FS_MAX] = {0};
fs_driver fs_drivers[FS_MAX] = {0};

void fs_init(){
	dbgout("FS: Init\n");
	fs_drivers[0]=initfs_getdriver();
	fs_mount("INIT", NULL, "INITFS");
	printf("FS: Mounted INITFS on INIT:\n");
	directory_entry root=fs_stat("INIT:");
	if(!root.valid) panic("(FS) Cannot stat root of INIT:!\n");
	dbgpf("FS: Root size: %i, type: 0x%x.\n", root.size, root.type);
	dir_handle dir=fs_open_dir("INITFS:");
	while(true){
		directory_entry entry=fs_read_dir(dir);
		if(!entry.valid) break;
		dbgpf("FS: %s %i 0x%x\n", entry.filename, entry.size, entry.type);
	}
	fs_close_dir(dir);
}

fs_driver *getfs(char *name){
	int i=0;
	while(fs_drivers[i].valid){
		if(strcmp(name, fs_drivers[i].name)==0){
			return &fs_drivers[i];
		}
		++i;
	}
	return NULL;
}

int getmount(char *name){
	int i=FS_MAX;
	while(i > -1 && strcmp(fs_mounts[i].name, name) != 0) --i;
	return i;
}

int getfreemount(){
	int i=0;
	while(i < FS_MAX && fs_mounts[i].valid) ++i;
	return i;
}

int getpathmount(char *path){
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
	fs_driver *driver=getfs(fs);
	if(driver && driver->valid){
		if(driver->needs_device){
			//TODO: Device drivers...
			return false;
		}else{
			fs_mountpoint &mount=fs_mounts[getfreemount()];
			mount.valid=true;
			strncpy(mount.name, name, 9);
			mount.driver=driver;
			mount.mountdata=driver->mount(device);
			dbgpf("FS: Mounted %s on %s (%s).\n", device?device:"NULL", name, fs);
		}
	}
	return false;
}

bool fs_unmount(char *name){
	int mountid=getmount(name);
	if(mountid<0) return false;
	fs_mountpoint &mount=fs_mounts[mountid];
	//TODO: Check for open files...
	mount.driver->unmount(mount.mountdata);
	mount.valid=false;
	dbgpf("FS: Unmounted %s.\n", name);
	return true;
}

file_handle fs_open(char *path){
	dbgpf("FS: OPEN %s.\n", path);
	file_handle ret;
	int mountid=getpathmount(path);
	char *fspath=getfspath(path);
	if(mountid<0 || !fspath){
		ret.valid=false;
		return ret;
	}
	fs_mountpoint &mount=fs_mounts[mountid];
	void *filedata=mount.driver->open(mount.mountdata, fspath);
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
	bool ret=file.mount->driver->close(file.filedata);
	if(ret) dbgout("FS: Closed a file.\n");
	return ret;
}

int fs_read(file_handle &file, size_t bytes, char *buf){
	if(!file.valid) return -1;
	int read=file.mount->driver->read(file.filedata, file.pos, bytes, buf);
	file.pos+=read;
	return read;
}

bool fs_write(file_handle &file, size_t bytes, char *buf){
	if(!file.valid) return false;
	bool ok=file.mount->driver->read(file.filedata, file.pos, bytes, buf);
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
	return file.mount->driver->ioctl(file.filedata, fn, bytes, buf);
}

dir_handle fs_open_dir(char *path){
	dir_handle ret;
	int mountid=getpathmount(path);
	char *fspath=getfspath(path);
	if(mountid<0 || !fspath){
		ret.valid=false;
		return ret;
	}
	fs_mountpoint &mount=fs_mounts[mountid];
	void *dirdata=mount.driver->open_dir(mount.mountdata, fspath);
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
	bool ret=dir.mount->driver->close_dir(dir.dirdata);
	if(ret) dbgout("FS: Closed a directory.\n");
	return ret;
}

directory_entry fs_read_dir(dir_handle &dir){
	directory_entry ret;
	if(!dir.valid){
		ret.valid=false;
		return ret;
	}
	ret=dir.mount->driver->read_dir(dir.dirdata, dir.pos);
	if(ret.valid) dir.pos++;
	return ret;
}

bool fs_write_dir(dir_handle &dir, directory_entry entry){
	if(!dir.valid) return false;
	bool ret=dir.mount->driver->write_dir(dir.dirdata, entry, dir.pos);
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
	int mountid=getpathmount(path);
	char *fspath=getfspath(path);
	if(mountid<0 || !fspath){
		ret.valid=false;
		return ret;
	}
	fs_mountpoint &mount=fs_mounts[mountid];
	return mount.driver->stat(mount.mountdata, fspath);
}
