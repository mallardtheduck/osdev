#include "module_stubs.h"
#include "fat_filelib.h"

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

#pragma GCC diagnostic ignored "-Wunused-parameter"

lock fat_lock;
int fat_lockcount=0;
char devicepath[256];
file_handle *fh;
void *fatmagic=(void*)0xFA7F5;
bool mounted=false;

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
	if(!fat_lockcount) take_lock(&fat_lock);
	fat_lockcount++;
}

void release_fat_lock(){
	fat_lockcount--;
	if(!fat_lockcount) release_lock(&fat_lock);
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
    return fread(fh, writesize, (char*)buffer);
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
		char spath[255]={0};
		char *modifiers;
		fs_path_to_string(path, spath);
		if(mode==FS_Read) modifiers="r";
		if(mode==FS_Write) modifiers="w";
		if(mode==(FS_Read | FS_Write)) modifiers="r+";
		return fl_fopen(spath, modifiers);
	} else return NULL;
}

bool fat_close(void *filedata){
	fl_fclose(filedata);
	return true;
}

size_t fat_read(void *filedata, size_t bytes, char *buf){
	int ret=fl_fread(buf, bytes, 1, filedata);
	return (ret>=0)?ret:0;
}

size_t fat_write(void *filedata, size_t bytes, char *buf){
	int ret=fl_fwrite(buf, bytes, 1, filedata);
	return (ret>=0)?ret:0;
}

size_t fat_seek(void *filedata, int pos, bool relative){
	int origin=SEEK_SET;
	if(relative) origin=SEEK_CUR;
	return fl_fseek(filedata, pos, origin);
}

int fat_ioctl(void *filedata, int fn, size_t bytes, char *buf){
	return 0;
}

void *fat_open_dir(void *mountdata, fs_path *path, fs_mode_flags mode){
	if(mounted && mountdata==fatmagic){
		char spath[255]={0};
		fs_path_to_string(path, spath);
		FL_DIR *dir=(FL_DIR*)malloc(sizeof(FL_DIR));
		return (void*)fl_opendir(spath, dir);
	}else return NULL;
}

bool fat_close_dir(void *dirdata){
	if(dirdata){
		fl_closedir((FL_DIR*)dirdata);
		free(dirdata);
		return true;
	} else return false;
}

directory_entry fat_read_dir(void *dirdata){
	if(dirdata){
		directory_entry ret;
		fl_dirent ent;
		if(!fl_readdir((FL_DIR*)dirdata, &ent)){
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
	add_filesystem(&fat_driver);
    return 0;
}