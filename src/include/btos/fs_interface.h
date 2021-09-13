#ifndef _FS_INTERFACE_H
#define _FS_INTERFACE_H

static const char FS_PATH_SEPARATOR='/';
static const char FS_DRIVE_SEPARATOR=':';

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

	FS_WriteFlags = FS_Write | FS_Truncate | FS_Delete | FS_Create,
	FS_ReadOnlyFlags = ~FS_WriteFlags,
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

enum fs_seek_flags{
	FS_Set			= 0,
	FS_Relative 	= 1,
	FS_Backwards 	= 1 << 1,
};

#endif
