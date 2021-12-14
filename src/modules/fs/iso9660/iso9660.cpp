#include <module/module.inc>
#include <module/utils/string.hpp>
#include <module/utils/fshelpers.hpp>

#include <util/scoped_ptr.hpp>

extern "C"{
	#include "lib9660.h"
}

#define MIN(a, b) ((a) < (b) ? (a) : (b))

constexpr size_t block_size = 2048;

using fs_path = vector<string>;

static fs_path split_path(const string &path){
	fs_path ret;
	string cur;
	for(auto c : path){
		if(c == '/'){
			if(!cur.empty()) ret.push_back(cur);
			cur.clear();
		}else{
			cur += c;
		}
	}
	if(!cur.empty()) ret.push_back(cur);
	return ret;
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

static bool in_string(char c, const string &s){
	for(auto sc : s) if(sc == c) return true;
	return false;
}

static string filter_chars(string path){
	const string allowed_chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_.+";
	const char replacement = '_';
	for(auto &pc : path){
		if(pc >= 'a' && pc <= 'z') pc += ('A' - 'a');
		if(!in_string(pc, allowed_chars)) pc = replacement;
	}
	return path;
}

static bt_filesize_t dual_to_le(l9660_duint32 dual){
	return *(bt_filesize_t*)dual.le;
}

static l9660_dir *get_parent(l9660_fs *fs, const fs_path &path){
	l9660_dir *parent = new l9660_dir();
	l9660_fs_open_root(parent, fs);
	for(auto p : path){
		l9660_dir *newparent = new l9660_dir();
		auto px = shorten(filter_chars(p));
		auto res = l9660_opendirat(newparent, parent, p.c_str());
		delete parent;
		if(res != L9660_OK){
			delete newparent;
			return nullptr;
		}
		parent = newparent;
	}
	return parent;
}

bool is_path_root(const fs_path &path){
	return (path.empty() || path[0].empty());
}

ILock *iso9660_lock;

class ISOFileHandle : public IFileHandle{
private:
	l9660_file *file;
	FilesystemNodePointer node;
public:
	ISOFileHandle(l9660_file *f) : file(f) {}

	~ISOFileHandle(){
		delete file;
	}

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


	void Close() override{}
	bool Wait() override{
		return false;
	}
};

class ISOFilesystemNode : public IFilesystemNode{
private:
	l9660_dir parent;
	char name[BT_MAX_SEGLEN + 1] = {0};
	bt_filesize_t size = 0;
	fs_item_types type = fs_item_types::FS_Invalid;

	bool root;
public:
	ISOFilesystemNode(l9660_dir *p, const char *n, bt_filesize_t s, fs_item_types t, bool r = false) : parent(*p), size(s), type(t), root(r){
		strncpy(name, n, BT_MAX_SEGLEN);
		replace_char(name, ';', '\0');
	}

	IFileHandle *OpenFile(uint32_t mode) override{
		if(type == FS_File){
			auto file = new l9660_file();
			auto status = l9660_openat(file, &parent, name);
			if(status != L9660_OK){
				delete file;
				return nullptr;
			}
			return new ISOFileHandle(file);
		}
		return nullptr;
	}
	IDirectoryHandle *OpenDirectory(uint32_t mode) override;

	const char *GetName() override{
		return name;
	}

	void Rename(const char *newName) override{}

	bt_filesize_t GetSize() override{
		return size;
	}

	fs_item_types GetType() override{
		return type;
	}
};

class ISODirectoryHandle : public IDirectoryHandle{
private:
	l9660_dir *dir;
	l9660_dirent *last_ent = nullptr;
	size_t dirsize = 0;

	FilesystemNodePointer node;
public:
	ISODirectoryHandle(l9660_dir *d, IFilesystemNode *n) : dir(d), node(n) {}

	~ISODirectoryHandle(){
		delete dir;
	}

	fs_item_types ReadType() override{
		if(!last_ent) return FS_Invalid;
		return (last_ent->flags & 0x02) ? FS_Directory : FS_File;
	}

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
				dbgpf("ISO9660: Filename '%s' Length: %i\n", ent.name, ent.name_len);
				ret = new ISOFilesystemNode(dir, ent.name, dual_to_le(ent.size), (ent.flags & 0x02) ? FS_Directory : FS_File);
				last_ent = pent;
			}
			return ret;
		}
		return nullptr;
	}
	
	bool Write(IFilesystemNode &node) override{
		return false;
	}

	size_t Seek(size_t pos, uint32_t flags) override{
		auto cpos = l9660_telldir(dir);
		if(dirsize == 0){
			l9660_seekdir(dir, 0);
			l9660_dirent *pent;
			while(l9660_readdir(dir, &pent) == L9660_OK) ++dirsize;
		}
		auto npos = FSHelpers::SeekPosition(pos, flags, cpos, dirsize);
		l9660_seekdir(dir, npos);
		return npos;
	}

	FilesystemNodePointer GetNode() override{
		return node;
	}

	void Close() override{}
	bool Wait() override{
		return false;
	}
};

IDirectoryHandle *ISOFilesystemNode::OpenDirectory(uint32_t mode){
	if(type == FS_Directory){
		auto dir = new l9660_dir();
		if(root){
			return new ISODirectoryHandle(&parent, this);
		}else{
			auto status = l9660_opendirat(dir, &parent, name);
			if(status != L9660_OK){
				delete dir;
				return nullptr;
			}
			return new ISODirectoryHandle(dir, this);
		}
	}
	return nullptr;
}

class ISOMountedFilesystem : public IMountedFilesystem{
private:
	struct DataStruct{
		l9660_fs fs; // Has to be first.
		ISOMountedFilesystem *thisPtr;
		IFileHandle *fh;
	} data;
public:
	ISOMountedFilesystem(FilesystemNodePointer node){
		data.thisPtr = this;
		data.fh = node->OpenFile(FS_Read);
		if(data.fh){
			auto status = l9660_openfs(&data.fs, [](struct l9660_fs *fs, void *buf, uint32_t sector) -> bool{
				auto d = (DataStruct*)fs;
				size_t readaddr = sector * block_size;
				auto pos = d->fh->Seek(readaddr, FS_Set);
				if(pos != readaddr) panic("(ISO9660) Seek failure.");
				auto ret = d->fh->Read(block_size, (char*)buf);
				if(ret == 0) panic("(ISO9660) Failed to read sector.");
				return (bool)ret;
			});
			if(status != L9660_OK) data.fh->Close();
		}
	}

	FilesystemNodePointer GetNode(const char *path) override{
		auto fsPath = split_path(path);
		if(is_path_root(fsPath)){
			auto dir = new l9660_dir();
			l9660_fs_open_root(dir, &data.fs);
			return new ISOFilesystemNode(dir, "", 0, FS_Directory);
		}else{
			scoped_ptr<l9660_dir> parent = get_parent(&data.fs, fsPath);
			scoped_ptr<l9660_file> file = new l9660_file();
			if(parent){
				auto status = l9660_openat(file.get(), parent.get(), fsPath.back().c_str());
				if(status == L9660_OK){
					l9660_seek(file.get(), L9660_SEEK_END, 0);
					auto size = l9660_tell(file.get());
					return new ISOFilesystemNode(parent.get(), fsPath.back().c_str(), size, FS_File);
				}else if(status == L9660_ENOTFILE){
					return new ISOFilesystemNode(parent.get(), fsPath.back().c_str(), 0, FS_Directory);
				}
			}
		}
		return nullptr;
	}
	void Flush() override{}
	bool Unmount() override{
		data.fh->Close();
		delete data.fh;
		data.fh = nullptr;
		return true;
	}
};

class ISOFilesystem : public IFilesystem{
public:
	IMountedFilesystem *Mount(FilesystemNodePointer node) override{
		return new ISOMountedFilesystem(node);
	}

	bool Format(const IFilesystemNode &node, void *options) override{
		return false;
	}
};

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

int module_main(char *){
	API->GetFilesystemManager().RegisterFilesystem("ISO9660", new ISOFilesystem());
	return 0;
}
