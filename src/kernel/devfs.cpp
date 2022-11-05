#include "kernel.hpp"
#include <btos/ioctl.h>
#include "utils/fshelpers.hpp"

void* const devfs_magic=(void*)0xDE7F5;
void* const devfs_dirmagic=(void*)0xDE7D19;

class DevFSFileHandle : public IFileHandle{
public:
	FilesystemNodePointer node;
	IVisibleDeviceInstance *inst;
public:
	DevFSFileHandle(FilesystemNodePointer n, IVisibleDeviceInstance *i) : node(n), inst(i) {}

	size_t Read(size_t bytes, char *buffer) override{
		return inst->Read(bytes, buffer);
	}

	size_t Write(size_t bytes, const char *buffer) override{
		return inst->Write(bytes, buffer);
	}

	bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) override{
		return inst->Seek(pos, flags);
	}

	bool Resize(bt_filesize_t) override{
		return false;
	}

	int IOCtl(int fn, size_t bytes, char *buffer) override{
		if(fn == bt_ioctl::DevType){
			return inst->GetType();
		}else if(fn==bt_ioctl::DevDesc){
			memcpy(buffer, inst->GetDescription(), bytes-1);
			buffer[bytes - 1] = '\0';
			return strlen(inst->GetDescription());
		}else{
			return inst->IOCtl(fn, bytes, buffer);
		}
	}

	void Flush() override {}

	FilesystemNodePointer GetNode() override{
		return node;
	}

	void Close() override{
		delete inst;
	}

	bool Wait() override{
		return false;
	}
};

class DevFSDirectoryHandle : public IDirectoryHandle{
private:
	VisibleDeviceIteratorWrapper it;
	FilesystemNodePointer node;
public:
	DevFSDirectoryHandle(FilesystemNodePointer n) : it(GetVisibleDeviceManager().begin()), node(n) {}

	fs_item_types ReadType() override{
		if(it != GetVisibleDeviceManager().end()) return FS_Device;
		else return FS_Invalid;
	}

	FilesystemNodePointer Read() override;

	bool Write(IFilesystemNode &) override{
		return false;
	}

	size_t Seek(size_t pos, uint32_t flags) override{
		return FSHelpers::SeekIterator(pos, flags, it, GetVisibleDeviceManager().begin(), GetVisibleDeviceManager().end());
	}

	FilesystemNodePointer GetNode() override{
		return node;
	}

	void Close() override{}

	bool Wait() override{
		return false;
	}
};

class DevFSNode : public IFilesystemNode{
private:
	IVisibleDevice *device;
public:
	DevFSNode(IVisibleDevice *d) : device(d) {}

	IFileHandle *OpenFile(uint32_t mode) override{
		auto inst = device->Open();
		if(inst) return new DevFSFileHandle(this, inst);
		else return nullptr;
	}

	IDirectoryHandle *OpenDirectory(uint32_t mode) override{
		if(!device) return new DevFSDirectoryHandle(this);
		else return nullptr;
	}

	IFileHandle *CreateFile(const char *, uint32_t) override{
		return nullptr;
	}

	IDirectoryHandle *CreateDirectory(const char *, uint32_t) override{
		return nullptr;
	}

	const char *GetName() override{
		if(!device) return "";
		else return device->GetName();
	}

	void Rename(const char *) override{}

	bt_filesize_t GetSize() override{
		return 0;
	}

	fs_item_types GetType() override{
		if(!device) return FS_Directory;
		else return FS_Device;
	}
};

FilesystemNodePointer DevFSDirectoryHandle::Read(){
	if(it != GetVisibleDeviceManager().end()){
		return new DevFSNode(it++);
	}
	else return nullptr;
}

static bool IsMatch(const string &a, const string &b){
	size_t aPos = 0, bPos = 0;
	while(a.size() > aPos && a[aPos] == '/') ++aPos;
	while(b.size() > bPos && b[bPos] == '/') ++bPos;
	while(a.size() > aPos && b.size() > bPos && to_upper(a[aPos]) == to_upper(b[bPos])){
		++aPos;
		++bPos;
	}
	return (a.size() == aPos && b.size() == bPos);
}

class MountedDevFS : public IMountedFilesystem{
public:
	FilesystemNodePointer GetNode(const char *path) override{
		string p = path;
		if(p == "" || p == "/") return new DevFSNode(nullptr);
		for(auto &device : GetVisibleDeviceManager()){
			if(IsMatch(device.GetName(), path)) return new DevFSNode(&device);
		}
		return nullptr;
	}

	void Flush() override{}
	bool Unmount() override{
		return true;
	}
};

class DevFS : public IFilesystem{
public:
	IMountedFilesystem *Mount(FilesystemNodePointer node) override{
		return new MountedDevFS();
	}

	bool Format(const IFilesystemNode &node, void *options) override{
		return false;
	}
};

static ManualStaticAlloc<DevFS> theDevFS;

IFilesystem *DevFSGet(){
	if(!theDevFS) theDevFS.Init();
	return theDevFS;
}

void DevFS_Init(){
	auto mount = DevFSGet()->Mount(nullptr);
	GetVirtualFilesystem().Attach("DEV", mount);
}