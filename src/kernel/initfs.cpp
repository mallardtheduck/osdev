#include "initfs.hpp"
#include "kernel.hpp"
#include "utils/fshelpers.hpp"

#define isspace(c) ((c) == ' ')
#define isodigit(c) ((c) >= '0' && (c) <= '7')

struct initfs_file{
	string name;
	unsigned char *data;
	size_t size;
};

ManualStaticAlloc<vector<initfs_file>> initfs_data;

class InitFSNode : public IFilesystemNode{
private:
	initfs_file *file;
public:
	InitFSNode(initfs_file *f) : file(f) {}

	IFileHandle *OpenFile(uint32_t mode) override;

	IDirectoryHandle *OpenDirectory(uint32_t mode) override;

	const char *GetName() override{
		return file->name.c_str();
	}

	void Rename(const char *) override{}

	bt_filesize_t GetSize() override{
		return file->size;
	}

	fs_item_types GetType() override{
		return FS_File;
	}
};

class InitFSFileHandle : public IFileHandle{
private:
	initfs_file *file;
	size_t pos;
	FilesystemNodePointer node;
public:
	InitFSFileHandle(initfs_file *f, FilesystemNodePointer n) : file(f), pos(0), node(n) {}

	size_t Read(size_t bytes, char *buffer) override{
		if(pos > file->size) return 0;
		if(pos + bytes > file->size) bytes = file->size - pos;
		size_t j=0;
		for(size_t i = pos; i < file->size && j < bytes; ++i, ++j){
			buffer[j]=file->data[i];
		}
		pos += j;
		return j;
	}

	size_t Write(size_t, const char *) override{
		return 0;
	}

	bt_filesize_t Seek(bt_filesize_t p, uint32_t flags) override{
		pos = FSHelpers::SeekPosition(p, flags, pos, file->size);
		return pos;
	}

	bool Resize(bt_filesize_t) override{
		return false;
	}

	int IOCtl(int, size_t, char *) override{
		return 0;
	}

	void Flush() override {}

	FilesystemNodePointer GetNode() override{
		return node;
	}

	void Close() override {}

	bool Wait() override {
		return false;
	}
};

class InitFSDirectoryHandle : public IDirectoryHandle{
private:
	size_t pos = 0;
public:
	fs_item_types ReadType() override{
		if(pos >= initfs_data->size()){
			dbgout("INITFS: No such directory entry.\n");
			return FS_Invalid;
		}
		return FS_File;
	}

	FilesystemNodePointer Read() override{
		if(pos >= initfs_data->size()){
			dbgout("INITFS: No such directory entry.\n");
			return nullptr;
		}
		initfs_file *file = &initfs_data->at(pos);
		FilesystemNodePointer ret = new InitFSNode(file);
		++pos;
		return ret;
	}

	bool Write(IFilesystemNode &) override{
		return false;
	}

	size_t Seek(size_t p, uint32_t flags) override{
		pos = FSHelpers::SeekPosition(p, flags, pos, initfs_data->size());
		return pos;
	}

	FilesystemNodePointer GetNode() override{
		return new InitFSNode(nullptr);
	}

	void Close() override {}

	bool Wait() override{
		return false;
	}
};

IFileHandle *InitFSNode::OpenFile(uint32_t mode){
	if(file) return new InitFSFileHandle(file, this);
	else return nullptr;
}

IDirectoryHandle *InitFSNode::OpenDirectory(uint32_t mode){
	if(!file) return new InitFSDirectoryHandle();
	else return nullptr;
}

bool IsMatch(const string &a, const string &b){
	size_t aPos = 0, bPos = 0;
	while(a.size() > aPos && a[aPos] == '/') ++aPos;
	while(b.size() > bPos && b[bPos] == '/') ++bPos;
	while(a.size() > aPos && b.size() > bPos && to_upper(a[aPos]) == to_upper(b[bPos])){
		++aPos;
		++bPos;
	}
	dbgpf("a: '%s' (%lu) b: '%s' (%lu) aPos: %lu bPos: %lu\n", a.c_str(), a.size(), b.c_str(), b.size(), aPos, bPos);
	return (a.size() == aPos && b.size() == bPos);
}

class MountedInitFS : public IMountedFilesystem{
public:
	FilesystemNodePointer GetNode(const char *path) override{
		dbgpf("INITFS: GetNode: %s\n", path);
		string spath = path;
		dbgpf("%i %i\n", (int)(spath == ""), (int)(spath == "/"));
		if(spath == "" || spath == "/") return new InitFSNode(nullptr);
		for(auto &file : *initfs_data){
			if(IsMatch(file.name, spath)) return new InitFSNode(&file);
		}
		return nullptr;
	}

	void Flush() override{}
	bool Unmount() override{
		return true;
	}
};

class InitFS : public IFilesystem{
public:
	IMountedFilesystem *Mount(FilesystemNodePointer node) override{
		return new MountedInitFS();
	}

	bool Format(const IFilesystemNode &node, void *options) override{
		return false;
	}
};

struct tar_header{
	char filename[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag[1];
};

long from_oct(int digs, const char *where){
	long	value;

	while (isspace((unsigned)*where)) {		/* Skip spaces */
		where++;
		if (--digs <= 0)
			return -1;		/* All blank field */
	}
	value = 0;
	while (digs > 0 && isodigit(*where)) {	/* Scan til nonoctal */
		value = (value << 3) | (*where++ - '0');
		--digs;
	}

	if (digs > 0 && *where && !isspace((unsigned)*where))
		return -1;			/* Ended on non-space/nul */

	return value;
}

size_t tar_size(const char *in){
	return from_oct(12, in);
}

static ManualStaticAlloc<InitFS> theInitFS;

IFilesystem *InitFSGet(){
	if(!initfs_data){
		initfs_data.Init();
		multiboot_info_t *mbi = mbt;
		if(mbi->mods_count > 0){
			module_t *mod = (module_t *)mbi->mods_addr;
			tar_header *th = (tar_header*)mod->mod_start;
			dbgpf("INITFS: Module starts at %x and ends at %x\n", (int)mod->mod_start, (int)mod->mod_end);
			while((uint32_t)th < mod->mod_end){
				if(th->filename[0] == '\0') break;
				unsigned char *data = (unsigned char*)((uint32_t)th + 512);
				size_t size = tar_size(th->size);
				dbgpf("INITFS: %s, %x, %i\n", th->filename, (int)data, (int)size);
				initfs_file file;
				file.data = data;
				file.name = th->filename;
				file.size = size;
				initfs_data->push_back(file);
				th = (tar_header*)((uint32_t) data + (512 * (size % 512 ? (size / 512) + 1 : size / 512)));
			}
		}else{
			panic("(INITFS) No tar module loaded!");
		}
	}
	if(!theInitFS) theInitFS.Init();
	return theInitFS;
}

void InitFS_Init(){
	auto mount = InitFSGet()->Mount(nullptr);
	GetVirtualFilesystem().Attach("INIT", mount);
}
