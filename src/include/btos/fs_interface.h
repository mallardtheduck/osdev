#ifndef _FS_INTERFACE_H
#define _FS_INTERFACE_H

static const char FS_PATH_SEPERATOR='/';
static const char FS_DRIVE_SEPERATOR=':';

#ifndef __cplusplus
#include <stdbool.h>
#include <stddef.h>
#else
#include <cstddef>
#endif

#ifdef __cplusplus
static const size_t BT_MAX_PATH=1024;
static const size_t BT_MAX_SEGLEN=256;
#else
#define BT_MAX_PATH 1024
#define BT_MAX_SEGLEN 256
#endif

typedef int64_t bt_filesize_t;

enum fs_item_types{
	FS_File=0x00,
	FS_Directory=0x01,
	FS_Link=0x02,
	FS_Device=0x10,

	FS_Invalid=0xFF,
};

#ifndef __cplusplus
typedef enum fs_item_types fs_item_types;
#endif


enum fs_mode_flags{
	FS_Read 	= 1,
	FS_Write	= 1 << 1,
	FS_AtEnd	= 1 << 2,
	FS_Create	= 1 << 3,
	FS_Delete	= 1 << 4,
	FS_Exclude	= 1 << 5,
	FS_Truncate = 1 << 6,
};

#ifndef __cplusplus
typedef enum fs_mode_flags fs_mode_flags;
#endif

#if defined(KERNEL) || defined(KERNEL_MODULE)
#define BT_DE_NAME directory_entry
#else
#define BT_DE_NAME bt_directory_entry
#endif

struct BT_DE_NAME{
	bool valid;
	uint64_t id;
	char filename[BT_MAX_SEGLEN];
	bt_filesize_t size;
	fs_item_types type;
};

#ifndef __cplusplus
typedef struct BT_DE_NAME BT_DE_NAME;
#endif

static const BT_DE_NAME invalid_directory_entry={false, 0, "", 0, FS_Invalid};

#undef BT_DE_NAME

struct fs_path{
	char *str;
	struct fs_path *next;
};

#ifndef __cplusplus
typedef struct fs_path fs_path;
#endif

enum fs_seek_flags{
	FS_Set			= 0,
	FS_Relative 	= 1,
	FS_Backwards 	= 1 << 1,
};

#if defined(KERNEL) || defined(KERNEL_MODULE)

struct fs_driver{
	bool valid;
	char *name;
	bool needs_device;
	void *(*mount)(char *device);
	bool (*unmount)(void *mountdata);
	void *(*open)(void *mountdata, fs_path *path, fs_mode_flags mode);
	bool (*close)(void *filedata);
	size_t (*read)(void *filedata, size_t bytes, char *buf);
	size_t (*write)(void *filedata, size_t bytes, char *buf);
	bt_filesize_t (*seek)(void *filedata, bt_filesize_t pos, uint32_t flags);
	bool (*setsize)(void *filedata, bt_filesize_t size);
	int (*ioctl)(void *filedata, int fn, size_t bytes, char *buf);
    void (*flush)(void *filedata);
	void *(*open_dir)(void *mountdata, fs_path *path, fs_mode_flags mode);
	bool (*close_dir)(void *dirdata);
	directory_entry (*read_dir)(void *dirdata);
	bool (*write_dir)(void *dirdata, directory_entry entry);
	size_t (*dirseek)(void *dirdata, size_t pos, uint32_t flags);
	directory_entry (*stat)(void *mountdata, fs_path *path);
	bool (*format)(char *device, void *options);
};

#ifndef __cplusplus
typedef struct fs_driver fs_driver;
#endif

struct fs_mountpoint{
	bool valid;
	char name[9];
	char device[255];
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
	fs_mode_flags mode;
};

#ifndef __cplusplus
typedef struct file_handle file_handle;
#endif

struct dir_handle{
	bool valid;
	fs_mountpoint *mount;
	void *dirdata;
	fs_mode_flags mode;
};

#ifndef __cplusplus
typedef struct dir_handle dir_handle;
#endif

#endif

#endif
