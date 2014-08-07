#ifndef _FS_INTERFACE_H
#define _FS_INTERFACE_H

const char FS_PATH_SEPERATOR='/';
const char FS_DRIVE_SEPERATOR=':';

#ifndef __cplusplus
#include <stdbool.h>
#endif

enum fs_item_types{
	FS_File=0x00,
	FS_Directory=0x01,
	FS_Link=0x02,
	FS_Device=0x10,
};

#ifndef __cplusplus
typedef enum fs_item_types fs_item_types;
#endif

struct directory_entry{
	bool valid;
	char filename[255];
	size_t size;
	fs_item_types type;
};

#ifndef __cplusplus
typedef struct directory_entry directory_entry;
#endif

struct fs_path{
	char *str;
	struct fs_path *next;
};

#ifndef __cplusplus
typedef struct fs_path fs_path;
#endif

#if defined(KERNEL) || defined(KERNEL_MODULE)

struct fs_driver{
	bool valid;
	char name[9];
	bool needs_device;
	void *(*mount)(char *device);
	bool (*unmount)(void *mountdata);
	void *(*open)(void *mountdata, fs_path *path);
	bool (*close)(void *filedata);
	int (*read)(void *filedata, size_t bytes, char *buf);
	bool (*write)(void *filedata, size_t bytes, char *buf);
	size_t (*seek)(void *filedata, int pos, bool relative);
	int (*ioctl)(void *filedata, int fn, size_t bytes, char *buf);
	void *(*open_dir)(void *mountdata, fs_path *path);
	bool (*close_dir)(void *dirdata);
	directory_entry (*read_dir)(void *dirdata);
	bool (*write_dir)(void *dirdata, directory_entry entry);
	size_t (*dirseek)(void *dirdata, int pos, bool relative);
	directory_entry (*stat)(void *mountdata, fs_path *path);
};

#ifndef __cplusplus
typedef struct fs_driver fs_driver;
#endif

struct fs_mountpoint{
	bool valid;
	char name[9];
	fs_driver driver;
	void *mountdata;
};

#ifndef __cplusplus
typedef struct fs_mountpoint fs_mountpoint;
#endif

struct file_handle{
	bool valid;
	fs_mountpoint *mount;
	void *filedata;
};

#ifndef __cplusplus
typedef struct file_handle file_handle;
#endif

struct dir_handle{
	bool valid;
	fs_mountpoint *mount;
	void *dirdata;
};

#ifndef __cplusplus
typedef struct dir_handle dir_handle;
#endif

#endif

#endif
