#include "util.hpp"
#include "el_malloc.hpp"

static const char *LIBPATH_ENV = "LIBPATH";

bt_handle_t open_lib(const char *name, char **fullpath){
    bt_handle_t ret = 0;
    if(!btos_path_is_absolute(name)){
        char *libPathStr = NULL;
        size_t lpLen = bt_getenv(LIBPATH_ENV, libPathStr, 0);
        if(lpLen > 0){
            libPathStr = (char*)realloc(libPathStr, lpLen + 1);
            bt_getenv(LIBPATH_ENV, libPathStr, lpLen);
            size_t startPoint = 0;
            for(size_t i=0; i<lpLen + 1; ++i){
                if(libPathStr[i] == ',' || libPathStr[i] == '\0'){
                    size_t partLen = i - startPoint;
                    if(partLen > 0){
                        char part[BT_MAX_PATH] = {0};
                        strncpy(part, &libPathStr[startPoint], partLen);
                        strncpy(part + strlen(part), "/", BT_MAX_PATH - strlen(part));
                        strncpy(part + strlen(part), name, BT_MAX_PATH - strlen(part));
                        char* checkPath = (char*)malloc(BT_MAX_PATH);
						memset(checkPath, 0, BT_MAX_PATH);
                        btos_path_parse(part, checkPath, BT_MAX_PATH);
                        bt_directory_entry ent = bt_stat(checkPath);
                        if(ent.valid && ent.type == FS_File){
                            ret = bt_fopen(checkPath, FS_Read);
                            if(!fullpath || !ret) free(checkPath);
							else *fullpath = checkPath;
                            break;
                        }
                        free(checkPath);
                        startPoint = i + 1;
                    }
                    if(libPathStr[i] == '\0') break;
                }
            }
        }else{
            bt_zero("ELOADER: No library path!\n");
        }
        free(libPathStr);
        if(!ret){
            char appPath[BT_MAX_PATH] = {0};
            bt_get_arg(0, appPath, BT_MAX_PATH);
            remove_filepart(appPath);
            strncpy(appPath + strlen(appPath), "/", BT_MAX_PATH - strlen(appPath));
            strncpy(appPath + strlen(appPath), name, BT_MAX_PATH - strlen(appPath));
            char* checkPath = (char*)malloc(BT_MAX_PATH);
            memset(checkPath, 0, BT_MAX_PATH);
            btos_path_parse(appPath, checkPath, BT_MAX_PATH);
            bt_directory_entry ent = bt_stat(checkPath);
            if(ent.valid && ent.type == FS_File){
                ret = bt_fopen(checkPath, FS_Read);
            }
            if(!fullpath || !ret) free(checkPath);
            else *fullpath = checkPath;
        }
    }else{
        ret = bt_fopen(name, FS_Read);
        if(ret && fullpath){
			*fullpath = (char*)malloc(strlen(name) + 1);
			memset(*fullpath, 0, strlen(name) + 1);
			strncpy(*fullpath, name, strlen(name) + 1);
		}
    }
    
    if(!ret && name[strlen(name)-1] == '.'){
		char *newname = (char*)malloc(strlen(name) + 1);
		newname[strlen(newname)-1] = '\0';
		ret = open_lib(newname, fullpath);
		free(newname);
	}
    return ret;
}
