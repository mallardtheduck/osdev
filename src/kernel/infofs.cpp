#include "kernel.hpp"
#include <util/ministl.hpp>
#include "utils/fshelpers.hpp"

void* const infofs_magic=(void*)0x14F0F5;

char *Info_Kernel(){
	char* buffer=(char*)malloc(128);
	sprintf(buffer, "%s %s (Build ID:%s)\n%s\n", KERNEL_OS_NAME, KERNEL_VERSION_STRING, kernel_buildid, KERNEL_COPYRIGHT);
	return buffer;
}

char *Info_CPU(){
	char* buffer=(char*)malloc(256);
	sprintf(buffer, "%s %s\n", GetHAL().CPUIDString(), "");//cpu_brandstring());
	return buffer;
}

static map<string, function<char*()>> infoItems;

class InfoFSNode;

class InfoFSHandle : public IFileHandle{
private:
	char *data;
	size_t size, pos;

	FilesystemNodePointer node;
public:
	InfoFSHandle(char *d, size_t s, size_t p, FilesystemNodePointer n) : data(d), size(s), pos(p), node(n) {}

	void Close() override{
		size = 0;
		pos = 0;
		if(data){
			free(data);
			data = nullptr;
		}
	}

	bool Wait() override{
		return true;
	}

	size_t Read(size_t bytes, char *buffer){
		auto readsize = min(bytes, size - pos);
		memcpy(buffer, data + pos, readsize);
		pos += readsize;
		return readsize;
	}

	size_t Write(size_t, const char *) override{
		return 0;
	}

	bt_filesize_t Seek(bt_filesize_t p, uint32_t flags) override{
		pos = FSHelpers::SeekPosition(p, flags, pos, size);
		return pos;
	}

	bool Resize(bt_filesize_t size) override{
		return false;
	}

	int IOCtl(int, size_t, char *) override{
		return 0;
	}

	void Flush() override {}

	FilesystemNodePointer GetNode() override{
		return node;
	}

	uint32_t GetMode() override{
		return FS_Read;
	}

	~InfoFSHandle(){
		Close();
	}
};

class InfoFSDirectory;

class InfoFSNode : public IFilesystemNode{
private:
	friend class InfoFSDirectory;
	friend class InfoFSMount;

	function<char*()> fn;
	string name;
	bool isDirectory = false;

	InfoFSNode(function<char*()> f, string n, bool iD) : fn(f), name(n), isDirectory(iD) {}
public:
	IFileHandle *OpenFile(uint32_t mode) override{
		if(isDirectory) return nullptr;
		if(mode & FS_WriteFlags) return nullptr;

		auto data = fn();
		auto size = strlen(data);
		auto pos = (mode & FS_AtEnd) ? size : 0;
		return new InfoFSHandle(data, size, pos, this);
	}

	IFileHandle *CreateFile(const char *, uint32_t) override{
		return nullptr;
	}

	IDirectoryHandle *CreateDirectory(const char *, uint32_t) override{
		return nullptr;
	}

	IDirectoryHandle *OpenDirectory(uint32_t mode) override;

	const char *GetName() override{
		return name.c_str();
	}

	void Rename(const char *) override{
	}

	bt_filesize_t GetSize() override{
		return 0;
	}

	fs_item_types GetType() override{
		return isDirectory ? FS_Directory : FS_File;
	}
};

class InfoFSDirectory : public IDirectoryHandle{
private:
	decltype(infoItems)::iterator pos;

public:
	InfoFSDirectory(){
		pos = infoItems.begin();
	}

	void Close() override {}
	bool Wait(){
		return false;
	}

	fs_item_types ReadType() override{
		if(pos != infoItems.end()) return FS_File;
		else return FS_Invalid;
	}

	FilesystemNodePointer Read() override{
		if(pos != infoItems.end()){
			auto ret = new InfoFSNode(pos->second, pos->first, false);
			++pos;
			return ret;
		}else return nullptr;
	}

	bool Write(IFilesystemNode &) override{
		return false;
	}

	size_t Seek(size_t p, uint32_t flags) override{
		size_t idx = 0;
		for(auto it = infoItems.begin(); it != pos && it != infoItems.end(); ++it, ++idx);
		auto npos = FSHelpers::SeekPosition(p, flags, idx, infoItems.size());
		pos = infoItems.begin();
		for(size_t i = 0; i < npos; ++i, ++pos);
		return npos;
	}

	FilesystemNodePointer GetNode() override{
		return new InfoFSNode(nullptr, "", true);
	}
};

IDirectoryHandle *InfoFSNode::OpenDirectory(uint32_t mode){
	if(mode & FS_WriteFlags) return nullptr;

	if(isDirectory) return new InfoFSDirectory();
	else return nullptr;
}

static bool IsMatch(const string &file, string query){
	if(!query.length()) return false;
	if(query[0] == '/') query = query.substr(1, query.length() - 1);
	return to_upper(file) == to_upper(query);
}

class InfoFSMount : public IMountedFilesystem{
private:
public:
	FilesystemNodePointer GetNode(const char *path) override{
		string p = path;
		if(p == "" || p == "/") return new InfoFSNode(nullptr, "", true);
		else{
			for(auto &info : infoItems){
				if(IsMatch(info.first, p)){
					return new InfoFSNode(info.second, info.first, false);
				}
			}
			return nullptr;
		}
	}

	void Flush() override {}
	bool Unmount(){
		return false;
	}

	IFilesystem *FileSystem(){
		return nullptr;
	}
	const char *Device(){
		return "N/A";
	}
};

void InfoRegister(const char *name, function<char*()> fn){
	infoItems[name] = fn;
}

void Info_Init(){
	GetVirtualFilesystem().Attach("INFO", new InfoFSMount());
	InfoRegister("VERSION", &Info_Kernel);
	InfoRegister("CPUID", &Info_CPU);
}