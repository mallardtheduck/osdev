#include "util.hpp"

int strlen(const char *s){
	int ret = 0;
	while(s && *s) ++ret, ++s;
	return ret;
}

char *strncpy(char *s1, const char *s2, size_t n){
	char *s = s1;
	while (n > 0 && *s2 != '\0') {
		*s++ = *s2++;
		--n;
	}
	while (n > 0) {
		*s++ = '\0';
		--n;
	}
	return s1;
}

int strcmp(const char *s1, const char *s2){
	if(!*s1 && !*s2) return 0;
	while((*s1 && *s2) && (*s1++ == *s2++));
	if(!*s1 != !*s2) return *s1 - *s2;
	else return *(--s1) - *(--s2);
}

void *memset(void *s, int c, size_t n){
	asm volatile ("cld; rep stosb" : "+D"(s) : "a"(c), "c"(n) : "cc", "memory" );
	return s;
}

bool btos_path_is_absolute(const char *path){
	if(!path) return false;
	const char *c;
	for(c=path; *c; ++c){
		if(*c==':') return true;
		if(*c=='/') return false;
	}
	return false;
}

static size_t btos_get_drive_end(const char *path){
	size_t i;
	for(i=0; i<(size_t)strlen(path); ++i){
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