#ifndef _FILESYSTEMS_HPP
#define _FILESYSTEMS_HPP

#include "kernel.hpp"
#include <btos/fs_interface.h>

class IFilesystemNode;

class IFileHandle : public IHandle{
public:
	virtual size_t Read(size_t bytes, char *buffer) = 0;
	virtual size_t Write(size_t bytes, const char *buffer) = 0;

	virtual bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) = 0;
	virtual bool Resize(bt_filesize_t size) = 0;

	virtual int IOCtl(int fn, size_t bytes, char *buffer) = 0;

	virtual void Flush() = 0;

	virtual IFilesystemNode *GetNode() = 0;

	virtual ~IFileHandle() {}
};

class IDirectoryHandle : public IHandle{
public:
	virtual fs_item_types ReadType() = 0;
	virtual IFilesystemNode *Read() = 0;
	virtual bool Write(IFilesystemNode &node) = 0;
	virtual size_t Seek(size_t pos, uint32_t flags) = 0;
	virtual IFilesystemNode *GetNode() = 0;

	virtual ~IDirectoryHandle() {}
};

class IFilesystemNode{
public:
	virtual IFileHandle *OpenFile(fs_mode_flags mode) = 0;
	virtual IDirectoryHandle *OpenDirectory(fs_mode_flags mode) = 0;

	virtual const char *GetName() = 0;
	virtual void Rename(const char *newName) = 0;
	virtual bt_filesize_t GetSize() = 0;
	virtual fs_item_types GetType() = 0;

	virtual ~IFilesystemNode() {}
};

class IMountedFilesystem{
public:
	virtual IFilesystemNode *GetNode(const char *path) = 0;
	virtual void Flush() = 0;
	virtual bool Unmount() = 0;

	virtual ~IMountedFilesystem() {}
};

class IFilesystem{
public:
	virtual IMountedFilesystem *Mount(const IFilesystemNode &node) = 0;
	virtual bool Format(const IFilesystemNode &node, void *options) = 0;

	virtual ~IFilesystem() {}
};

class IVirtualFilesystem{
public:
	virtual bool Attach(const char *name, IMountedFilesystem *mount) = 0;
	virtual IMountedFilesystem *Detach(const char *name) = 0;
	virtual IMountedFilesystem *GetByName(const char *name) = 0;

	virtual IFilesystemNode *GetNode(const char *path) = 0;

	virtual ~IVirtualFilesystem() {}
};

class IFilesystemManager{
public:
	virtual void RegisterFilesystem(const char *name, IFilesystem *fs) = 0;
	virtual IFilesystem *UnRegisterFileystem(const char *name) = 0;
	virtual IFilesystem *GetByName(const char *name) = 0;

	virtual ~IFilesystemManager() {}
};

void Filesystem_Init();
IVirtualFilesystem &GetVirtualFilesystem();
IFilesystemManager &GetFilesystemManager();

#endif
