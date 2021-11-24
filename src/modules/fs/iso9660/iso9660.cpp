#include <module/module.inc>
#include <module/utils/string.hpp>
#include <util/scoped_ptr.hpp>

extern "C"{
	#include "lib9660.h"
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

constexpr size_t block_size = 2048;

ILock *iso9660_lock;

class ISOFileHandle : public IFileHandle{
private:
	l9660_file *file;
	FilesystemNodePointer node;
public:
	size_t Read(size_t bytes, char *buffer) override{
		if(file){
			auto hl = iso9660_lock->LockExclusive();
			size_t ret = 0;
			size_t left = bytes;
			while(ret < bytes){
				size_t read = 0;
				l9660_status status = l9660_read(file, buffer, left, &read);
				if(status != L9660_OK || read == 0) break;
				left -= read;
				buffer += read;
				ret += read;
			}
			return ret;
		}
		return 0;
	}
	size_t Write(size_t, const char *) override{
		return 0;
	}

	bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) override{
		size_t ret = 0;
		if(file){
			auto hl = iso9660_lock->LockExclusive();
			int32_t offset = pos;
			int whence = L9660_SEEK_SET;
			if((flags & FS_Backwards)) offset = -pos;
			if((flags & FS_Relative)) whence = L9660_SEEK_CUR;
			l9660_status status = l9660_seek(file, whence, offset);
			if(status != L9660_OK) panic("(ISO9660) Seek failure.");
			ret = l9660_tell(file);
		}
		return ret;
	}

	bool Resize(bt_filesize_t) override{
		return false;
	}

	int IOCtl(int, size_t, char *) override{
		return 0;
	}

	void Flush() override{}

	FilesystemNodePointer GetNode() override{
		return node;
	}
};

class ISODirectoryHandle : public IDirectoryHandle{
private:
	l9660_dir *dir;
public:
	fs_item_types ReadType() override{}

	FilesystemNodePointer Read() override{
		if(dir){
			dbgout("ISO9660: Reading directory.\n");
			FilesystemNodePointer ret;
			auto hl = iso9660_lock->LockExclusive();
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
			return ret;
		}
		return nullptr;
	}
	
	bool Write(IFilesystemNode &node) override{}
	size_t Seek(size_t pos, uint32_t flags) override{}
	FilesystemNodePointer GetNode() override{}

	void Close() override{}
	bool Wait() override{}
};

class ISOFilesystemNode : public IFilesystemNode{
private:
public:
	IFileHandle *OpenFile(uint32_t mode) override{}
	IDirectoryHandle *OpenDirectory(uint32_t mode) override{}

	const char *GetName() override{}
	void Rename(const char *newName) override{}
	bt_filesize_t GetSize() override{}
	fs_item_types GetType() override{}
};

class ISOMountedFilesystem : public IMountedFilesystem{
private:
	l9660_fs fs;
	IFileHandle *fh;
public:
	FilesystemNodePointer GetNode(const char *path) override{}
	void Flush() override{}
	bool Unmount() override{}
};

class ISOFilesystem : public IFilesystem{
public:
	IMountedFilesystem *Mount(FilesystemNodePointer node) override{}
	bool Format(const IFilesystemNode &node, void *options) override{}
};

static bool in_string(char c, const string &s){
	for(auto sc : s) if(sc == c) return true;
	return false;
}

static string shorten(const string &fname){
	size_t prelen = 0;
	size_t extstart = 0;
	size_t extlen = 0;
	bool inext = false;
	for(auto c : fname){
		if(!inext && c == '.'){
			extstart = prelen;
		}else{ 
			if(inext) ++extlen;
			else ++prelen;
		}
	}
	auto name = fname.substr(0, prelen > 8 ? 8 : prelen);
	if(extlen){
		auto ext = fname.substr(extstart, extlen > 3 ? 3 : extlen);
		name += ext;
	}
	return name;
}

static void filter_chars(string &path){
	const string allowed_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_.+";
	const char replacement = '_';
	for(auto &pc : path){
		if(pc >= 'a' && pc <= 'z') pc += ('A' - 'a');
		if(!in_string(pc, allowed_chars)) pc = replacement;
	}
}

size_t strlen(const char *s) {
	size_t i;
	for (i = 0; s[i] != '\0'; i++) ;
	return i;
}

string convert_path(const string &path){
	string ret;
	string cur_seg;
	for(auto c : path){
		if(c == '/' && !cur_seg.empty()){
			filter_chars(cur_seg);
			ret += '/';
			ret += shorten(cur_seg);
			cur_seg.clear();
		}else{
			cur_seg += c;
		}
	}
	if(!cur_seg.empty()){
			filter_chars(cur_seg);
			ret += shorten(cur_seg);
	}
	return ret;
}

string path_leaf(const string &path){
	string ret;
	for(auto c : path){
		if(c == '/') ret.clear();
		else ret += c;
	}
	return ret;
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
	bt_filesize_t pos = fseek(mount->fh, readaddr, false);
	if(pos != readaddr) panic("(ISO9660) Seek failure.");
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
			dbgpf("ISO9660: Failed to mount %s (status: %i)\n", path, s);
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


int module_main(char *params){
		init_lock(&iso9660_lock);
		add_filesystem(&iso9660_driver);
		return 0;
}
