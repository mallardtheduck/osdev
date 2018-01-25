#include <btos_module.h>
#include <util/scoped_ptr.hpp>

extern "C"{
	#include "lib9660.h"
}

#pragma GCC diagnostic ignored "-Wunused-parameter"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

struct iso9660_mountdata{
	l9660_fs fs;
	file_handle *fh;
};

syscall_table *SYSCALL_TABLE;
char dbgbuf[256];

lock iso9660_lock;
const size_t block_size = 2048;
char path_buffer[BT_MAX_PATH] = {0};

static bool in_string(char c, const char *s){
	while(s && *s){
		if(*s == c) return true;
		++s;
	}
	return false;
}

static void shorten(char *fname){
	char *oname = fname;
	char name[13];
	memset(name, 0, 13);
	size_t prelen = 0;
	while(fname && *fname && *fname != '.') ++prelen, ++fname;
	size_t extstart = prelen;
	while(fname && *fname && *fname == '.') ++extstart, ++fname;
	size_t extlen = 0;
	while(fname && *fname) ++extlen, ++fname;
	memcpy(name, oname, prelen > 8 ? 8 : prelen);
	if(extlen){
		size_t extput = prelen > 8 ? 8 : prelen;
		name[extput] = '.';
		++extput;
		memcpy(&name[extput], &oname[extstart], extlen > 3 ? 3 : extlen);
	}
	size_t newlen = (prelen > 8 ? 8 : prelen) + (extlen ? ((extlen > 3 ? 3 : extlen) + 1) : 0);
	//dbgpf("ISO9660: Shorten '%s' to '%s' (%i, %i, %i)\n", oname, name, (int)prelen, (int)extstart, (int)extlen);
	memcpy(oname, name, newlen);
	oname[newlen] = 0;
}

static void filter_chars(char *path){
	const char *allowed_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_.+";
	const char replacement = '_';
	while(path && *path){
		if(*path >= 'a' && *path <= 'z') *path += ('A' - 'a');
		if(!in_string(*path, allowed_chars)) *path = replacement;
		++path;
	}
}

size_t strlen(const char *s) {
	size_t i;
	for (i = 0; s[i] != '\0'; i++) ;
	return i;
}

void fs_path_to_string(fs_path *path, char *buf){
	buf[0] = '\0';
	bool first = true;
	while(path){
		filter_chars(path->str);
		shorten(path->str);
		//dbgpf("ISO9660: Path segment: '%s'\n", path->str);
		if(first){
			strncpy(buf, path->str, BT_MAX_SEGLEN);
			first = false;
		}else sprintf(&buf[strlen(buf)], "/%s", path->str);
		path=path->next;
	}
	dbgpf("ISO9660: Path: %s\n", buf);
}

fs_path *fs_path_last_part(fs_path *path){
	while(true){
		if(path->next) path=path->next;
		else return path;
	}
}

l9660_dir *get_parent(iso9660_mountdata *mount, fs_path *path){
	l9660_dir *parent = new l9660_dir();
	l9660_fs_open_root(parent, &mount->fs);
	while(path && path->str && path->next){
		l9660_dir *newparent = new l9660_dir();
		filter_chars(path->str);
		shorten(path->str);
		l9660_opendirat(newparent, parent, path->str);
		delete parent;
		parent = newparent;
		path = path->next;
	}
	return parent;
}

bool is_path_root(fs_path *path){
	if (!path->next && strcmp(path->str, "") == 0) return true;
	if(path->next) return false;
	char *c = path->str;
	while(c && *c){
		if(*c == '/') *c = '\0';
		++c;
	}
	if(strcmp(path->str, "") == 0) return true;
	return false;
}

uint32_t dual_to_le(l9660_duint32 dual){
	return *(uint32_t*)dual.le;
}

bool read_sector(struct l9660_fs *fs, void *buf, uint32_t sector){
	iso9660_mountdata *mount = (iso9660_mountdata*)fs;
	size_t readaddr = sector * block_size;
	take_lock_recursive(&iso9660_lock);
	fseek(mount->fh, readaddr, false);
	int ret=fread(mount->fh, block_size, (char*)buf);
	release_lock(&iso9660_lock);
	if(ret == 0) panic("(ISO9660) read_sector failed.");
	return !!ret;
}

void *iso9660_mount(char *path){
	void *ret = NULL;
	take_lock(&iso9660_lock);
	file_handle *fh = fopen(path, FS_Read);
	if(fh){
		iso9660_mountdata *mount = new iso9660_mountdata();
		mount->fh = fh;
		l9660_status s = l9660_openfs(&mount->fs, &read_sector);
		if(s == L9660_OK){
			ret = (void*)mount;
		}else{
			dbgpf("ISO9660: Failed to mount %s\n", path);
			delete mount;
		}
	}
	release_lock(&iso9660_lock);
	return ret;
}

bool iso9660_unmount(void *mountdata){
	iso9660_mountdata *mount = (iso9660_mountdata*)mountdata;
	if(mount){
		fclose(mount->fh);
		delete mount;
		return true;
	}else return false;
}

void *iso9660_open(void *mountdata, fs_path *path, fs_mode_flags flags){
	iso9660_mountdata *mount = (iso9660_mountdata*)mountdata;
	if(mount){
		if((flags & FS_Write) || (flags & FS_Truncate))	return NULL;
		take_lock(&iso9660_lock);
		scoped_ptr<l9660_dir> parent(get_parent(mount, path));
		l9660_file *file = new l9660_file();
		char *fname = fs_path_last_part(path)->str;
		filter_chars(fname);
		shorten(fname);
		l9660_status status = l9660_openat(file, parent.get(), fname);
		if(status == L9660_OK){
			if((flags & FS_AtEnd)) l9660_seek(file, L9660_SEEK_END, 0);
		}else{
			delete file;
			file = NULL;
		}
		release_lock(&iso9660_lock);
		return (void*)file;
	}
	return NULL;
}

bool iso9660_close(void *filedata){
	l9660_file *file = (l9660_file*)filedata;
	if(file) { 
		delete file;
		return true;
	}
	return false;
}

size_t iso9660_read(void *filedata, size_t bytes, char *buf){
	l9660_file *file = (l9660_file*)filedata;
	if(file){
		take_lock(&iso9660_lock);
		size_t ret = 0;
		size_t left = bytes;
		while(ret < bytes){
			size_t read = 0;
			l9660_status status = l9660_read(file, buf, left, &read);
			if(status != L9660_OK || read == 0) break;
			left-=read;
			buf+=read;
			ret+=read;
		}
		release_lock(&iso9660_lock);
		return ret;
	}
	return 0;
}

size_t iso9660_write(void *filedata, size_t bytes, char *buf){
	return 0;
}

bt_filesize_t iso9660_seek(void *filedata, bt_filesize_t pos, uint32_t flags){
	l9660_file *file = (l9660_file*)filedata;
	size_t ret = 0;
	if(file){
		take_lock(&iso9660_lock);
		int32_t offset = pos;
		int whence = L9660_SEEK_SET;
		if((flags & FS_Backwards)) offset = -pos;
		if((flags & FS_Relative)) whence = L9660_SEEK_CUR;
		l9660_status status = l9660_seek(file, whence, offset);
		if(status != L9660_OK) panic("(ISO9660) Seek failure.");
		ret = l9660_tell(file);
		release_lock(&iso9660_lock);
	}
	return ret;
}

bool iso9660_setsize(void *filedata, bt_filesize_t size){
	return false;
}

int iso9660_ioctl(void *filedata, int fn, size_t bytes, char *buf){
	return 0;
}

void iso9660_flush(void *){
}

void *iso9660_open_dir(void *mountdata, fs_path *path, fs_mode_flags flags){
	iso9660_mountdata *mount = (iso9660_mountdata*)mountdata;
	if(mount){
		if((flags & FS_Write) || (flags & FS_Truncate))	return NULL;
		take_lock(&iso9660_lock);
		char *pathstr = path_buffer;
		fs_path_to_string(path, pathstr);
		l9660_dir *dir = new l9660_dir();
		l9660_status status;
		if(is_path_root(path)){
			dbgout("ISO9660: Opening root directory.\n");
			status = l9660_fs_open_root(dir, &mount->fs);
		}else{
			dbgpf("ISO9660: Opening directory: '%s'\n", pathstr);
			scoped_ptr<l9660_dir> parent(get_parent(mount, path));
			status = l9660_opendirat(dir, parent.get(), fs_path_last_part(path)->str);
		}
		if(status != L9660_OK){
			delete dir;
			dir = NULL;
		}
		release_lock(&iso9660_lock);
		dbgpf("ISO9660: Returning %p\n", dir);
		return dir;
	}
	return NULL;
}

bool iso9660_close_dir(void *dirdata){
	l9660_dir *dir = (l9660_dir*)dirdata;
	if(dir){
		delete dir;
		return true;
	}
	return false;
}

directory_entry iso9660_read_dir(void *dirdata){
	l9660_dir *dir = (l9660_dir*)dirdata;
	if(dir){
		dbgout("ISO9660: Reading directory.\n");
		directory_entry ret;
		take_lock(&iso9660_lock);
		l9660_dirent *pent;
		do{
			l9660_readdir(dir, &pent);
		}while(pent && (pent->name[0] == '\0' || pent->name[0] == '\1'));
		if(pent){
			l9660_dirent &ent = *pent;
			ret.valid=true;
			dbgpf("ISO9660: Filename '%s' Length: %i\n", ent.name, ent.name_len);
			memset(ret.filename, 0, BT_MAX_SEGLEN);
			strncpy(ret.filename, ent.name, ent.name_len + 1);
			replace_char(ret.filename, ';', '\0');
			ret.type=(ent.flags & 0x02)?FS_Directory:FS_File;
			ret.size=dual_to_le(ent.size);
			ret.id=dual_to_le(ent.sector);
		}else{
			ret.valid = false;
		}
		release_lock(&iso9660_lock);
		return ret;
	}
	return directory_entry();
}

bool iso9660_write_dir(void *, directory_entry){
	return false;
}

size_t iso9660_dirseek(void *dirdata, size_t pos, uint32_t flags){
	l9660_dir *dir = (l9660_dir*)dirdata;
	if(dir){
		take_lock(&iso9660_lock);
		int32_t offset = pos;
		int whence = L9660_SEEK_SET;
		if((flags & FS_Backwards)) pos = -pos;
		if((flags & FS_Relative)) whence = L9660_SEEK_CUR;
		l9660_seek(&dir->file, whence, offset);
		release_lock(&iso9660_lock);
		return l9660_tell(&dir->file);
	}
	return 0;
}

directory_entry iso9660_stat(void *mountdata, fs_path *path){
	iso9660_mountdata *mount = (iso9660_mountdata*)mountdata;
	if(mount){
		directory_entry ret;
		scoped_ptr<l9660_file> file(new l9660_file());
		take_lock(&iso9660_lock);
		char *pathstr = path_buffer;
		fs_path_to_string(path, pathstr);
		dbgpf("ISO9660: Stat '%s'\n", pathstr);
		if(is_path_root(path)) dbgout("ISO9660: Root.\n");
		scoped_ptr<l9660_dir> root(new l9660_dir());
		l9660_status status;
		l9660_fs_open_root(root.get(), &mount->fs);
		if(!is_path_root(path)){
			scoped_ptr<l9660_dir> parent(get_parent(mount, path));
			status = l9660_openat(file.get(), parent.get(), fs_path_last_part(path)->str);
		}
		else status = L9660_ENOTFILE;
		dbgpf("ISO9660: Stat staus %i\n", status);
		if(status == L9660_OK || status == L9660_ENOTFILE){
			ret.valid = true;
			fs_path *lastpart=fs_path_last_part(path);
			strncpy(ret.filename, lastpart->str, BT_MAX_SEGLEN);
			if(status == L9660_OK){
				ret.type = FS_File;
				l9660_seek(file.get(), L9660_SEEK_END, 0);
				ret.size = l9660_tell(file.get());
				ret.id = file->first_sector;
			}else{
				ret.type = FS_Directory;
				ret.size = 0;
				ret.id = 0;
			}
		}else{
			ret.valid = false;
			ret.type = FS_Invalid;
		}
		release_lock(&iso9660_lock);
		return ret;
	}
	return directory_entry();
}

bool iso9660_format(char *, void *){
	return false;
}

fs_driver iso9660_driver = {true, "iso9660", false, iso9660_mount, iso9660_unmount,
							iso9660_open, iso9660_close, iso9660_read, iso9660_write, iso9660_seek, iso9660_setsize, iso9660_ioctl, iso9660_flush,
							iso9660_open_dir, iso9660_close_dir, iso9660_read_dir, iso9660_write_dir, iso9660_dirseek,
							iso9660_stat, iso9660_format};


extern "C" int module_main(syscall_table *systbl, char *params){
		SYSCALL_TABLE=systbl;
		init_lock(&iso9660_lock);
		add_filesystem(&iso9660_driver);
    	return 0;
}
