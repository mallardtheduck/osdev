#include <btos/file.hpp>

namespace btos_api{

	File::File(bt_handle_t h) : Handle(h, false) {}

	File::File(const char *path, uint32_t flags) : Handle(bt_fopen(path, flags)) {}
	
	size_t File::Write(size_t bytes, const char *buffer){
		return bt_fwrite(handle, bytes, buffer);
	}

	size_t File::Read(size_t bytes, char *buffer){
		return bt_fread(handle, bytes, buffer);
	}

	size_t File::IOCtl(int function, size_t bytes, char *buffer){
		return bt_fioctl(handle, function, bytes, buffer);
	}
	
	bt_filesize_t File::Seek(bt_filesize_t bytes, uint32_t flags){
		return bt_fseek(handle, bytes, flags);
	}

	bt_filesize_t File::Tell(){
		return bt_fseek(handle, 0, FS_Relative);
	}

	void File::Flush(){
		bt_fflush(handle);
	}

	FileMapping File::MemMap(size_t offset, char *addr, size_t size){
		return FileMapping(handle, offset, addr, size);
	}


	FileMapping::FileMapping(bt_handle_t h, size_t o, char *a, size_t s) : 
		Handle(bt_mmap(h, o, a, s)), filehandle(h), offset(o), addr(a), size(s) {}
	
	File FileMapping::GetFile(){
		return File(filehandle);
	}

	size_t FileMapping::Offset(){
		return offset;
	}

	char *FileMapping::Address(){
		return addr;
	}

	size_t FileMapping::Size(){
		return size;
	}
}
