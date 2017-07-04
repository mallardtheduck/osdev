#include <btos/directory.hpp>

namespace btos_api{

	Directory::Directory(const char *path, uint32_t flags) : Handle(bt_dopen(path, flags)) {}

	bool Directory::Write(const bt_directory_entry &entry){
		return bt_dwrite(handle, entry);
	}

	bt_directory_entry Directory::Read() const{
		return bt_dread(handle);
	}

	size_t Directory::Seek(size_t bytes, uint32_t flags){
		return bt_dseek(handle, bytes, flags);
	}

	size_t Directory::Tell() const{
		return bt_dseek(handle, 0, FS_Relative);
	}

}
