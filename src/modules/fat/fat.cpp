#include <btos_module.h>
class fatfs_format;
extern "C" {
    #include "fat_filelib.h"
}

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

lock fat_lock;
char devicepath[256];
file_handle *fh;
void *fatmagic=(void*)0xFA7F5;
bool mounted=false;

struct fat_file_handle{
	void *flh;
	fs_mode_flags mode;
	char path[BT_MAX_PATH];
	bool debug;
};

typedef struct fat_file_handle fat_file_handle;

struct fat_dir_handle{
	FL_DIR *fld;
	fs_mode_flags mode;
	char path[BT_MAX_PATH];
};

typedef struct fat_dir_handle fat_dir_handle;

void init_queue();
size_t fat_queued_read(void *flh, uint8_t *buf, size_t size);
size_t fat_queued_write(void *flh, uint8_t *buf, size_t size);
size_t fat_queued_seek(void *flh, uint32_t pos, int origin);

extern "C" int strncmp(const char* s1, const char* s2, size_t n)
{
    while(n--)
        if(*s1++!=*s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return 0;
}

extern "C" size_t strlen(const char *s) {
    size_t i;
    for (i = 0; s[i] != '\0'; i++) ;
    return i;
}

void fs_path_to_string(fs_path *path, char *buf){
	while(path){
		sprintf(&buf[strlen(buf)], "/%s", path->str);
		path=path->next;
	}
}

fs_path *fs_path_last_part(fs_path *path){
	while(true){
		if(path->next) path=path->next;
		else return path;
	}
}

void take_fat_lock(){
    take_lock_recursive(&fat_lock);
}

void release_fat_lock(){
    release_lock(&fat_lock);
}

int fat_device_read(uint32_t sector, uint8_t *buffer, uint32_t sector_count){
    take_fat_lock();
	size_t readaddr=sector*512;
	size_t readsize=sector_count*512;
	fseek(fh, readaddr, false);
	int ret=fread(fh, readsize, (char*)buffer);
    release_fat_lock();
    return ret;
}

int fat_device_write(uint32_t sector, uint8_t *buffer, uint32_t sector_count){
    take_fat_lock();
	size_t writeaddr=sector*512;
    size_t writesize=sector_count*512;
    fseek(fh, writeaddr, false);
    int ret=fwrite(fh, writesize, (char*)buffer);
    release_fat_lock();
    return ret;
}

void *fat_mount(char *device){
    take_fat_lock();
	if(mounted) {
        release_fat_lock();
        return NULL;
    }
	sprintf(devicepath, "%s", device);
	fh=fopen(devicepath, (fs_mode_flags)(FS_Read | FS_Write));
	fl_attach_media(&fat_device_read, &fat_device_write);
	mounted=true;
    release_fat_lock();
	return fatmagic;
}

bool fat_unmount(void *mountdata){
	if(mounted && mountdata==fatmagic){
        take_fat_lock();
		fl_shutdown();
        release_fat_lock();
		mounted=false;
		return true;
	} else return false;
}

void *fat_open(void *mountdata, fs_path *path, fs_mode_flags mode){
	if(mounted && mountdata==fatmagic){
		fat_file_handle *ret=new fat_file_handle();
		ret->debug = false;
		ret->mode=mode;
		mode=(fs_mode_flags)(mode & ~(FS_Delete | FS_Exclude));
		char spath[BT_MAX_PATH]={0};
		char *modifiers="";
		fs_path_to_string(path, spath);
		strncpy(ret->path, spath, BT_MAX_PATH);
		if(mode & FS_Truncate && mode & FS_AtEnd) mode = (fs_mode_flags)(mode & ~FS_AtEnd);
		if(mode==FS_Read) modifiers="r";
		if((mode & ~(FS_Create | FS_Truncate))==FS_Write ) modifiers="w";
		if(mode==(FS_Write | FS_AtEnd | FS_Create) || mode==(FS_Write | FS_AtEnd)) modifiers="a";
		if(mode==(FS_Read | FS_Write)) modifiers="r+";
		if(mode==(FS_Write | FS_Read | FS_Truncate | FS_Create)) modifiers="w+";
		if(mode==(FS_Write | FS_Read | FS_AtEnd | FS_Create)) modifiers="a+";
		if(mode==(FS_Read | FS_Write | FS_Create)) modifiers = "a+";
		dbgpf("FAT: Encoded flags: %s\n", modifiers);
		take_fat_lock();
		void *flh=fl_fopen(spath, modifiers);
		if(flh && mode==(FS_Read | FS_Write | FS_Create)){
			fl_fclose(flh);
			flh = fl_fopen(spath, "r+");
		}
		if(flh){
			ret->flh=flh;
		}else{
			free(ret);
            release_fat_lock();
			return NULL;
		}
		dbgpf("FAT: Opened %s (%p).\n", ((FL_FILE*)flh)->filename, ret);
        release_fat_lock();
		return ret;
	} else return NULL;
}

bool fat_close(void *filedata){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return false;
    take_fat_lock();
	fl_fclose(fd->flh);
	if(fd->mode & FS_Delete){
		fl_remove(fd->path);
	}
	dbgpf("FAT: Closed (%p).\n", fd);
	delete fd;
    release_fat_lock();
	return true;
}

size_t fat_read(void *filedata, size_t bytes, char *buf){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return 0;
	take_fat_lock();
	size_t pos=fl_ftell(fd->flh);
	int ret=fl_fread(buf, bytes, 1, fd->flh);
    release_fat_lock();
    /*size_t ret=fat_queued_read(fd->flh, (uint8_t*)buf, bytes);
    return ret;*/
	if(fd->debug) dbgpf("FAT: Read from (%p): got %i, %i requested at %i.\n", fd, (int)ret, (int)bytes, (int)pos);
	return (ret>=0)?ret:0;
}

size_t fat_write(void *filedata, size_t bytes, char *buf){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return 0;
	take_fat_lock();
	size_t pos=fl_ftell(fd->flh);
	int ret=fl_fwrite(buf, bytes, 1, fd->flh);
    release_fat_lock();
    /*size_t ret= fat_queued_write(fd->flh, (uint8_t*)buf, bytes);
    return ret;*/
	if(fd->debug) dbgpf("FAT: Write to (%p): put %i, %i requested at %i.\n", fd, (int)ret, (int)bytes, (int)pos);
	return (ret>=0)?ret:0;
}

bt_filesize_t fat_seek(void *filedata, bt_filesize_t pos, uint32_t flags){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return 0;
    take_fat_lock();
	
	int offset = (int)pos;
	int origin=SEEK_SET;
	if(flags & FS_Relative) origin=SEEK_CUR;
	if(flags & FS_Backwards) origin=SEEK_END;
	if(flags == (FS_Backwards | FS_Relative)){
		origin=SEEK_CUR;
		offset=-offset;
	}
	fl_fseek(fd->flh, offset, origin);
	size_t ret=fl_ftell(fd->flh);
	release_fat_lock();
	if(fd->debug) dbgpf("FAT: Seek in (%p): pos: %i flags: %x ret: %i.\n", fd, (int)pos, (int)flags, (int)ret);
    //size_t ret= fat_queued_seek(fd->flh, offset, origin);
    return ret;
}

bool fat_setsize(void *filedata, bt_filesize_t size){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return 0;
	take_fat_lock();
	dbgpf("FAT: SETSIZE @ %i\n", (int)size);
	//Do something?
	release_fat_lock();
	return true;
}

int fat_ioctl(void *filedata, int fn, size_t bytes, char *buf){
	return 0;
}

void fat_flush(void *filedata){
    take_fat_lock();
    fl_shutdown();
    release_fat_lock();
}

void *fat_open_dir(void *mountdata, fs_path *path, fs_mode_flags mode){
	if(mounted && mountdata==fatmagic){
        take_fat_lock();
		char spath[BT_MAX_PATH]={0};
		fs_path_to_string(path, spath);
		fat_dir_handle *ret=new fat_dir_handle();
		ret->mode=mode;
		strncpy(ret->path, spath, BT_MAX_PATH);
		ret->fld=(FL_DIR*)malloc(sizeof(FL_DIR));
		void *res=(void*)fl_opendir(spath, ret->fld);
		if(!res && (mode & FS_Create)){
			if(fl_createdirectory(spath)){
				res=(void*)fl_opendir(spath, ret->fld);
			}
		}
		if(!res){
			free(ret->fld);
			free(ret);
            release_fat_lock();
			return NULL;
		}
        release_fat_lock();
		return ret;
	}else return NULL;
}

bool fat_close_dir(void *dirdata){
	fat_dir_handle *dir=(fat_dir_handle*)dirdata;
	if(dir){
        take_fat_lock();
		fl_closedir(dir->fld);
		if(dir->mode & FS_Delete){
			void *fd=fl_fopen(dir->path, "a");
			fl_fclose(fd);
			int r=fl_remove(dir->path);
			dbgpf("FAT: Directory delete: %i\n", r);
		}
		free(dir->fld);
		delete dir;
        release_fat_lock();
		return true;
	} else return false;
}

directory_entry fat_read_dir(void *dirdata){
	fat_dir_handle *dir=(fat_dir_handle*)dirdata;
	if(dir){
        take_fat_lock();
		directory_entry ret;
		fl_dirent ent;
		int err = 0;
		while(!(err = fl_readdir(dir->fld, &ent)) && (strcmp(ent.filename, ".") == 0 || strcmp(ent.filename, "..") == 0));
		if(!err){
			ret.valid=true;
			strncpy(ret.filename, ent.filename, 255);
			ret.type=(ent.is_dir)?FS_Directory:FS_File;
			ret.size=ent.size;
			ret.id=ent.cluster;
            release_fat_lock();
            return ret;
		} else {
            release_fat_lock();
            return invalid_directory_entry;
        }
	} else return invalid_directory_entry;
}

bool fat_write_dir(void *dirdata, directory_entry entry){
	return false;
}

size_t fat_dirseek(void *dirdata, size_t pos, uint32_t flags){
	return 0;
}

directory_entry fat_stat(void *mountdata, fs_path *path){
	if(mounted && mountdata==fatmagic){
        take_fat_lock();
		char spath[BT_MAX_SEGLEN]={0};
		fs_path_to_string(path, spath);
		fs_item_types type=FS_Invalid;
		size_t filesize=0;
		uint64_t id = 0;
		void *flh=fl_fopen(spath, "r");
		if(flh){
			id = ((FL_FILE*)flh)->startcluster;
			type=FS_File;
			fl_fseek(flh, 0, SEEK_END);
			filesize=fl_ftell(flh);
			fl_fclose(flh);
		}else if(fl_is_dir(spath)){
			type=FS_Directory;
		}else {
			release_fat_lock();
			dbgpf("FAT: Could not stat '%s'\n", spath);
            return invalid_directory_entry;
        }

		directory_entry ret;
        ret.valid=true;
        fs_path *lastpart=fs_path_last_part(path);
        strncpy(ret.filename, lastpart->str, BT_MAX_SEGLEN);
        ret.type=type;
        ret.size=filesize;
		ret.id=id;
        release_fat_lock();
        return ret;
	}else return invalid_directory_entry;
}

bool fat_format(char *device, void*){
    take_fat_lock();
	if(mounted) {
		release_fat_lock();
		return false;
	}
	sprintf(devicepath, "%s", device);
	fh=fopen(devicepath, (fs_mode_flags)(FS_Read | FS_Write));
	if(!fh){
		release_fat_lock();
		return false;
	}
	bt_filesize_t fsize = fseek(fh, 0, FS_Backwards);
	uint32_t sectors = fsize / 512;
	dbgpf("FAT: Formatting %s, %i blocks (%i bytes).\n", device, sectors, (int)fsize);
	fl_attach_media(&fat_device_read, &fat_device_write);
	fl_format(sectors, "BT/OS FAT");
    release_fat_lock();
	return true;
}

fs_driver fat_driver={true, "FAT", true,
	fat_mount, fat_unmount, fat_open, fat_close, fat_read, fat_write, fat_seek, fat_setsize, fat_ioctl, fat_flush,
	fat_open_dir, fat_close_dir, fat_read_dir, fat_write_dir, fat_dirseek, fat_stat, fat_format};

extern "C" int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	init_lock(&fat_lock);
    init_queue();
	fl_init();
	fl_attach_locks(&take_fat_lock, &release_fat_lock);
	add_filesystem(&fat_driver);
    return 0;
}
