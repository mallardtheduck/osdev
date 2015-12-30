/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <btos.h>
#include <module/drivers.h>
#include "crt_support.h"

char *__env[1] = { 0 };
char **environ = __env;

static bt_pid lastchild=0;

void _exit(){
	bt_exit(0);
}

int close(int file){
    bt_handle h=btos_get_handle(file);
    int ret=bt_fclose(h);
    if(ret) btos_remove_filenum(file);
    return ret;
}

int execve(char *name, char **argv, char **env){
    size_t i=0;
    if(argv){
        while(argv[i]) ++i;
    }
    lastchild=bt_spawn(name, i, argv);
    if(!lastchild) return -1;
    return lastchild;
}

int fork() {
    errno=EAGAIN;
    return -1;
}

int fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int getpid(){
    return bt_getpid();
}

int isatty(int file){
    bt_filehandle fh=btos_get_handle(file);
    if(fh){
        size_t type=bt_fioctl(fh, bt_ioctl_DevType, 0, NULL);
        if(type==TERMINAL) return 1;
    }
    return 0;
}

int kill(int pid, int sig){
    if(sig == 9){
    	bt_kill(pid);
    	return 0;
    }
    else{
    	errno = EINVAL;
    	return -1;
    }
}

int link(char *old, char *new){
    errno=EMLINK;
    return -1;
}

int lseek(int file, int ptr, int dir){
	uint32_t flags = 0;
    if(dir==SEEK_CUR){ 
		flags = FS_Relative;
		if(ptr < 0){ 
			flags |= FS_Backwards;
			ptr = -ptr;
		}
	}
	else if(dir==SEEK_END) flags = FS_Backwards;
    return bt_fseek(btos_get_handle(file), ptr, flags);
}

int open(const char *name, int flags, ...){
    fs_mode_flags mode=FS_Read;
    if(flags & O_WRONLY) mode &= ~FS_Read;
    if(flags & O_WRONLY || flags & O_RDWR) mode |= FS_Write;
    if(flags & O_APPEND) mode |= FS_AtEnd;
    if(flags & O_CREAT) mode |= FS_Create;
    if(flags & O_EXCL) mode |= FS_Exclude;
	if(flags & O_TRUNC) mode |= FS_Truncate;
	char path[BT_MAX_PATH]={0};
	if(btos_path_parse(name, path, BT_MAX_PATH)){
		bt_filehandle fh=bt_fopen(path, mode);
		if(fh) return btos_set_filenum(fh);
		else return -1;
	}else return -1;
}

int read(int file, char *ptr, int len){
    return bt_fread(btos_get_handle(file), len, ptr);
}

caddr_t sbrk(int incr){
	static void *base=0;
	static size_t limit=0, alloc=0;

	if(!base){
		base=bt_alloc_pages(1);
		memset(base, 0, 4096);
		alloc=4096;
	}

	size_t old_limit=limit;
	limit+=incr;

	while(limit >= alloc){
		void *page=bt_alloc_pages(1);
        if(!page) return NULL;
		memset(page, 0, 4096);
		alloc+=4096;
	}

	return base+old_limit;
}

int stat(const char *file, struct stat *st){
    st->st_mode = S_IFCHR;
    return 0;
}

clock_t times(struct tms *buf){
	return -1;
}

int unlink(char *name){
	errno=ENOENT;
    return -1;
}

int wait(int *status){
	if(lastchild){
		return bt_wait(lastchild);
	}else{
		errno=ECHILD;
		return -1;
	}
}

int write(int file, char *ptr, int len){
	return bt_fwrite(btos_get_handle(file), len, ptr);
}

