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

class MountedInitFS : public IMountedFilesystem{
public:
	FilesystemNodePointer GetNode(const char *path) override{
		if(string(path) == "") return new InitFSNode(nullptr);
		for(auto &file : *initfs_data){
			if(file.name == path) return new InitFSNode(&file);
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

struct initfs_handle{
	size_t fileindex;
	size_t pos;
	initfs_handle(size_t index, size_t p=0) : fileindex(index), pos(p) {}
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

#if 0

#define fdata ((initfs_handle*)filedata)

struct initfs_dirhandle{
	size_t pos;
	initfs_dirhandle(size_t p=0) : pos(p) {}
};

#define ddata ((initfs_dirhandle*)dirdata)

size_t initfs_getfilecount(){
	return initfs_data->size();
}

initfs_file initfs_getfile(int index){
	return (*initfs_data)[index];
}

void *initfs_mount(char *){
	dbgout("INITFS: Mounted.\n");
	return (void*)1;
}

bool initfs_unmount(void *){
	return true;
}

void *initfs_open(void *, fs_path *path, fs_mode_flags){
	dbgpf("INITFS: Open %s.\n", path->str);
	int files=initfs_getfilecount();
	for(int i=0; i<files; ++i){
		initfs_file file=initfs_getfile(i);
		if(to_upper(file.name) == to_upper(path->str)){
			return (void*)new initfs_handle(i);
		}
	}
	return NULL;
}



void *initfs_open_dir(void *, fs_path *path, fs_mode_flags){
	if(path->next != NULL) return NULL;
	return (void*)new initfs_dirhandle;
}
bool initfs_close_dir(void *dirdata){
	delete (initfs_dirhandle*)ddata;
	return true;
}

directory_entry initfs_read_dir(void *dirdata){
	directory_entry ret;
	if(ddata->pos>=initfs_getfilecount()){
		ret.valid=false;
		dbgout("INITFS: No such directory entry.\n");
		return ret;
	}
	initfs_file file=initfs_getfile(ddata->pos);
	strncpy(ret.filename, file.name.c_str(), 255);
	ret.id = (uint64_t)file.data;
	ret.size=file.size;
	ret.type=FS_File;
	ret.valid=true;
	ddata->pos++;
	return ret;
}

bool initfs_write_dir(void *, directory_entry){
	return false;
}

directory_entry initfs_stat(void *, fs_path *path){
	dbgpf("INITFS: Stat '%s'.\n",path->str);
	if(*(path->str)=='\0'){
		dbgout("INITFS: Stat root.\n");
		directory_entry ret;
		ret.filename[0]='\0';
		ret.id = 0;
		ret.size=initfs_getfilecount();
		ret.type=FS_Directory;
		ret.valid=true;
		return ret;
	}else{
		int files=initfs_getfilecount();
		for(int i=0; i<files; ++i){
			initfs_file file=initfs_getfile(i);
			if(to_upper(file.name) == to_upper(path->str)){
				initfs_dirhandle dh(i);
				return initfs_read_dir(&dh);
			}
		}
		directory_entry ret;
		ret.valid=false;
		return ret;
	}
}

bt_filesize_t initfs_seek(void *filedata, bt_filesize_t pos, uint32_t flags){
	if(flags & FS_Relative) fdata->pos+=pos;
	else if(flags & FS_Backwards){
		initfs_file file=initfs_getfile(fdata->fileindex);
		fdata->pos = file.size - pos;
	} else if(flags == (FS_Backwards | FS_Relative)) fdata->pos-=pos;
	else fdata->pos=pos;
	return fdata->pos;
}

bool initfs_seek(void *filedata, bt_filesize_t size){
	return false;
}

size_t initfs_dirseek(void *dirdata, size_t pos, uint32_t flags){
	if(flags & FS_Relative) ddata->pos+=pos;
	else if(flags & FS_Backwards){
		ddata->pos = initfs_getfilecount() - pos;
	} else if(flags == (FS_Backwards | FS_Relative)) ddata->pos-=pos;
	else ddata->pos=pos;
	return ddata->pos;
}

bool initfs_format(char*, void*){
	return false;
}

fs_driver initfs_driver = {true, (char*)"INITFS", false,
	initfs_mount, initfs_unmount,
	initfs_open, initfs_close, initfs_read, initfs_write, initfs_seek, initfs_seek, initfs_ioctl, initfs_flush,
	initfs_open_dir, initfs_close_dir, initfs_read_dir, initfs_write_dir, initfs_dirseek,
	initfs_stat, initfs_format};

fs_driver initfs_getdriver(){
	if(!initfs_data){
		initfs_data = new vector<initfs_file>();
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
	return initfs_driver;
}
#endif