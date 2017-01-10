#include <btos.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "crt_support.h"

#define ARGS_MAX 4096
#define ARGC_MAX 512

static char argsbuffer[ARGS_MAX]={0};
static char *argsptr[ARGC_MAX]={0};

static bt_handle *filehandles=NULL;
static size_t fh_count=0;

static bool std_streams_open = false;

void btos_open_std_streams(){
	if(std_streams_open) return;
    char buffer[BT_MAX_PATH];
    size_t s=bt_getenv("STDIN", buffer, BT_MAX_PATH);
    if(s){
        bt_handle input=bt_fopen(buffer, FS_Read);
        btos_set_specific_filenum(0, input);
    }
    memset(buffer, 0, BT_MAX_PATH);
    s=bt_getenv("STDOUT", buffer, BT_MAX_PATH);
    if(s){
        bt_handle output=bt_fopen(buffer, FS_Write | FS_AtEnd);
        btos_set_specific_filenum(1, output);
    }
    memset(buffer, 0, BT_MAX_PATH);
    s=bt_getenv("STDERR", buffer, BT_MAX_PATH);
    if(s){
        bt_handle output=bt_fopen(buffer, FS_Write | FS_AtEnd);
        btos_set_specific_filenum(2, output);
    }
    std_streams_open = true;
}

int btos_set_filenum(bt_handle fh){
    size_t i;
    for(i=0; i<fh_count; ++i){
        if(filehandles[i]==0){
            filehandles[i]=fh;
            return (int)i;
        }
    }
    ++fh_count;
    filehandles=realloc(filehandles, fh_count * sizeof(bt_handle));
    filehandles[fh_count-1]=fh;
    return (int)fh_count-1;
}

bt_handle btos_get_handle(int fd){
	bt_zero("b_g_h\n");
	btos_open_std_streams();
    if(fd < fh_count) return filehandles[fd];
    else return 0;
}

void btos_set_specific_filenum(int fd, bt_handle fh){
    if(fd < fh_count) filehandles[fd]=fh;
    else{
        size_t oldsize=fh_count;
        fh_count=fd+1;
        filehandles=realloc(filehandles, fh_count * sizeof(bt_handle));
        memset(&filehandles[oldsize], 0, (fh_count-oldsize) * sizeof(bt_handle));
        filehandles[fd]=fh;
    }
}

void btos_remove_filenum(int fd){
    if(fd < fh_count) filehandles[fd]=0;
}

size_t get_argc(){
	return bt_get_argc();
}

char **get_argv(){
	size_t bufferused=0;
	size_t argc=get_argc();
	if(argc >  ARGC_MAX) argc=ARGC_MAX;
	size_t i;
	for(i=0; i < argc; ++i){
		if(bufferused >= ARGS_MAX) break;
		size_t psize=bt_get_arg(i, &argsbuffer[bufferused], ARGS_MAX-bufferused);
		argsptr[i]=&argsbuffer[bufferused];
		bufferused+=psize+1;
	}
	return argsptr;
}

bool btos_path_is_absolute(const char *path){
	if(!path) return false;
	char *c;
	for(c=path; *c; ++c){
		if(*c==':') return true;
		if(*c=='/') return false;
	}
	return false;
}

size_t btos_get_drive_end(const char *path){
	size_t i;
	for(i=0; i<strlen(path); ++i){
		if(path[i]==':') return i;
	}
	return 0;
}

bool btos_path_parse(const char *opath, char *buffer, size_t size){
	char path[BT_MAX_PATH]={0};
	if(btos_path_is_absolute(opath)){
		strncpy(path, opath, BT_MAX_PATH);
	}else{
		if(opath[0]=='/'){
			char cwd[BT_MAX_PATH];
			bt_getenv("CWD", cwd, BT_MAX_PATH);
			size_t drive_end=btos_get_drive_end(cwd);
			strncpy(path, cwd, drive_end);
			strncpy(&path[strlen(path)], ":", BT_MAX_PATH-strlen(path));
			strncpy(&path[strlen(path)], opath, BT_MAX_PATH-strlen(path));
		}else{
			bt_getenv("CWD", path, BT_MAX_PATH);
			strncpy(&path[strlen(path)], "/", BT_MAX_PATH-strlen(path));
			strncpy(&path[strlen(path)], opath, BT_MAX_PATH-strlen(path));
		}
	}
	char *c;
	bool has_drive=false;
	memset(buffer, 0, size);
	size_t bpos=0, ipos=0, cstart=0;
	for(c=path; (ipos==0 || *(c - 1)) && bpos < size; ++c, ++ipos){
		if(*c==':'){
			if(!has_drive && ipos){
				buffer[bpos++]=':';
				buffer[bpos++]='/';
				cstart=bpos;
				has_drive=true;
			}else{
				return false;
			}
		}else if(*c=='/' || *c=='\n' || *c=='\0'){
			char cstr[BT_MAX_SEGLEN]={0};
			if((int)(bpos-cstart) > 0) strncpy(cstr, &buffer[cstart], bpos-cstart);
			if(strlen(cstr) && strcmp(cstr, "..")==0){
				buffer[--bpos]='\0';
				buffer[--bpos]='\0';
				if(bpos-2 > 0 && buffer[bpos-2] != ':'){
					buffer[--bpos]='\0';
					while(bpos && buffer[bpos]!='/') buffer[bpos--]='\0';
					buffer[bpos++]='/';
				}
				cstart=bpos;
			}else if(strlen(cstr) && strcmp(cstr, ".")==0){
				buffer[--bpos]='\0';
				cstart=bpos;
			}else if(strlen(cstr) && *c!='\n' && *c!='\0'){
				buffer[bpos++]='/';
				cstart=bpos;
			}
		}else buffer[bpos++]=*c;
	}
	if(bpos > 1 && buffer[bpos-1]=='/' && buffer[bpos-2] != ':') buffer[bpos-1]='\0';
	return true;
}
