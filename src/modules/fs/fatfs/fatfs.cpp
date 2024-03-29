#include <module/module.inc>
#include <module/utils/string.hpp>
#include <module/utils/fshelpers.hpp>

#include "drive.hpp"

#include "ff.h"

class FatFSMountedFilesystem;
class FatFSFilesystem;

FatFSFilesystem *theFilesystem;

static FilesystemNodePointer CreateNode(FilesystemNodePointer node, const string &path);
FilesystemNodePointer GetNodeLocal(FatFSMountedFilesystem *mount, const char *path);

static string PathConcat(const string &stem, const string &leaf){
	if(stem.empty()) return leaf;
	if(stem[stem.length() - 1] == '/'){
		return stem + leaf;
	}else{
		return stem + '/' + leaf;
	}
}

static void itoa(uint32_t num, char *s){
    char* cp;
    char outbuf[12];
    const char digits[] = "0123456789ABCDEF";

    // Build string backwards
    cp = outbuf;
    do
    {
        *cp++ = digits[(int)(num % 10)];
    }
    while ((num /= 10) > 0);

    *cp-- = 0;

    // Copy in forwards
    while (cp >= outbuf)
        *s++ = *cp--;

    *s = 0;
}

class FatFSFileHandle : public IFileHandle{
private:
	FIL fp;

	string path;
	FilesystemNodePointer node;
	bool del = false;
	uint32_t mode;
public:
	FatFSFileHandle(const string &p, uint32_t m, IFilesystemNode *n) : path(p), node(n), mode(m){
		uint8_t fmode = 0;
		if(mode & fs_mode_flags::FS_Read) fmode |= FA_READ;
		if(mode & fs_mode_flags::FS_Write) fmode |= FA_WRITE;

		if(mode & fs_mode_flags::FS_Create) fmode |= FA_OPEN_ALWAYS;
		if(mode & fs_mode_flags::FS_Truncate) fmode |= FA_CREATE_ALWAYS;

		if(mode & fs_mode_flags::FS_AtEnd) fmode |= FA_OPEN_APPEND;
		/* auto res = */ f_open(&fp, path.c_str(), fmode);
		// dbgpf("FATFS: Open: %s mode: %lu (%i) Result: %i\n", path.c_str(), mode, (int)fmode, res);
		if(mode & fs_mode_flags::FS_Delete) del = true;
	}
	size_t Read(size_t bytes, char *buffer) override{
		unsigned int read = 0;
		auto res = f_read(&fp, buffer, bytes, &read);
		if(res != FR_OK) dbgpf("FATFS: Read failure (\"%s\", %i, %i)!\n", path.c_str(), bytes, res);
		return read;
	}
	size_t Write(size_t bytes, const char *buffer) override{
		unsigned int written = 0;
		auto res = f_write(&fp, buffer, bytes, &written);
		if(res != FR_OK) dbgpf("FATFS: Write failure (\"%s\", %i, %lu) %i!\n", path.c_str(), bytes, res, written);
		return written;
	}

	bt_filesize_t Seek(bt_filesize_t pos, uint32_t flags) override{
		auto cpos = f_tell(&fp);
		auto size = f_size(&fp);
		auto npos = FSHelpers::SeekPosition(pos, flags, cpos, size);
		f_lseek(&fp, npos);
		return npos;
	}
	bool Resize(bt_filesize_t size) override{
		auto cpos = f_tell(&fp);
		f_lseek(&fp, size);
		auto res = f_truncate(&fp);
		f_lseek(&fp, cpos);
		return res == 0;
	}

	int IOCtl(int /*fn*/, size_t /*bytes*/, char * /*buffer*/) override{
		return 0;
	}

	void Flush() override{
		f_sync(&fp);
	}

	FilesystemNodePointer GetNode() override{
		return node;
	}

	uint32_t GetMode() override{
		return mode;
	}

	void Close() override{
		f_close(&fp);
		if(del) f_unlink(path.c_str());
	}

	bool Wait() override{
		return false;
	}
};

class FatFSDirectoryHandle : public IDirectoryHandle{
private:
	DIR dp;
	FILINFO fno;
	string path;

	FilesystemNodePointer node;
	bt_filesize_t cpos = 0;
	bool del = false;
public:
	FatFSDirectoryHandle(const string &p, uint32_t mode, IFilesystemNode *n) : path(p), node(n){
		if(mode & fs_mode_flags::FS_Delete) del = true;
		f_opendir(&dp, path.c_str());
	}

	fs_item_types ReadType() override{
		if(fno.fattrib & AM_DIR) return fs_item_types::FS_Directory;
		else return fs_item_types::FS_File;
	}
	
	FilesystemNodePointer Read() override{
		auto res = f_readdir(&dp, &fno);
		if(res != FR_OK || fno.fname[0] == 0) return nullptr;
		else{
			++cpos;
			return CreateNode(node, PathConcat(path, fno.fname));
		}
	}

	bool Write(IFilesystemNode &/*node*/) override{
		return false;
	}

	size_t Seek(size_t pos, uint32_t flags) override{
		bt_filesize_t size = 0;
		f_rewinddir(&dp);
		while(f_readdir(&dp, &fno) == FR_OK && fno.fname[0]) ++size;
		auto npos = FSHelpers::SeekPosition(pos, flags, cpos, size);
		f_rewinddir(&dp);
		for(bt_filesize_t i = 0; i < (bt_filesize_t)npos; ++i) f_readdir(&dp, &fno);
		cpos = npos;
		return cpos;
	}

	FilesystemNodePointer GetNode() override{
		return node;
	}

	void Close() override{
		f_closedir(&dp);
		if(del) f_rmdir(path.c_str());
	}

	bool Wait() override{
		return false;
	}
};

class FatFSFilesystemNode : public IFilesystemNode{
private:
	FatFSMountedFilesystem *mount;
	string path;
	FILINFO fno;
public:
	FatFSFilesystemNode(FatFSMountedFilesystem *m, const string &p, bool rootDir = false) : mount(m), path(p){
		if(rootDir){
			memset(&fno, 0, sizeof(fno));
			fno.fattrib = AM_DIR;
		}else{
			f_stat(path.c_str(), &fno);
		}
	}

	IFileHandle *OpenFile(uint32_t mode) override{
		if(!(fno.fattrib & AM_DIR)) return new FatFSFileHandle(path, mode, this);
		else return nullptr;
	}
	IDirectoryHandle *OpenDirectory(uint32_t mode) override{
		if(fno.fattrib & AM_DIR) return new FatFSDirectoryHandle(path, mode, this);
		else return nullptr;
	}

	IFileHandle *CreateFile(const char *name, uint32_t mode) override{
		dbgpf("FATFS: CreateFile(\"%s\" / \"%s\", %x, %x)\n", path.c_str(), name, mode, fno.fattrib);
		if(fno.fattrib & AM_DIR){
			auto fullPath = path + '/' + name;
			FILINFO info;
			auto r = f_stat(fullPath.c_str(), &info);
			if(r == FR_NO_FILE){
				FIL fp;
				r = f_open(&fp, fullPath.c_str(), FA_READ | FA_WRITE | FA_CREATE_NEW);
				if(r == FR_OK){
					unsigned int written = 0;
					auto cra = f_write(&fp, "AAA", 3, &written);
					f_lseek(&fp, 0);
					f_truncate(&fp);
					auto cr = f_close(&fp);
					auto node = GetNodeLocal(mount, fullPath.c_str());
					if(node){
						return node->OpenFile(mode);
					}else{
						dbgpf("FATFS: CreateFile could not retrieve node (\"%s\", %i, %i, %i)!\n", fullPath.c_str(), cr, written, cra);
					}
				}else{
					dbgpf("FATFS: CreateFile failed (\"%s\", %i)!\n", name, (int)r);
				}
			}
		}
		return nullptr;
	}

	IDirectoryHandle *CreateDirectory(const char *name, uint32_t mode) override{
		//dbgpf("FATFS: CreateDirectory(\"%s\", %x)\n", name, mode);
		if(fno.fattrib & AM_DIR){
			auto fullPath = path + '/' + name;
			auto r = f_mkdir(fullPath.c_str());
			if(r == FR_OK){
				auto node = GetNodeLocal(mount, fullPath.c_str());
				if(node){
					return node->OpenDirectory(mode);
				}
			}
		}
		return nullptr;
	}

	const char *GetName() override{
		return fno.fname;
	}
	void Rename(const char *newName) override{
		f_rename(path.c_str(), newName);
	}
	bt_filesize_t GetSize() override{
		return fno.fsize;
	}
	fs_item_types GetType() override{
		if(fno.fattrib & AM_DIR) return fs_item_types::FS_Directory;
		else return fs_item_types::FS_File;
	}

	FatFSMountedFilesystem *GetMount(){
		return mount;
	}
};

static FilesystemNodePointer CreateNode(FilesystemNodePointer node, const string &path){
	auto fatfsNode = static_cast<FatFSFilesystemNode*>(node.get());
	return new FatFSFilesystemNode(fatfsNode->GetMount(), path);
}

class FatFSMountedFilesystem : public IMountedFilesystem{
private:
	FATFS fs;

	uint8_t drvId;
	string drvNo;
	IFileHandle *handle;
	string deviceName;
public:
	FatFSMountedFilesystem(IFileHandle *h) : handle(h){
		drvId = NewDrive(handle);
		char buf[12] = {0};
		itoa(drvId, buf);
		drvNo = buf;
		auto res = f_mount(&fs, drvNo.c_str(), 2);
		if(res != FR_OK) dbgpf("FATFS: Mount failed (%i)\n", res);
		deviceName = h->GetNode()->GetName();
	}

	FilesystemNodePointer GetNode(const char *p) override{
		string path = drvNo + ":" + p;
		bool rootDir = false;
		string pStr = p;
		if(pStr == "" || pStr == "/") rootDir = true;
		FILINFO fno;
		auto res = rootDir ? FR_OK : f_stat(path.c_str(), &fno);
		//dbgpf("FATFS: GetNode(%s) -> %s : %i\n", p, path.c_str(), res);
		if(res == FR_OK && (rootDir || fno.fname[0] != 0)) return new FatFSFilesystemNode(this, path, rootDir);
		else return nullptr;
	}

	FilesystemNodePointer GetNodeLocal(const char *path){
		bool rootDir = false;
		string pStr = path;
		if(pStr == "" || pStr == "/") rootDir = true;
		FILINFO fno;
		auto res = rootDir ? FR_OK : f_stat(path, &fno);
		//dbgpf("FATFS: GetNodeLocal(%s) : %i\n", path, res);
		if(res == FR_OK && (rootDir || fno.fname[0] != 0)) return new FatFSFilesystemNode(this, path, rootDir);
		else return nullptr;
	}

	void Flush() override{}

	bool Unmount() override{
		f_unmount(drvNo.c_str());
		DeleteDrive(drvId);
		return true;
	}

	IFilesystem *FileSystem();
	const char *Device(){
		return deviceName.c_str();
	}
};

FilesystemNodePointer GetNodeLocal(FatFSMountedFilesystem *mount, const char *path){
	return mount->GetNodeLocal(path);
}

class FatFSFilesystem : public IFilesystem{
public:
	IMountedFilesystem *Mount(FilesystemNodePointer node) override{
		if(!node) return nullptr;
		auto handle = node->OpenFile(fs_mode_flags::FS_Read | fs_mode_flags::FS_Write);
		if(handle){
			return new FatFSMountedFilesystem(handle);
		}
		return nullptr;
	}
	bool Format(const IFilesystemNode &node, void *options) override{
		return false;
	}
};

IFilesystem *FatFSMountedFilesystem::FileSystem(){
	return theFilesystem;
}

int module_main(char *){
	theFilesystem = new FatFSFilesystem();
	API->GetFilesystemManager().RegisterFilesystem("FAT", theFilesystem);
	return 0;
}