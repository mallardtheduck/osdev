#include <module/module.inc>
#include <module/utils/string.hpp>
#include <module/utils/fshelpers.hpp>

#include "drive.hpp"

#include "ff.h"

static FilesystemNodePointer CreateNode(const string &path);

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
public:
	FatFSFileHandle(const string &p, uint32_t mode, IFilesystemNode *n) : path(p), node(n){
		uint8_t fmode = 0;
		if(mode & fs_mode_flags::FS_Read) fmode |= FA_READ;
		if(mode & fs_mode_flags::FS_Write) fmode |= FA_WRITE;

		if(mode & fs_mode_flags::FS_Create) fmode |= FA_CREATE_NEW;
		if(mode & fs_mode_flags::FS_Truncate) fmode |= FA_CREATE_ALWAYS;

		if(mode & fs_mode_flags::FS_AtEnd) fmode |= FA_OPEN_APPEND;
		f_open(&fp, path.c_str(), fmode);
		if(mode & fs_mode_flags::FS_Delete) del = true;
	}
	size_t Read(size_t bytes, char *buffer) override{
		unsigned int read = 0;
		f_read(&fp, buffer, bytes, &read);
		return read;
	}
	size_t Write(size_t bytes, const char *buffer) override{
		unsigned int written = 0;
		f_write(&fp, buffer, bytes, &written);
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
public:
	FatFSDirectoryHandle(const string &p, uint32_t mode, IFilesystemNode *n) : path(p), node(n){
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
			return CreateNode(PathConcat(path, fno.fname));
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
	}

	bool Wait() override{
		return false;
	}
};

class FatFSFilesystemNode : public IFilesystemNode{
private:
	string path;
	FILINFO fno;
public:
	FatFSFilesystemNode(const string &p) : path(p){
		f_stat(path.c_str(), &fno);
	}

	IFileHandle *OpenFile(uint32_t mode) override{
		if(!(fno.fattrib & AM_DIR)) return new FatFSFileHandle(path, mode, this);
		else return nullptr;
	}
	IDirectoryHandle *OpenDirectory(uint32_t mode) override{
		if(fno.fattrib & AM_DIR) return new FatFSDirectoryHandle(path, mode, this);
		else return nullptr;
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
};

static FilesystemNodePointer CreateNode(const string &path){
	return new FatFSFilesystemNode(path);
}

class FatFSMountedFilesystem : public IMountedFilesystem{
private:
	FATFS fs;

	uint8_t drvId;
	string drvNo;
	IFileHandle *handle;
public:
	FatFSMountedFilesystem(IFileHandle *h) : handle(h){
		drvId = NewDrive(handle);
		char buf[12] = {0};
		drvNo = buf;
		itoa(drvId, buf);
		f_mount(&fs, drvNo.c_str(), 2);
	}

	FilesystemNodePointer GetNode(const char *p) override{
		string path = drvNo + ":/" + p;
		FILINFO fno;
		auto res = f_stat(path.c_str(), &fno);
		if(res == FR_OK && fno.fname[0] != 0)return new FatFSFilesystemNode(path);
		else return nullptr;
	}

	void Flush() override{}

	bool Unmount() override{
		f_unmount(drvNo.c_str());
		DeleteDrive(drvId);
		return true;
	}
};

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

int module_main(char *){
	API->GetFilesystemManager().RegisterFilesystem("FAT", new FatFSFilesystem());
	return 0;
}