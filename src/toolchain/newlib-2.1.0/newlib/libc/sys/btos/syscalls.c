/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include "../../../../../include/btos_stubs.h"

char *__env[1] = { 0 };
char **environ = __env;

#define num_specialhandles 10
static bt_filehandle specialhandles[num_specialhandles]={0};
static bt_pid lastchild=0;

static int bt_filehandle_to_fileint(bt_filehandle h){
	return h + num_specialhandles;
}

static bt_filehandle fileint_to_bt_filehandle(int i){
	if(i<num_specialhandles){
		if(!specialhandles[1]){ //STDOUT
			char stdout_path[255];
			if(!bt_getenv("STDOUT", stdout_path, 200)){
				char temp[255];
				if(!bt_getenv("DISPLAY_DEVICE", temp, 200)){
					return 0;
				}else{
					snprintf(stdout_path, 255, "DEV:/%s", temp);
				}
			}
			specialhandles[1]=bt_fopen(stdout_path, FS_Write);
    	}
    	if(!specialhandles[2]){ //STDERR
    		specialhandles[2]=specialhandles[1];
    	}

		return specialhandles[i];
	}
	else return i - num_specialhandles;
}

void _exit(){
	bt_exit(0);
}

int close(int file){
    return bt_fclose(fileint_to_bt_filehandle(file));
}

int execve(char *name, char **argv, char **env){
    lastchild=bt_spawn(name, 0, NULL);
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
    return 1;
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
    bool relative=false;
    if(dir==SEEK_CUR) relative=true;
    return bt_fseek(fileint_to_bt_filehandle(file), ptr, relative);
}

int open(const char *name, int flags, ...){
    fs_mode_flags mode=FS_Read;
    if(flags & O_WRONLY) mode &= ~FS_Read;
    if(flags & O_WRONLY || flags & O_RDWR) mode |= FS_Write;
    if(flags & O_APPEND) mode |= FS_AtEnd;
    if(flags & O_CREAT) mode |= FS_Create;
    if(flags & O_EXCL) mode |= FS_Exclude;
	if(flags & O_TRUNC) mode |= FS_Truncate;
	bt_filehandle fh=bt_fopen(name, mode);
	if(fh) return bt_filehandle_to_fileint(fh);
	else return -1;
}

int read(int file, char *ptr, int len){
    return bt_fread(fileint_to_bt_filehandle(file), len, ptr);
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
	return bt_fwrite(fileint_to_bt_filehandle(file), len, ptr);
}

