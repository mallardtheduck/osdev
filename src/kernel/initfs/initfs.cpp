#include "initfs.hpp"

struct initfs_handle{
	size_t fileindex;
	size_t pos;
	initfs_handle(size_t index, size_t p=0) : fileindex(index), pos(p) {}
};

#define fdata ((initfs_handle*)filedata)

struct initfs_dirhandle{
	size_t pos;
	initfs_dirhandle(size_t p=0) : pos(p) {}
};

#define ddata ((initfs_dirhandle*)dirdata)

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

void *initfs_open(void *, fs_path *path){
	dbgpf("INITFS: Open %s.\n", path->str);
	int files=initfs_getfilecount();
	for(int i=0; i<files; ++i){
		initfs_file file=initfs_getfile(i);
		if(strcmp(path->str, file.name)==0){
			return (void*)new initfs_handle(i);
		}
	}
	return NULL;
}

bool initfs_close(void *filedata){
	delete fdata;
	return true;
}

int initfs_read(void *filedata, size_t bytes, char *buf){
	initfs_file file=initfs_getfile(fdata->fileindex);
	if(fdata->pos > file.size) return 0;
	size_t j=0;
	for(size_t i=fdata->pos; i<file.size && j<bytes; ++i, ++j){
		buf[j]=file.data[i];
	}
	fdata->pos+=j;
	return j;
}

bool initfs_write(void *, size_t, char *){
	return false;
}

int initfs_ioctl(void *, int, size_t, char *){
	return 0;
}

void *initfs_open_dir(void *, fs_path *path){
	if(path->next != NULL) return NULL;
	return (void*)new initfs_dirhandle;
}
bool initfs_close_dir(void *dirdata){
	delete ddata;
	return true;
}

directory_entry initfs_read_dir(void *dirdata){
	directory_entry ret;
	if(ddata->pos>=initfs_getfilecount()){
		ret.valid=false;
		dbgout("INITFS: No such directory entry.\n");
		return ret;
	}
	initfs_file file=initfs_getfile(ddata->pos);
	strncpy(ret.filename, file.name, 255);
	ret.size=file.size;
	ret.type=FS_File;
	ret.valid=true;
	ddata->pos++;
	return ret;
}

bool initfs_write_dir(void *, directory_entry){
	return false;
}

directory_entry initfs_stat(void *, fs_path *path){
	dbgpf("INITFS: Stat '%s'.\n",path->str);
	if(*(path->str)=='\0'){
		dbgout("INITFS: Stat root.\n");
		directory_entry ret;
		ret.filename[0]='\0';
		ret.size=initfs_getfilecount();
		ret.type=FS_Directory;
		ret.valid=true;
		return ret;
	}else{
		int files=initfs_getfilecount();
		for(int i=0; i<files; ++i){
			initfs_file file=initfs_getfile(i);
			if(strcmp(path->str, file.name)==0){
				initfs_dirhandle dh(i);
				return initfs_read_dir(&dh);
			}
		}
		directory_entry ret;
		ret.valid=false;
		return ret;
	}
}

bool initfs_seek(void *filedata, int pos, bool relative){
	if(relative) fdata->pos+=pos;
	else fdata->pos=pos;
	return true;
}

bool initfs_dirseek(void *dirdata, int pos, bool relative){
	if(relative) ddata->pos+=pos;
	else ddata->pos=pos;
	return true;
}

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
  	bool (*seek)(void *filedata, int pos, bool relatiive);
  	int (*ioctl)(void *filedata, int fn, size_t bytes, char *buf);
  	void *(*open_dir)(void *mountdata, fs_path *path);
  	bool (*close_dir)(void *dirdata);
  	directory_entry (*read_dir)(void *dirdata);
  	bool (*write_dir)(void *dirdata, directory_entry entry);
  	bool (*dirseek)(void *dirdata, int pos, bool relative);
  	directory_entry (*stat)(void *mountdata, fs_path *path);
  };*/

fs_driver initfs_driver = {true, "INITFS", false,
	initfs_mount, initfs_unmount,
	initfs_open, initfs_close, initfs_read, initfs_write, initfs_seek, initfs_ioctl,
	initfs_open_dir, initfs_close_dir, initfs_read_dir, initfs_write_dir, initfs_dirseek,
	initfs_stat};

fs_driver initfs_getdriver(){
	int files=initfs_getfilecount();
	dbgpf("INITFS: Files in InitFS: %i\n", files);
	for(int i=0; i<files; ++i){
		initfs_file file=initfs_getfile(i);
		dbgpf("INITFS: '%s' %i bytes\n", file.name, file.size);
	}
	return initfs_driver;
}
