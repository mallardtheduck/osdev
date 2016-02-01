#include "initfs.hpp"
#include "ministl.hpp"
#include "strutil.hpp"

struct initfs_file{
	string name;
	unsigned char *data;
	size_t size;
};

struct tar_header{
    char filename[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char chksum[8];
    char typeflag[1];
};

vector<initfs_file> *initfs_data;

struct initfs_handle{
	size_t fileindex;
	size_t pos;
	initfs_handle(size_t index, size_t p=0) : fileindex(index), pos(p) {}
};

size_t tar_size(const char *in){
	size_t size = 0, j, count = 1;
	for (j = 11; j > 0; j--, count *= 8) size += ((in[j - 1] - '0') * count);
	return size;
}

#define fdata ((initfs_handle*)filedata)

struct initfs_dirhandle{
	size_t pos;
	initfs_dirhandle(size_t p=0) : pos(p) {}
};

#define ddata ((initfs_dirhandle*)dirdata)

size_t initfs_getfilecount(){
	return initfs_data->size();
}

initfs_file initfs_getfile(int index){
	return (*initfs_data)[index];
}

void *initfs_mount(char *){
	dbgout("INITFS: Mounted.\n");
	return (void*)1;
}

bool initfs_unmount(void *){
	return true;
}

void *initfs_open(void *, fs_path *path, fs_mode_flags){
	dbgpf("INITFS: Open %s.\n", path->str);
	int files=initfs_getfilecount();
	for(int i=0; i<files; ++i){
		initfs_file file=initfs_getfile(i);
		if(to_upper(file.name) == to_upper(path->str)){
			return (void*)new initfs_handle(i);
		}
	}
	return NULL;
}

bool initfs_close(void *filedata){
	delete (initfs_handle*)fdata;
	return true;
}

size_t initfs_read(void *filedata, size_t bytes, char *buf){
	initfs_file file=initfs_getfile(fdata->fileindex);
	if(fdata->pos > file.size) return 0;
    if(fdata->pos + bytes > file.size) bytes=file.size - fdata->pos;
	size_t j=0;
	for(size_t i=fdata->pos; i<file.size && j<bytes; ++i, ++j){
		buf[j]=file.data[i];
	}
	fdata->pos+=j;
	return j;
}

size_t initfs_write(void *, size_t, char *){
	return 0;
}

int initfs_ioctl(void *, int, size_t, char *){
	return 0;
}

void initfs_flush(void *){
}

void *initfs_open_dir(void *, fs_path *path, fs_mode_flags){
	if(path->next != NULL) return NULL;
	return (void*)new initfs_dirhandle;
}
bool initfs_close_dir(void *dirdata){
	delete (initfs_dirhandle*)ddata;
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
	strncpy(ret.filename, file.name.c_str(), 255);
	ret.id = (uint64_t)file.data;
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
		ret.id = 0;
		ret.size=initfs_getfilecount();
		ret.type=FS_Directory;
		ret.valid=true;
		return ret;
	}else{
		int files=initfs_getfilecount();
		for(int i=0; i<files; ++i){
			initfs_file file=initfs_getfile(i);
			if(to_upper(file.name) == to_upper(path->str)){
				initfs_dirhandle dh(i);
				return initfs_read_dir(&dh);
			}
		}
		directory_entry ret;
		ret.valid=false;
		return ret;
	}
}

size_t initfs_seek(void *filedata, size_t pos, uint32_t flags){
	if(flags & FS_Relative) fdata->pos+=pos;
	else if(flags & FS_Backwards){
		initfs_file file=initfs_getfile(fdata->fileindex);
		fdata->pos = file.size - pos;
	} else if(flags == (FS_Backwards | FS_Relative)) fdata->pos-=pos;
	else fdata->pos=pos;
	return fdata->pos;
}

size_t initfs_dirseek(void *dirdata, size_t pos, uint32_t flags){
	if(flags & FS_Relative) ddata->pos+=pos;
	else if(flags & FS_Backwards){
		ddata->pos = initfs_getfilecount() - pos;
	} else if(flags == (FS_Backwards | FS_Relative)) ddata->pos-=pos;
	else ddata->pos=pos;
	return ddata->pos;
}

fs_driver initfs_driver = {true, "INITFS", false,
	initfs_mount, initfs_unmount,
	initfs_open, initfs_close, initfs_read, initfs_write, initfs_seek, initfs_ioctl, initfs_flush,
	initfs_open_dir, initfs_close_dir, initfs_read_dir, initfs_write_dir, initfs_dirseek,
	initfs_stat};

fs_driver initfs_getdriver(){
	if(!initfs_data){
		initfs_data = new vector<initfs_file>();
		multiboot_info_t *mbi = vmm_get_multiboot();
		if(mbi->mods_count > 0){
			module_t *mod = (module_t *)mbi->mods_addr;
			tar_header *th = (tar_header*)mod->mod_start;
			dbgpf("INITFS: Module starts at %x and ends at %x\n", mod->mod_start, mod->mod_end);
			while((uint32_t)th < mod->mod_end){
				if(th->filename[0] == '\0') break;
				unsigned char *data = (unsigned char*)((uint32_t)th + 512);
				size_t size = tar_size(th->size);
				dbgpf("INITFS: %s, %x, %i\n", th->filename, data, size);
				initfs_file file;
				file.data = data;
				file.name = th->filename;
				file.size = size;
				initfs_data->push_back(file);
				th = (tar_header*)((uint32_t) data + ((size & ~511) + 512));
			}
		}else{
			panic("(INITFS) No tar module loaded!");
		}
	}
	return initfs_driver;
}
