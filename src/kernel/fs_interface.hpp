#ifndef _FS_INTERFACE_HPP
#define _FS_INTERFACE_HPP

#include "kernel.hpp"

namespace direntry_types{
	enum Enum{
		File=0x00,
		Directory=0x01,
		Symlink=0x02,
		Device=0x10,
	};	
};

struct directory_entry{
	bool valid;
	char filename[255];
	size_t size;
	direntry_types::Enum type;	
};

struct fs_driver{
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
};

struct fs_mountpoint{
	bool valid;
	char name[9];
	fs_driver *driver;
	void *mountdata;
};

struct file_handle{
	bool valid;
	fs_mountpoint *mount;
	void *filedata;
	size_t pos;
};

struct dir_handle{
	bool valid;
	fs_mountpoint *mount;
	void *dirdata;
	size_t pos;
};

#endif
