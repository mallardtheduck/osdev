#ifndef MODULE_FILESYSTEMS_HPP
#define MODULE_FILESYSTEMS_HPP

#include <module/kernelsys/handles.hpp>

class IFilesystemNode;
using FilesystemNodePointer = RefCountPointer<IFilesystemNode>;

class IFileHandle : public IHandle{
public:
	virtual uint32_t GetType(){
		return KernelHandles::File::id;
	}

	virtual size_t Read(size_t bytes, char *buffer) = 0;
	virtual size_t Write(size_t bytes, const char *buffer) = 0;

	virtual bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) = 0;
	virtual bool Resize(bt_filesize_t size) = 0;

	virtual int IOCtl(int fn, size_t bytes, char *buffer) = 0;

	virtual void Flush() = 0;

	virtual FilesystemNodePointer GetNode() = 0;

	virtual ~IFileHandle() {}
};

class IDirectoryHandle : public IHandle{
public:
	virtual uint32_t GetType(){
		return KernelHandles::Directory::id;
	}

	virtual fs_item_types ReadType() = 0;
	virtual FilesystemNodePointer Read() = 0;
	virtual bool Write(IFilesystemNode &node) = 0;
	virtual size_t Seek(size_t pos, uint32_t flags) = 0;
	virtual FilesystemNodePointer GetNode() = 0;

	virtual ~IDirectoryHandle() {}
};

class IFilesystemNode : private nonmovable{
private:
	size_t refcount = 0;
public:
	virtual IFileHandle *OpenFile(uint32_t mode) = 0;
	virtual IDirectoryHandle *OpenDirectory(uint32_t mode) = 0;

	virtual const char *GetName() = 0;
	virtual void Rename(const char *newName) = 0;
	virtual bt_filesize_t GetSize() = 0;
	virtual fs_item_types GetType() = 0;

	virtual void IncrementRefCount(){
		++refcount;
	}

	virtual void DecrementRefCount(){
		if(--refcount == 0) delete this;
	}

	virtual ~IFilesystemNode() {}
};

class IMountedFilesystem : private nonmovable{
public:
	virtual FilesystemNodePointer GetNode(const char *path) = 0;
	virtual void Flush() = 0;
	virtual bool Unmount() = 0;

	virtual ~IMountedFilesystem() {}
};

class IFilesystem : private nonmovable{
public:
	virtual IMountedFilesystem *Mount(FilesystemNodePointer node) = 0;
	virtual bool Format(const IFilesystemNode &node, void *options) = 0;

	virtual ~IFilesystem() {}
};

class IVirtualFilesystem : private nonmovable{
public:
	virtual bool Attach(const char *name, IMountedFilesystem *mount) = 0;
	virtual IMountedFilesystem *Detach(const char *name) = 0;
	virtual IMountedFilesystem *GetByName(const char *name) = 0;

	virtual FilesystemNodePointer GetNode(const char *path) = 0;

	IFileHandle *OpenFile(const char *path, fs_mode_flags mode){
		auto node = GetNode(path);
		if(node){
			auto ret = node->OpenFile(mode);
			return ret;
		}
		return nullptr;
	}

	virtual ~IVirtualFilesystem() {}
};

class IFilesystemManager : private nonmovable{
public:
	virtual void RegisterFilesystem(const char *name, IFilesystem *fs) = 0;
	virtual IFilesystem *UnRegisterFileystem(const char *name) = 0;
	virtual IFilesystem *GetByName(const char *name) = 0;

	virtual ~IFilesystemManager() {}
};

#endif