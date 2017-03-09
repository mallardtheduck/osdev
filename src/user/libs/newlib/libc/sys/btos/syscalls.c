#define __LARGE64_FILES

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/termios.h>
#include <pwd.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <btos.h>
#include <dev/rtc.h>
#include "crt_support.h"

#pragma GCC diagnostic ignored "-Wunused-parameter"

USE_BT_RTC_API;

char *__env[1] = { 0 };
//static char **environ = __env;

static bt_pid lastchild=0;

void _exit(){
	bt_exit(0);
}

int _close(int file){
    virtual_handle *vh=btos_get_handle_virt(file);
    if(!vh) return -1;
    if(vh->type == HANDLE_OS){
		bt_handle_t h = vh->handle;
		int ret=bt_fclose(h);
		if(ret) btos_remove_filenum(file);
		else errno = EBADF;
		return ret;
	}else{
		int ret=vh->virtual.close(vh->virtual.data);
		if(ret) btos_remove_filenum(file);
		else errno = EBADF;
		return ret;
	}
}

int close(int file){
	return _close(file);
}

int _execve(char *name, char **argv, char **env){
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

int execve(char *name, char **argv, char **env){
	return _execve(name, argv, env);
}

int _fork() {
    errno=EAGAIN;
    return -1;
}

int fork(){
	return _fork();
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int fstat(int file, struct stat *st){
	return _fstat(file, st);
}

int _getpid(){
    return bt_getpid();
}

int getpid(){
	return _getpid();
}

int _isatty(int file){
    virtual_handle *vh=btos_get_handle_virt(file);
    if(!vh) return -1;
    if(vh->type == HANDLE_OS){
		bt_filehandle fh = vh->handle;
		if(fh){
			size_t type=bt_fioctl(fh, bt_ioctl_DevType, 0, NULL);
			if((int)type==TERMINAL) return 1;
		}
	}else{
		return vh->virtual.isatty(vh->virtual.data);
	}
    return 0;
}

int isatty(int file){
	return _isatty(file);
}

int _kill(int pid, int sig){
    if(sig == 9){
    	bt_kill(pid);
    	return 0;
    }
    else{
    	errno = EINVAL;
    	return -1;
    }
}

int kill(int pid, int sig){
	return _kill(pid, sig);
}

int _link(char *old, char *new){
    errno=EMLINK;
    return -1;
}

int link(char *old, char *new){
	return _link(old, new);
}

off_t _lseek(int file, off_t ptr, int dir){
	uint32_t flags = 0;
    if(dir==SEEK_CUR){ 
		flags = FS_Relative;
		if(ptr < 0){ 
			flags |= FS_Backwards;
			ptr = -ptr;
		}
	}
	else if(dir==SEEK_END) flags = FS_Backwards;
	
	virtual_handle *vh=btos_get_handle_virt(file);
    if(!vh) return -1;
    if(vh->type == HANDLE_OS){
		bt_filehandle fh = vh->handle;
		return bt_fseek(fh, ptr, flags);
	}else{
		return vh->virtual.lseek(vh->virtual.data, ptr, dir);
	}
}

off_t lseek(int file, off_t ptr, int dir){
	return _lseek(file, ptr, dir);
}

int _open(const char *name, int flags, ...){
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

int open(const char *name, int flags, ...){
	return _open(name, flags);
}

int _read(int file, char *ptr, int len){
	virtual_handle *vh=btos_get_handle_virt(file);
    if(!vh) return -1;
    if(vh->type == HANDLE_OS){
		bt_filehandle fh = vh->handle;
		return bt_fread(fh, len, ptr);
	}else{
		return vh->virtual.read(vh->virtual.data, ptr, len);
	}
}

int read(int file, char *ptr, int len){
	return _read(file, ptr, len);
}

caddr_t _sbrk(int incr){
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

caddr_t sbrk(int incr){
	return _sbrk(incr);
}

int _stat(const char *file, struct stat *st){
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

int stat(const char *file, struct stat *st){
	return _stat(file, st);
}

clock_t _times(struct tms *buf){
	errno = ENOTSUP;
	return -1;
}

int _unlink(char *name){
	bt_handle_t fh = bt_fopen(name, FS_Delete);
	if(!fh){
		errno = ENOENT;
		return -1;
	}
	return bt_fclose(fh);
}

int unlink(char *name){
	return _unlink(name);
}

int _wait(int *status){
	if(lastchild){
		return bt_wait(lastchild);
	}else{
		errno=ECHILD;
		return -1;
	}
}

int wait(int *status){
	return _wait(status);
}

int _write(int file, char *ptr, int len){
	virtual_handle *vh=btos_get_handle_virt(file);
    if(!vh) return -1;
    if(vh->type == HANDLE_OS){
		bt_filehandle fh = vh->handle;
		return bt_fwrite(fh, len, ptr);
	}else{
		return vh->virtual.write(vh->virtual.data, ptr, len);
	}
}

int write(int file, char *ptr, int len){
	return _write(file, ptr, len);
}

int _creat(const char *path, mode_t mode){
	return open(path, O_WRONLY|O_CREAT|O_TRUNC, mode);
}

int creat(const char *path, mode_t mode){
	return _creat(path, mode);
}

int _chmod(const char *path, mode_t mode){
	(void)path; (void)mode;
	errno = ENOTSUP;
	return -1;
}

int chmod(const char *path, mode_t mode){
	return _chmod(path, mode);
}

int _symlink(const char *path1, const char *path2){
	(void)path1; (void)path2;
	errno = ENOTSUP;
	return -1;
}

int symlink(const char *path1, const char *path2){
	return _symlink(path1, path2);
}

int _mkdir(const char *name, mode_t mode){
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

int mkdir(const char *name, mode_t mode){
	return _mkdir(name, mode);
}

int _pipe(int fildes[2]){
	(void)fildes;
	errno = ENOTSUP;
	return -1;
}

int pipe(int fildes[2]){
	return _pipe(fildes);
}

int _dup(int fildes){
	errno = ENOTSUP;
	(void)fildes;
	return -1;
}

int dup(int fildes){
	return _dup(fildes);
}

mode_t _umask(mode_t cmask){
	(void)cmask;
	errno = ENOTSUP;
	return 0;
}

mode_t umask(mode_t cmask){
	return _umask(cmask);
}

ssize_t _readlink(const char *__restrict path, char *__restrict buf, size_t bufsize){
	(void)path; (void)buf; (void)bufsize;
	errno = ENOTSUP;
	return -1;
}

ssize_t readlink(const char *__restrict path, char *__restrict buf, size_t bufsize){
	return _readlink(path, buf, bufsize);
}

struct passwd *_getpwuid(uid_t uid){
	(void)uid;
	errno = ENOTSUP;
	return NULL;
}

struct passwd *getpwuid(uid_t uid){
	return _getpwuid(uid);
}

struct passwd *_getpwnam(const char *name){
	(void)name;
	errno = ENOTSUP;
	return NULL;
}

struct passwd *getpwnam(const char *name){
	return _getpwnam(name);
}

void setgrent(){
}

struct group *_getgrgid(gid_t gid){
	(void)gid;
	errno = ENOTSUP;
	return NULL;
}

struct group *getgrgid(gid_t gid){
	return _getgrgid(gid);
}

struct group *_getgrnam(const char *name){
	(void)name;
	errno = ENOTSUP;
	return NULL;
}

struct group *getgrnam(const char *name){
	return _getgrnam(name);
}

int _gettimeofday(struct timeval *__restrict tv, void *__restrict tz){
	(void)tz;
	uint64_t time = bt_rtc_get_time();
	tv->tv_sec = (time / 1000) + 946684800; //Seconds between 1/1/1970 and 1/1/2000.
	tv->tv_usec = (time % 1000) * 1000;
	return 0;
}

int gettimeofday(struct timeval *__restrict tv, void *__restrict tz){
	return _gettimeofday(tv, tz);
}

int _usleep(useconds_t useconds)
{
	uint32_t msec = useconds / 1000;
	bt_rtc_sleep(msec);
   	return 0;
}

int usleep(useconds_t useconds){
	return _usleep(useconds);
}

int _getpagesize(){
	return 4096;
}

int getpagesize(){
	return _getpagesize();
}

char *_getwd(char *path_name){
	bt_getenv("CWD", path_name, BT_MAX_PATH);
	return path_name;
}

char *getwd(char *path_name){
	return _getwd(path_name);
}

int _fcntl(int fd, int cmd, ... /* arg */){
	return 0;
}

int fcntl(int fd, int cmd, ... /* arg */){
	return 0;
}


uid_t _getuid(){
	return 0;
}

uid_t getuid(){
	return _getuid();
}

int tcgetattr(int fd, struct termios *termios_p){
	if(isatty(fd)){
		memset(termios_p, 0, sizeof(*termios_p));
		termios_p->c_cc[1] = 8;
		return 0;
	}
	return 1;
}

int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p){
	return -1;
}

int _fsync(int fd){
	virtual_handle *vh=btos_get_handle_virt(fd);
    if(!vh) return -1;
    if(vh->type == HANDLE_OS){
		bt_filehandle fh = vh->handle;
		bt_fflush(fh);
	}else{
		return vh->virtual.fsync(vh->virtual.data);
	}
	return 0;
}

int fsync(int fd){
	return _fsync(fd);
}

char *realpath(const char *path, char *resolved_path){
	if(!resolved_path) resolved_path = malloc(BT_MAX_PATH);
	btos_path_parse(path, resolved_path, BT_MAX_PATH);
	return resolved_path;
}

char *_getcwd(char *buf, size_t size){
	if(!buf) buf = malloc(BT_MAX_PATH);
	bt_getenv("CWD", buf, BT_MAX_PATH);
	return buf;
}

char *getcwd(char *buf, size_t size){
	return _getcwd(buf, size);
}

int _chdir(const char *path){
	char buf[BT_MAX_PATH] = {0};
	btos_path_parse(path, buf, BT_MAX_PATH);
	bt_setenv("CWD", path, 0);
	return 0;
}

int chdir(const char *path){
	return _chdir(path);
}

int _lstat(const char *path, struct stat *buf){
	return _stat(path, buf);
}

int lstat(const char *path, struct stat *buf){
	return _lstat(path, buf);
}

int _stat64(const char *path, struct stat64 *buf){
	return 0;
}

int stat64(const char *path, struct stat64 *buf){
	return _stat64(path, buf);
}
