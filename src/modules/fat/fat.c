#include "module_stubs.h"
#include "fat_filelib.h"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

lock fat_lock, super_lock;
int fat_lockcount=0;
char devicepath[256];
file_handle *fh;
void *fatmagic=(void*)0xFA7F5;
bool mounted=false;

struct fat_file_handle{
	void *flh;
	fs_mode_flags mode;
	char path[BT_MAX_PATH];
};

typedef struct fat_file_handle fat_file_handle;

struct fat_dir_handle{
	FL_DIR *fld;
	fs_mode_flags mode;
	char path[BT_MAX_PATH];
};

typedef struct fat_dir_handle fat_dir_handle;

int strncmp(const char* s1, const char* s2, size_t n)
{
    while(n--)
        if(*s1++!=*s2++)
            return *(unsigned char*)(s1 - 1) - *(unsigned char*)(s2 - 1);
    return 0;
}

size_t strlen(const char *s) {
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

void take_fat_lock(){
	take_lock(&super_lock);
	if(fat_lock==thread_id() || !fat_lockcount){
		if(!fat_lockcount) take_lock(&fat_lock);
		fat_lockcount++;
	}else{
		release_lock(&super_lock);
		take_lock(&fat_lock);
		take_lock(&super_lock);
        fat_lockcount++;
	}
	release_lock(&super_lock);
}

void release_fat_lock(){
	take_lock(&super_lock);
	if(fat_lock==thread_id()){
		fat_lockcount--;
		if(!fat_lockcount) release_lock(&fat_lock);
	}else{
		panic("(FAT) Lock being released by wrong thread!");
	}
	release_lock(&super_lock);
}

int fat_device_read(uint32_t sector, uint8_t *buffer, uint32_t sector_count){
	size_t readaddr=sector*512;
	size_t readsize=sector_count*512;
	fseek(fh, readaddr, false);
	return fread(fh, readsize, (char*)buffer);
}

int fat_device_write(uint32_t sector, uint8_t *buffer, uint32_t sector_count){
	size_t writeaddr=sector*512;
    size_t writesize=sector_count*512;
    fseek(fh, writeaddr, false);
    return fwrite(fh, writesize, (char*)buffer);
}

void *fat_mount(char *device){
	if(mounted) return NULL;
	sprintf(devicepath, "%s", device);
	fh=fopen(devicepath, FS_Read | FS_Write);
	fl_init();
	fl_attach_locks(&take_fat_lock, &release_fat_lock);
	fl_attach_media(&fat_device_read, &fat_device_write);
	mounted=true;
	return fatmagic;
}

bool fat_unmount(void *mountdata){
	if(mounted && mountdata==fatmagic){
		fl_shutdown();
		mounted=false;
		return true;
	} else return false;
}

void *fat_open(void *mountdata, fs_path *path, fs_mode_flags mode){
	if(mounted && mountdata==fatmagic){
		fat_file_handle *ret=malloc(sizeof(fat_file_handle));
		ret->mode=mode;
		mode=mode & ~(FS_Delete | FS_Exclude);
		char spath[BT_MAX_PATH]={0};
		char *modifiers="";
		fs_path_to_string(path, spath);
		strncpy(ret->path, spath, BT_MAX_PATH);
		if(mode==FS_Read) modifiers="r";
		if((mode & ~(FS_Create | FS_Truncate))==FS_Write ) modifiers="w";
		if(mode==(FS_Write | FS_AtEnd | FS_Create)) modifiers="a";
		if(mode==(FS_Read | FS_Write)) modifiers="r+";
		if(mode==(FS_Write | FS_Read | FS_Truncate | FS_Create)) modifiers="w+";
		if(mode==(FS_Write | FS_Read | FS_AtEnd | FS_Create)) modifiers="a+";
		dbgpf("FAT: Encoded flags: %s\n", modifiers);
		void *flh=fl_fopen(spath, modifiers);
		if(flh)	ret->flh=flh;
		else{
			free(ret);
			return NULL;
		}
		dbgpf("FAT: Opened %s.\n", ((FL_FILE*)flh)->filename);
		return ret;
	} else return NULL;
}

bool fat_close(void *filedata){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return false;
	fl_fclose(fd->flh);
	if(fd->mode & FS_Delete){
		fl_remove(fd->path);
	}
	free(fd);
	return true;
}

size_t fat_read(void *filedata, size_t bytes, char *buf){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return 0;
	int ret=fl_fread(buf, bytes, 1, fd->flh);
	return (ret>=0)?ret:0;
}

size_t fat_write(void *filedata, size_t bytes, char *buf){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return 0;
	int ret=fl_fwrite(buf, bytes, 1, fd->flh);
	return (ret>=0)?ret:0;
}

size_t fat_seek(void *filedata, int pos, bool relative){
	fat_file_handle *fd=(fat_file_handle*)filedata;
	if(!fd) return 0;
	int origin=SEEK_SET;
	if(relative) origin=SEEK_CUR;
	fl_fseek(fd->flh, pos, origin);
	return fl_ftell(fd->flh);
}

int fat_ioctl(void *filedata, int fn, size_t bytes, char *buf){
	return 0;
}

void *fat_open_dir(void *mountdata, fs_path *path, fs_mode_flags mode){
	if(mounted && mountdata==fatmagic){
		char spath[BT_MAX_PATH]={0};
		fs_path_to_string(path, spath);
		fat_dir_handle *ret=malloc(sizeof(fat_dir_handle));
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
			return NULL;
		}
		return ret;
	}else return NULL;
}

bool fat_close_dir(void *dirdata){
	fat_dir_handle *dir=(fat_dir_handle*)dirdata;
	if(dir){
		fl_closedir(dir->fld);
		if(dir->mode & FS_Delete){
			void *fd=fl_fopen(dir->path, "a");
			fl_fclose(fd);
			int r=fl_remove(dir->path);
			dbgpf("FAT: Directory delete: %i\n", r);
		}
		free(dir->fld);
		free(dir);
		return true;
	} else return false;
}

directory_entry fat_read_dir(void *dirdata){
	fat_dir_handle *dir=(fat_dir_handle*)dirdata;
	if(dir){
		directory_entry ret;
		fl_dirent ent;
		if(!fl_readdir(dir->fld, &ent)){
			ret.valid=true;
			strncpy(ret.filename, ent.filename, 255);
			ret.type=(ent.is_dir)?FS_Directory:FS_File;
			ret.size=ent.size;
			return ret;
		} else return invalid_directory_entry;
	} else return invalid_directory_entry;
}

bool fat_write_dir(void *dirdata, directory_entry entry){
	return false;
}

size_t fat_dirseek(void *dirdata, int pos, bool relative){
	return 0;
}

directory_entry fat_stat(void *mountdata, fs_path *path){
	if(mounted && mountdata==fatmagic){
		char spath[255]={0};
		fs_path_to_string(path, spath);
		fs_item_types type=FS_Invalid;
		void *flh=fl_fopen(spath, "r");
		if(flh){
			type=FS_File;
			fl_fclose(flh);
		}else if(fl_is_dir(spath)){
			type=FS_Directory;
		}else return invalid_directory_entry;

		directory_entry ret;
        ret.valid=true;
        strncpy(ret.filename, spath, 255);
        ret.type=type;
        ret.size=0;
        return ret;
	}else return invalid_directory_entry;
}

fs_driver fat_driver={true, "FAT", true,
	fat_mount, fat_unmount, fat_open, fat_close, fat_read, fat_write, fat_seek, fat_ioctl,
	fat_open_dir, fat_close_dir, fat_read_dir, fat_write_dir, fat_dirseek, fat_stat};

int module_main(syscall_table *systbl, char *params){
	SYSCALL_TABLE=systbl;
	init_lock(&fat_lock);
	init_lock(&super_lock);
	add_filesystem(&fat_driver);
    return 0;
}