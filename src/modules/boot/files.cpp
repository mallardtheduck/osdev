#include "ini.h"
#include <btos_module.h>

extern "C" void *fopen(const char *filename, fs_mode_flags flags){
	auto node = API->GetVirtualFilesystem().GetNode(filename);
	if(node){
		return node->OpenFile(flags);
	}else return nullptr;
}

extern "C" void fclose(FILE *stream){
	auto handle = static_cast<IFileHandle*>(stream);
	handle->Close();
	delete handle;
}

extern "C" char *fgets(char *str, int num, FILE *stream){
	auto handle = static_cast<IFileHandle*>(stream);
	char *ret = str; 
	for(int i = 0; i < num; ++i){
		if(handle->Read(1, str) != 1) return nullptr;
		if(*str=='\n'){
			*str='\0';
			break;
		}
		++str;
	}
	return ret;
}