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

void _exit(){
	bt_exit(0);
}

int close(int file){
    return -1;
}

int execve(char *name, char **argv, char **env){
    errno=ENOMEM;
    return -1;
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
    return 1;
}

int isatty(int file){
    return 1;
}

int kill(int pid, int sig){
    errno=EINVAL;
    return(-1);
}

int link(char *old, char *new){
    errno=EMLINK;
    return -1;
}

int lseek(int file, int ptr, int dir){
    return 0;
}

int open(const char *name, int flags, ...){
    return -1;
}

int read(int file, char *ptr, int len){
    return 0;
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
	errno=ECHILD;
	return -1;
}

int write(int file, char *ptr, int len){
	static bt_filehandle stdout_handle=0;
	if(file==1){
		if(!stdout_handle){
			char stdout_path[255];
			if(!bt_getenv("STDOUT", stdout_path, 200)){
				char temp[255];
				if(!bt_getenv("DISPLAY_DEVICE", &temp, 200)){
					return 0;
				}else{
					snprintf(stdout_path, 255, "DEV:/%s", temp);
				}
			}
			stdout_handle=bt_fopen(stdout_path, 0);
		}
		return bt_fwrite(stdout_handle, len, ptr);
	}
	return 0;
}

