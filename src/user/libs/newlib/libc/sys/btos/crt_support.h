#ifndef _CRT_SUPPORT_H
#define _CRT_SUPPORT_H

#include <btos.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#define HANDLE_NULL 0
#define HANDLE_OS 1
#define HANDLE_VIRT 2

struct virtual_handle{
	int type;
	union{
		struct{
			bt_handle_t handle;
			char path[BT_MAX_PATH + 1];
		} os;
		struct{
			void *data;
			int (*close)(void*);
			int (*isatty)(void*);
			off_t (*lseek)(void*, off_t, int);
			int (*read)(void*, char*, int);
			int (*write)(void*, char*, int);
			int (*fsync)(void*);
		}virt;
	};
};

#ifndef __cplusplus
typedef struct virtual_handle virtual_handle;
#endif

bool btos_path_parse(const char *opath, char *buffer, size_t size);
bool btos_path_is_absolute(const char *path);
bool btos_path_is_root(const char *path);
size_t btos_get_drive_end(const char *path);
int btos_set_filenum(bt_handle fh, const char *path);
int btos_set_filenum_virt(virtual_handle *vh);
bt_handle_t btos_get_handle(int fd);
virtual_handle *btos_get_handle_virt(int fd);
void btos_set_specific_filenum(int fd, bt_handle fh, const char *path);
void btos_set_specific_filenum_virt(int fd, virtual_handle *vh);
void btos_remove_filenum(int fd);
void btos_open_std_streams();

#ifdef __cplusplus
};
#endif

#endif
