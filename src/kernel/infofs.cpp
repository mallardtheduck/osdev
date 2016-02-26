#include "kernel.hpp"
#include "ministl.hpp"

void* const infofs_magic=(void*)0x14F0F5;

map<string, info_function> *info_items;

struct infofs_filehandle{
	size_t pos, size;
	char *data;

	infofs_filehandle(char *d) : pos(0), size(strlen(d)), data(d) {}
	infofs_filehandle() : pos(0), size(0), data(NULL) {}
	~infofs_filehandle() {free(data);}
};

struct infofs_dirhandle{
	size_t pos;
	infofs_dirhandle(size_t p=0) : pos(p) {}
};

static string get_dirindex(size_t idx){
	size_t count=0;
	for(map<string, info_function>::iterator i=info_items->begin(); i!=info_items->end(); ++i){
		if(count==idx) return i->first;
		count++;
	}
	return "";
}

void *infofs_mount(char *device){
	return infofs_magic;
}

bool infofs_unmount(void *mountdata){
	return (mountdata == infofs_magic);
}

void *infofs_open(void *mountdata, fs_path *path, fs_mode_flags){
	if(mountdata != infofs_magic) return NULL;
	if(!info_items->has_key(path->str)) return NULL;
	char *data=(*info_items)[path->str]();
	infofs_filehandle *ret=new infofs_filehandle(data);
	return (void*)ret;
}

bool infofs_close(void *filedata){
	if(!filedata) return false;
	infofs_filehandle *fdata=(infofs_filehandle*)filedata;
	delete fdata;
	return true;
}

size_t infofs_read(void *filedata, size_t bytes, char *buf){
	if(!filedata) return 0;
	infofs_filehandle *fdata=(infofs_filehandle*)filedata;
	if(fdata->pos >= fdata->size) return 0;
	if(fdata->pos + bytes >= fdata->size) bytes=fdata->size - fdata->pos;
	memcpy(buf, &fdata->data[fdata->pos], bytes);
	fdata->pos+=bytes;
	return bytes;
}

size_t infofs_write(void *filedata, size_t bytes, char *buf){
	return 0;
}

bt_filesize_t infofs_seek(void *filedata, bt_filesize_t pos, uint32_t flags){
	if(!filedata) return 0;
    infofs_filehandle *fdata=(infofs_filehandle*)filedata;
    if(flags & FS_Relative) fdata->pos+=pos;
	else if (flags & FS_Backwards){
		fdata->pos = fdata->size - pos;
	}else if(flags == (FS_Relative | FS_Backwards)) fdata->pos -= pos;
    else fdata->pos=pos;
    return fdata->pos;
}

int infofs_ioctl(void *filedata, int fn, size_t bytes, char *buf){
	return 0;
}

void infofs_flush(void *){
}

void *infofs_open_dir(void *mountdata, fs_path *path, fs_mode_flags){
	if(mountdata != infofs_magic) return NULL;
	return (void*)new infofs_dirhandle();
}

bool infofs_close_dir(void *dirdata){
	if(!dirdata) return false;
	delete (infofs_dirhandle*)dirdata;
	return true;
}

directory_entry infofs_read_dir(void *dirdata){
	if(!dirdata) return invalid_directory_entry;
	infofs_dirhandle *ddata=(infofs_dirhandle*)dirdata;
	string name=get_dirindex(ddata->pos);
	if(name=="") return invalid_directory_entry;
	dbgpf("INFO: '%s', %i\n", name.c_str(), strcmp(name.c_str(), ""));
	directory_entry ret;
	ret.valid=true;
	strncpy(ret.filename, name.c_str(), 255);
	ret.id = (uint64_t)(*info_items)[name];
	ret.size=0;
	ret.type=FS_File;
	ddata->pos++;
	return ret;
}

bool infofs_write_dir(void *dirdata, directory_entry entry){
	return false;
}

size_t infofs_dirseek(void *dirdata, size_t pos, uint32_t flags){
	if(!dirdata) return 0;
	infofs_dirhandle *ddata=(infofs_dirhandle*)dirdata;
	if(flags & FS_Relative) ddata->pos+=pos;
	else if(flags & FS_Backwards){
		ddata->pos = info_items->size() - pos;
	} else if(flags == (FS_Backwards | FS_Relative)) ddata->pos-=pos;
	else ddata->pos=pos;
	return ddata->pos;
}

directory_entry infofs_stat(void *mountdata, fs_path *path){
	if(!path->next && strcmp(path->str, "")==0){
		directory_entry ret;
		ret.valid=true;
		strncpy(ret.filename, "/", 255);
		ret.id = 0;
		ret.size=0;
		ret.type=FS_Directory;
		return ret;
	}
	if(!info_items->has_key(path->str)) return invalid_directory_entry;
	directory_entry ret;
    ret.valid=true;
    strncpy(ret.filename, path->str, 255);
	ret.id = (uint64_t)(*info_items)[path->str];
    ret.size=0;
    ret.type=FS_File;
    return ret;
}

bool infofs_format(char*, void*){
	return false;
}

fs_driver infofs_driver={true, "INFOFS", false, infofs_mount, infofs_unmount, infofs_open, infofs_close, infofs_read,
	infofs_write, infofs_seek, infofs_ioctl, infofs_flush, infofs_open_dir, infofs_close_dir, infofs_read_dir, infofs_write_dir,
	infofs_dirseek, infofs_stat, infofs_format};

void infofs_register(const char *name, info_function fn){
	if(!info_items) info_items=new map<string, info_function>();
	(*info_items)[name]=fn;
}

char *info_kernel(){
	char* buffer=(char*)malloc(128);
	sprintf(buffer, "%s %s (Build ID:%s)\n%s\n", KERNEL_OS_NAME, KERNEL_VERSION_STRING, kernel_buildid, KERNEL_COPYRIGHT);
	return buffer;
}

char *info_cpu(){
	char* buffer=(char*)malloc(256);
	sprintf(buffer, "%s %s\n", cpu_idstring(), cpu_brandstring());
	return buffer;
}

void infofs_init(){
	if(!info_items) info_items=new map<string, info_function>();
	fs_registerfs(infofs_driver);
	fs_mount("INFO", NULL, "INFOFS");
	infofs_register("VERSION", &info_kernel);
	infofs_register("CPUID", &info_cpu);
}

