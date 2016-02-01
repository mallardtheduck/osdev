#include <sys/dirent.h>
#include <stdlib.h>
#include <string.h>
#include "crt_support.h"

DIR *opendir (const char *name){
	char path[BT_MAX_PATH]={0};
	if(btos_path_parse(name, path, BT_MAX_PATH)){
		DIR *ret = malloc(sizeof(DIR));
		if(ret) *ret = bt_dopen(path, FS_Read);
		return ret;
	}else return NULL;
}

int readdir_r (DIR *__restrict dirp, struct dirent *__restrict entry, struct dirent **__restrict result){
	bt_directory_entry de = bt_dread(*dirp);
	if(de.valid){
		entry->d_ino = de.id;
		strncpy(entry->d_name, de.filename, MAXNAMLEN);
		entry->d_namlen = strlen(entry->d_name);
		entry->d_reclen = sizeof(entry);
		if(result) *result = entry;
		return 0;
	}else{
		if(result) *result = NULL;
		return -1;
	}
}

struct dirent *readdir (DIR *dirp){
	static struct dirent ret;
	readdir_r(dirp, &ret, NULL);
	return &ret;
}

void rewinddir (DIR *dirp){
	bt_dseek(*dirp, 0, 0);
}

int closedir (DIR *dirp){
	bt_dclose(*dirp);
	free(dirp);
}