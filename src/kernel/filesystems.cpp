#include "kernel.hpp"
#include "filesystems.hpp"
#include "ministl.hpp"
#include "locks.hpp"
#include "strutil.hpp"

map<string, fs_mountpoint> *fs_mounts;
map<string, fs_driver> *fs_drivers;

lock fs_lock;

static const fs_driver invalid_fs_driver={false, "", false, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL};
static const fs_mountpoint invalid_mountpoint={false, "", "", invalid_fs_driver, NULL};

char *fs_mounts_infofs(){
	char *buffer=(char*)malloc(4096);
	memset(buffer, 0, 4096);
	sprintf(buffer, "# name, device, filesystem\n");
	for(map<string, fs_mountpoint>::iterator i=fs_mounts->begin(); i!=fs_mounts->end(); ++i){
		sprintf(&buffer[strlen(buffer)], "%s, %s, %s\n", i->first.c_str(), i->second.device, i->second.driver.name);
	}
	return buffer;
}

void fs_init(){
	dbgout("FS: Init\n");
	init_lock(fs_lock);
    take_lock_exclusive(fs_lock);
	fs_mounts=new map<string, fs_mountpoint>();
	fs_drivers=new map<string, fs_driver>();
	release_lock(fs_lock);
	fs_registerfs(initfs_getdriver());
	fs_registerfs(devfs_getdriver());
	fs_mount("INIT", NULL, "INITFS");
	fs_mount("DEV", NULL, "DEVFS");
	directory_entry root=fs_stat("INIT:");
	if(!root.valid) panic("(FS) Cannot stat root of INIT:!\n");
	dbgpf("FS: Root size: %i, type: 0x%x.\n", root.size, root.type);
	dir_handle dir=fs_open_dir("INIT:", FS_Read);
	while(true){
		directory_entry entry=fs_read_dir(dir);
		if(!entry.valid) break;
		dbgpf("FS: %s %i 0x%x\n", entry.filename, entry.size, entry.type);
	}
	fs_close_dir(dir);
	infofs_register("MOUNTS", &fs_mounts_infofs);
}

fs_path *new_fs_path(const string &path, bool toupper=true){
	//dbgpf("FS: path:'%s'\n", path.c_str());
	string upath;
	if(toupper) upath=to_upper(path);
	else upath=path;
	string current_str="";
	fs_path *head=NULL;
	fs_path *current_node=NULL;
	for(size_t i=0; i<upath.length(); ++i){
		if(upath[i]==FS_PATH_SEPERATOR && current_str.length()>0){
			//dbgpf("FS: segment:'%s'\n", current_str.c_str());
			if(head==NULL){
				head=new fs_path();
				current_node=head;
			}else{
				fs_path *next=new fs_path();
            	current_node->next=next;
            	current_node=current_node->next;
			}
			current_node->next=NULL;
			current_node->str=new char[current_str.length()+1];
			strncpy(current_node->str, current_str.c_str(), current_str.length()+1);
			current_str="";
		}else{
			if(upath[i]!=FS_PATH_SEPERATOR) current_str+=upath[i];
		}
	}
	if(current_str!=""){
		//dbgpf("FS: segment:'%s'\n", current_str.c_str());
		if(head==NULL){
			head=new fs_path();
			current_node=head;
		}else{
			fs_path *next=new fs_path();
			current_node->next=next;
			current_node=current_node->next;
		}
		current_node->next=NULL;
		current_node->str=new char[current_str.length()+1];
		strncpy(current_node->str, current_str.c_str(), current_str.length()+1);
	}
	if(head==NULL){
		//dbgout("FS: empty path\n");
		head=new fs_path();
		head->str=new char[1];
		*(head->str)='\0';
	}
	return head;
}

void delete_fs_path(fs_path *p){
	if(p->next) delete_fs_path(p->next);
	delete[] p->str;
	delete p;
}

fs_driver &getfs(char *name){
	hold_lock hl(fs_lock);
	return (*fs_drivers)[name];
}

fs_mountpoint &getmount(char *name){
	hold_lock hl(fs_lock);
	if(fs_mounts->has_key(name)) return (*fs_mounts)[name];
	else return (fs_mountpoint&)invalid_mountpoint;
}

void fs_registerfs(const fs_driver &driver){
	hold_lock hl(fs_lock);
	string name=driver.name;
	(*fs_drivers)[name]=driver;
}

fs_mountpoint &getpathmount(char *path){
	char mountname[9]={0};
	string strpath=to_upper(path);
	path=(char*)strpath.c_str();
	for(int i=0; i<8 && path[i]!='\0' && path[i]!=':'; ++i){
		mountname[i]=path[i];
	}
	return getmount(mountname);
}

char *getfspath(char *path){
	char *ret=path;
	while(*ret++!='\0'){
		if(*ret==FS_DRIVE_SEPERATOR) return ++ret;
	}
	return NULL;
}

bool fs_mount(char *name, char *device, char *fs){
	dbgpf("FS: Mount %s on %s (%s).\n", device?device:"NULL", name, fs);
	string strname=to_upper(name);
	name=(char*)strname.c_str();
	fs_driver driver=getfs(fs);
	if(driver.valid){
		if(driver.needs_device){
			if(!device || device[0]=='\0') return false;
			if(!fs_stat(device).valid) return false;
		}
		void *mountdata=driver.mount(device);
		{	hold_lock hl(fs_lock);
			fs_mountpoint &mount=(*fs_mounts)[name];
			mount.valid=true;
			strncpy(mount.name, name, 9);
			mount.driver=driver;
			mount.mountdata=mountdata;
			strncpy(mount.device, device?device:"NULL", 255);
		}
		dbgpf("FS: Mounted %s on %s (%s).\n", device?device:"NULL", name, fs);
		return true;
	}else{
		dbgpf("FS: FS driver not found.\n");
	}
	return false;
}

bool fs_unmount(char *name){
	fs_mountpoint &mount=getmount(name);
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

file_handle fs_open(char *path, fs_mode_flags mode){
	dbgpf("FS: OPEN %s mode: %i.\n", path, mode);
	file_handle ret;
	char *fspath=getfspath(path);
	if(!fspath){
		dbgout("FS: Invalid path.\n");
		ret.valid=false;
		return ret;
	}
	fs_mountpoint &mount=getpathmount(path);
	if(!mount.valid){
		dbgout("FS: Invalid mount.\n");
		ret.valid=false;
		return ret;
	}
	fs_path *ppath=new_fs_path(fspath);
	void *filedata=mount.driver.open(mount.mountdata, ppath, mode);
	delete_fs_path(ppath);
	if(!filedata){
		dbgout("FS: Open failed in FS driver.\n");
		ret.valid=false;
		return ret;
	}
	ret.mount=new fs_mountpoint(mount);
	ret.filedata=filedata;
	ret.valid=true;
	ret.mode=mode;
	if(mode & FS_AtEnd){
		mount.driver.seek(filedata, 0xFFFFFFFF, false);
	}
	dbgpf("FS: Opened %s.\n", path);
	return ret;
}

bool fs_close(file_handle &file){
	if(!file.valid) return false;
	bool ret=file.mount->driver.close(file.filedata);
	if(ret) {
        amm_close(file);
        file.valid=false;
        delete file.mount;
        dbgout("FS: Closed a file.\n");
    }
	return ret;
}

size_t fs_read(file_handle &file, size_t bytes, char *buf){
	if(!file.valid || !(file.mode & FS_Read)) return -1;
	return file.mount->driver.read(file.filedata, bytes, buf);
}

size_t fs_write(file_handle &file, size_t bytes, char *buf){
	if(!file.valid || !(file.mode & FS_Write)) return 0;
	return file.mount->driver.write(file.filedata, bytes, buf);
}

size_t fs_seek(file_handle &file, int32_t pos, bool relative){
	return file.mount->driver.seek(file.filedata, pos, relative);
}

int fs_ioctl(file_handle &file, int fn, size_t bytes, char *buf){
	if(!file.valid) return false;
	return file.mount->driver.ioctl(file.filedata, fn, bytes, buf);
}

dir_handle fs_open_dir(char *path, fs_mode_flags mode){
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
	fs_path *ppath=new_fs_path(fspath);
	void *dirdata=mount.driver.open_dir(mount.mountdata, ppath, mode);
	delete_fs_path(ppath);
	if(!dirdata){
		dbgout("FS: Directory open failed in FS driver.\n");
		ret.valid=false;
		return ret;
	}
	ret.dirdata=dirdata;
	ret.mount=&mount;
	ret.valid=true;
	ret.mode=mode;
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
	if(!dir.valid || !(dir.mode & FS_Read)){
		ret.valid=false;
		return ret;
	}
	return dir.mount->driver.read_dir(dir.dirdata);
}

bool fs_write_dir(dir_handle &dir, directory_entry entry){
	if(!dir.valid || !(dir.mode & FS_Write)) return false;
	return dir.mount->driver.write_dir(dir.dirdata, entry);
}

size_t fs_seek_dir(dir_handle &dir, size_t pos, bool relative){
	return dir.mount->driver.dirseek(dir.dirdata, pos, relative);
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
	fs_path *ppath=new_fs_path(fspath);
	ret=mount.driver.stat(mount.mountdata, ppath);
	delete_fs_path(ppath);
	return ret;
}

void fs_flush(file_handle &file){
    if(!file.valid) return;
    file.mount->driver.flush(file.filedata);
    amm_flush(file);
}
