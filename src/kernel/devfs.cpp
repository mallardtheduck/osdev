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

	IFileHandle *OpenFile(fs_mode_flags mode) override{
		auto inst = device->Open();
		if(inst) return new DevFSFileHandle(this, inst);
		else return nullptr;
	}

	IDirectoryHandle *OpenDirectory(fs_mode_flags mode) override{
		if(device == nullptr) return new DevFSDirectoryHandle(this);
		else return nullptr;
	}

	const char *GetName() override{
		return device->GetName();
	}

	void Rename(const char *) override{}

	bt_filesize_t GetSize() override{
		return 0;
	}

	fs_item_types GetType() override{
		return FS_Device;
	}
};

FilesystemNodePointer DevFSDirectoryHandle::Read(){
	if(it != GetVisibleDeviceManager().end()) return new DevFSNode(it);
	else return nullptr;
	++it;
}

class MountedDevFS : public IMountedFilesystem{
public:
	FilesystemNodePointer GetNode(const char *path) override{
		if(string(path) == "") return new DevFSNode(nullptr);
		for(auto &device : GetVisibleDeviceManager()){
			if(device.GetName() == path) return new DevFSNode(&device);
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
	IMountedFilesystem *Mount(const IFilesystemNode &node) override{
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