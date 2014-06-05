#include "initfs.hpp"

size_t initfs_getfilecount(){
	size_t ret=0;
	while(initfs_data[++ret].valid);
	return ret;
}

initfs_file initfs_getfile(int index){
	return initfs_data[index];
}

void *initfs_mount(char *){
	dbgout("INITFS: Mounted.\n");
	return (void*)1;
}

bool initfs_unmount(void *){
	return true;
}

void *initfs_open(void *, char *path){
	dbgpf("INITFS: Open %s.\n", path);
	int files=initfs_getfilecount();
	for(int i=0; i<files; ++i){
		initfs_file file=initfs_getfile(i);
		if(strcmp(path, file.name)==0){
			return (void*)i;
		}
	}
	return NULL;
}

bool initfs_close(void *){
	return true;
}

int initfs_read(void *filedata, size_t pos, size_t bytes, char *buf){
	initfs_file file=initfs_getfile((int)filedata);
	if(pos > file.size) return 0;
	size_t j=0;
	for(size_t i=pos; i<file.size && j<bytes; ++i, ++j){
		buf[j]=file.data[i];
	}
	return j;
}

bool initfs_write(void *, size_t, size_t, char *){
	return false;
}

int initfs_ioctl(void *, int, size_t, char *){
	return 0;
}

void *initfs_open_dir(void *, char *path){
	if(path[0] != '\0') return NULL;
	return (void*)1;
}
bool initfs_close_dir(void *dirdata){
	if(dirdata!=(void*)1)return false;
	return true;
}

directory_entry initfs_read_dir(void *dirdata, size_t pos){
	directory_entry ret;
	if(dirdata!=(void*)1){
		ret.valid=false;
		return ret;
	}
	if(pos>=initfs_getfilecount()){
		ret.valid=false;
		dbgout("INITFS: No such directory entry.\n");
		return ret;
	}
	initfs_file file=initfs_getfile(pos);
	strncpy(ret.filename, file.name, 255);
	ret.size=file.size;
	ret.type=direntry_types::File;
	ret.valid=true;
	return ret;
}

bool initfs_write_dir(void *, directory_entry, size_t){
	return false;
}

directory_entry initfs_stat(void *, char *path){
	dbgpf("INITFS: Stat '%s'.\n", path);
	if(path[0]=='\0'){
		dbgout("INITFS: Stat root.\n");
		directory_entry ret;
		ret.filename[0]='\0';
		ret.size=initfs_getfilecount();
		ret.type=direntry_types::Directory;
		ret.valid=true;
		return ret;
	}else{
		int files=initfs_getfilecount();
		for(int i=0; i<files; ++i){
			initfs_file file=initfs_getfile(i);
			if(strcmp(path, file.name)==0){
				return initfs_read_dir((void*)1, i);
			}
		}
		directory_entry ret;
		ret.valid=false;
		return ret;
	}
}

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

fs_driver initfs_driver = {true, "INITFS", false, initfs_mount, initfs_unmount, initfs_open, initfs_close, initfs_read, initfs_write, initfs_ioctl, initfs_open_dir, initfs_close_dir, initfs_read_dir, initfs_write_dir, initfs_stat}; 

fs_driver initfs_getdriver(){
	int files=initfs_getfilecount();
	dbgpf("INITFS: Files in InitFS: %i\n", files);
	for(int i=0; i<files; ++i){
		initfs_file file=initfs_getfile(i);
		dbgpf("INITFS: '%s' %i bytes\n", file.name, file.size);
	}
	return initfs_driver;
}
