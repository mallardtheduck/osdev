/* note these headers are all provided by newlib - you don't need to provide them */
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <btos.h>
#include <dev/rtc.h>
#include "crt_support.h"

USE_BT_RTC_API;

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
	else errno = EBADF;
    return ret;
}

int execve(char *name, char **argv, char **env){
    size_t i=0;
    if(argv){
        while(argv[i]) ++i;
    }
    lastchild=bt_spawn(name, i, argv);
    if(!lastchild){
		errno = ENOENT;
		return -1;
	}
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
		else{
			errno = ENOENT;
			return -1;
		}
	}else{
		errno = ENOENT;
		return -1;
	}
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
	char path[BT_MAX_PATH]={0};
	if(btos_path_parse(file, path, BT_MAX_PATH)){
		bt_directory_entry e = bt_stat(path);
		if(e.valid){
			st->st_dev = 0;
			st->st_ino = e.id;
			switch(e.type){
				case FS_File:
					st->st_mode = S_IFREG | S_IRWXU | S_IRWXG | S_IRWXO;
					break;
				case FS_Directory:
					st->st_mode = S_IFDIR | S_IRWXU | S_IRWXG | S_IRWXO;
					break;
				case FS_Link:
					st->st_mode = S_IFLNK | S_IRWXU | S_IRWXG | S_IRWXO;
					break;
				case FS_Device:
					st->st_mode = S_IFCHR | S_IRWXU | S_IRWXG | S_IRWXO;
					break;
				case FS_Invalid:
					return -1;
			}
			st->st_nlink = 1;
			st->st_uid = 0;
			st->st_gid = 0;
			st->st_rdev = 0;
			st->st_size = e.size;
			st->st_atime = 0;
			st->st_mtime = 0;
			st->st_ctime = 0;
			st->st_blksize = 1;
			st->st_blocks = e.size;
			return 0;
		}else{
			errno = ENOENT;
			return -1;
		}
	}else{
		errno = EINVAL;
		return -1;
	}
}

clock_t times(struct tms *buf){
	errno = ENOTSUP;
	return -1;
}

int unlink(char *name){
	bt_handle_t fh = bt_fopen(name, FS_Delete);
	if(!fh){
		errno = ENOENT;
		return -1;
	}
	return bt_fclose(fh);
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

int creat(const char *path, mode_t mode){
	return open(path, O_WRONLY|O_CREAT|O_TRUNC, mode);
}

int chmod(const char *path, mode_t mode){
	(void)path; (void)mode;
	errno = ENOTSUP;
	return -1;
}


int symlink(const char *path1, const char *path2){
	(void)path1; (void)path2;
	errno = ENOTSUP;
	return -1;
}


int mkdir(const char *name, mode_t mode){
	char path[BT_MAX_PATH]={0};
	if(btos_path_parse(name, path, BT_MAX_PATH)){
		bt_dirhandle dh=bt_dopen(path, FS_Read | FS_Create);
		if(dh) {
			bt_dclose(dh);
			return 0;
		}else{
			errno = ENOENT;
			return -1;
		}
	}else{
		errno = EINVAL;
		return -1;
	}
}

int pipe(int fildes[2]){
	(void)fildes;
	errno = ENOTSUP;
	return -1;
}

int dup(int fildes){
	errno = ENOTSUP;
	(void)fildes;
	return -1;
}

mode_t umask(mode_t cmask){
	(void)cmask;
	errno = ENOTSUP;
	return 0;
}


ssize_t readlink(const char *__restrict path, char *__restrict buf, size_t bufsize){
	(void)path; (void)buf; (void)bufsize;
	errno = ENOTSUP;
	return -1;
}

struct passwd *getpwuid(uid_t uid){
	(void)uid;
	errno = ENOTSUP;
	return NULL;
}


struct passwd *getpwnam(const char *name){
	(void)name;
	errno = ENOTSUP;
	return NULL;
}

void setgrent(){
}

struct group *getgrgid(gid_t gid){
	(void)gid;
	errno = ENOTSUP;
	return NULL;
}

struct group *getgrnam(const char *name){
	(void)name;
	errno = ENOTSUP;
	return NULL;
}

int gettimeofday(struct timeval *__restrict tv, void *__restrict tz){
	(void)tz;
	uint64_t time = bt_rtc_get_time();
	tv->tv_sec = (time / 1000) + 946684800; //Seconds between 1/1/1970 and 1/1/2000.
	tv->tv_usec = (time % 1000) * 1000;
	return 0;
}

int usleep(useconds_t useconds)
{
	uint32_t msec = useconds / 1000;
	bt_rtc_sleep(msec);
   	return 0;
}

int getpagesize(void){
	return 4096;
}

char *getwd(char *path_name){
	bt_getenv("CWD", path_name, BT_MAX_PATH);
	return path_name;
}

int fcntl(int fd, int cmd, ... /* arg */){
	return 0;
}


uid_t getuid(){
	return 0;
}
