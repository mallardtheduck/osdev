#include "kernel.hpp"
#include "filesystems.hpp"
#include "utils/ministl.hpp"
#include "locks.hpp"
#include <util/asprintf.h>

static bool IsNameValid(const char *name){
	static constexpr auto validNameChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_1234567890";

	size_t len = 0;
	while(name && *name){
		auto search = validNameChars;
		while(*name != *search){
			++search;
			if(!*search) return false;
		}
		++name; ++len;
	}
	return len > 0;
}

class VirtualFilesystem : public IVirtualFilesystem{
private:
	map<string, IMountedFilesystem*> mounts;
	ILock *lock = NewLock();

	static char *InfoFS();
public:
	VirtualFilesystem(){
		InfoRegister("MOUNTS", &InfoFS);
	}

	bool Attach(const char *name, IMountedFilesystem *mount) override{
		if(!IsNameValid(name)) return false;
		auto hl = lock->LockExclusive();
		if(mounts.has_key(name)) return false;
		mounts[name] = mount;
		return true;
	}

	IMountedFilesystem *Detach(const char *name) override{
		auto hl = lock->LockExclusive();
		if(!mounts.has_key(name)) return nullptr;
		auto mount = mounts[name];
		mounts.erase(name);
		return mount;
	}

	IMountedFilesystem *GetByName(const char *name) override{
		if(!IsNameValid(name)) return nullptr;
		auto hl = lock->LockExclusive();
		if(!mounts.has_key(name)) return nullptr;
		return mounts[name];
	}

	FilesystemNodePointer GetNode(const char *path) override{
		string pathString = path;
		string mountName;
		auto pathPtr = path;
		while(pathPtr && *pathPtr && *pathPtr != ':'){
			mountName += *pathPtr;
		}
		if(*pathPtr != ':' || IsNameValid(mountName.c_str())) return nullptr;
		if(pathString.length() < mountName.length() + 2) return nullptr;
		auto pathPart = pathString.substr(mountName.length() + 1, pathString.length() - mountName.length() - 1);
		auto hl = lock->LockExclusive();
		if(!mounts.has_key(mountName.c_str())) return nullptr;
		auto mount = mounts[mountName];
		return mount->GetNode(pathPart.c_str());
	}
};

class FilesystemManager : public IFilesystemManager{
private:
	map<string, IFilesystem*> filesystems;
	ILock *lock = NewLock();

	static char *InfoFS();
public:
	FilesystemManager(){
		InfoRegister("FILESYSTEMS", &InfoFS);
	}

	void RegisterFilesystem(const char *name, IFilesystem *fs) override{
		auto hl = lock->LockExclusive();
		if(IsNameValid(name) && !filesystems.has_key(name)) filesystems[name] = fs;
	}

	IFilesystem *UnRegisterFileystem(const char *name) override{
		auto hl = lock->LockExclusive();
		if(filesystems.has_key(name)){
			auto fs = filesystems[name];
			filesystems.erase(name);
			return fs;
		}
		return nullptr;
	}

	IFilesystem *GetByName(const char *name) override{
		if(!IsNameValid(name)) return nullptr;
		auto hl = lock->LockExclusive();
		if(filesystems.has_key(name)) return filesystems[name];
		return nullptr;
	}
};

static ManualStaticAlloc<VirtualFilesystem> theVirtualFilesystem;
static ManualStaticAlloc<FilesystemManager> theFilesystemManager;

void Filesystem_Init(){
	theFilesystemManager.Init();
	theVirtualFilesystem.Init();
}

IVirtualFilesystem &GetVirtualFilesystem(){
	return *theVirtualFilesystem;
}

IFilesystemManager &GetFilesystemManager(){
	return *theFilesystemManager;
}


char *VirtualFilesystem::InfoFS(){
	auto hl = theVirtualFilesystem->lock->LockExclusive();
	char *buffer=nullptr;
	asprintf(&buffer, "# name, device, filesystem\n");
	for(auto &mount : theVirtualFilesystem->mounts){
		reasprintf_append(&buffer, "%s, %s, %s\n", mount.first.c_str(), "???", "NEWFS");
	}
	return buffer;
}

char *FilesystemManager::InfoFS(){
	auto hl = theFilesystemManager->lock->LockExclusive();
	char *buffer=nullptr;
	asprintf(&buffer, "# name, addr\n");
	for(auto &fs : theFilesystemManager->filesystems){
		reasprintf_append(&buffer, "%s, %p\n", fs.first.c_str(), fs.second);
	}
	return buffer;
}
