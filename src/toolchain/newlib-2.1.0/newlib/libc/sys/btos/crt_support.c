#include "../../../../../include/btos_stubs.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define ARGS_MAX 4096
#define ARGC_MAX 512

static char argsbuffer[ARGS_MAX]={0};
static char *argsptr[ARGC_MAX]={0};

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

bool btos_path_is_absolute(char *path){
	if(!path) return false;
	char *c;
	for(c=path; *c; ++c){
		if(*c==':') return true;
		if(*c=='/') return false;
	}
	return false;
}

bool btos_path_parse(char *opath, char *buffer, size_t size){
	char path[BT_MAX_PATH]={0};
	if(btos_path_is_absolute(opath)){
		strncpy(path, opath, BT_MAX_PATH);
	}else{
		bt_getenv("CWD", path, BT_MAX_PATH);
		strncpy(&path[strlen(path)], opath, BT_MAX_PATH-strlen(path));
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