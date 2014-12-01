#ifndef _BTOS_API_H
#define _BTOS_API_H

#ifndef KERNEL
#include <stddef.h>
#include <stdint.h>
#endif

#include "fs_interface.h"

#ifdef __cplusplus
namespace btos_api{
#endif

typedef uint32_t bt_handle;
typedef bt_handle bt_lockhandle;
typedef bt_handle bt_filehandle;
typedef bt_handle bt_dirhandle;
typedef bt_handle bt_threadhandle;

typedef uint32_t bt_pid;
typedef uint32_t bt_priority;

enum{
	BT_ALLOC_PAGES		= 0x0101,
	BT_FREE_PAGES		= 0x0102,
    BT_ALLOC_AT         = 0x0103,
    BT_GUARD_PAGE       = 0x0104,
    BT_PF_HANDLE        = 0x0105,
    BT_SET_PAGEFLAGS    = 0x0106,
    BT_CLOSEHANDLE      = 0x0107,

	BT_GET_ARGC			= 0x0111,
	BT_GET_ARG			= 0x0112,

	BT_CREATE_LOCK		= 0x0201,
	BT_LOCK				= 0x0202,
	BT_TRY_LOCK			= 0x0203,
	BT_UNLOCK			= 0x0204,
	BT_DESTROY_LOCK		= 0x0205,

	BT_NEW_THREAD		= 0x0301,
	BT_WAIT_THREAD		= 0x0302,
	BT_THREAD_STATUS	= 0x0303,
	BT_BLOCK_THREAD		= 0x0304,
	BT_UNBLOCK_THREAD	= 0x0305,
	BT_GET_THREAD		= 0x0306,
	BT_END_THREAD		= 0x0307,
	BT_YIELD			= 0x0308,
	BT_THREAD_PRIORITIZE= 0x0309,
    BT_THREAD_ABORT     = 0x030A,

	BT_MOUNT			= 0x0401,
	BT_UNMOUNT			= 0x0402,

	BT_FOPEN			= 0x0501,
	BT_FCLOSE			= 0x0502,
	BT_FWRITE			= 0x0503,
	BT_FREAD			= 0x0504,
	BT_FIOCTL			= 0x0505,
	BT_FSEEK			= 0x0506,
    BT_FFLUSH           = 0x0507,
    BT_MMAP             = 0x0508,
	BT_DOPEN			= 0x0510,
	BT_DCLOSE			= 0x0511,
	BT_DWRITE			= 0x0512,
	BT_DREAD			= 0x0513,
	BT_DSEEK			= 0x0514,
	BT_STAT				= 0x0520,

	BT_LOAD_MODULE		= 0x0601,

	BT_GETENV			= 0x0701,
	BT_SETENV			= 0x0702,

	BT_SPAWN			= 0x0801,
	BT_WAIT				= 0x0802,
	BT_KILL				= 0x0803,
	BT_PRIORITIZE		= 0x0804,
	BT_EXIT				= 0x0805,
	BT_GETPID			= 0x0806,

	BT_SEND				= 0x0901,
	BT_RECV				= 0x0902,
	BT_CONTENT			= 0x0903,
	BT_ACK				= 0x0904,
	BT_SUBSCRIBE		= 0x0905,
	BT_MSGWAIT			= 0x0906,

	BT_QUERY_EXT		= 0x0F01,
};

struct bt_buffer{
	size_t size;
	char *buffer;
};

#ifndef __cplusplus
typedef struct bt_buffer bt_fioctl_buffer;
typedef struct bt_buffer bt_mmap_buffer;
#else
typedef bt_buffer bt_fioctl_buffer;
typedef bt_buffer bt_mmap_buffer;
#endif

#ifdef __cplusplus
}
#endif

#endif
