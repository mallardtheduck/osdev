#include <btos/directory.hpp>

namespace btos_api{

	void Directory::iterator::operator++(){
		ent = dir->Read();
	}

	bt_directory_entry Directory::iterator::operator*(){
		return ent;
	}

	bool Directory::iterator::operator==(const Directory::iterator &i){
		if(ent.valid) return ent.id == i.ent.id;
		else return !i.ent.valid;
	}

	bool Directory::iterator::operator!=(const Directory::iterator &i){
		return !(*this == i);
	}

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

	Directory::iterator Directory::begin(){
		Seek(0, FS_Set);
		iterator ret;
		ret.dir = this;
		++ret;
		return ret;
	}

	Directory::iterator Directory::end(){
		iterator ret;
		ret.dir = this;
		ret.ent.valid = false;
		return ret;
	}

}
