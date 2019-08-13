#include <btos/resc.h>
#include "tar.hpp"
#include "virt_handles.hpp"
#include "elf.hpp"

#include <memory>
#include <vector>
#include <iostream>
#include <fstream>
#include <ext/stdio_filebuf.h>

#include <unistd.h>
#include <fcntl.h>

//#include <util/tinyformat.hpp>

namespace btos_api{
namespace resc{
	
struct RescHandle_Impl{
	virtual_handle vh;
	int fd;
	__gnu_cxx::stdio_filebuf<char> buf;
	std::istream stream;
	const char *local_addr;
	
	tar::reader Reader(){
		stream.seekg(0);
		return tar::reader(stream);
	}
	
	std::vector<std::unique_ptr<virtual_handle>> handles;
	
	virtual_handle *AddHandle(const virtual_handle &h){
		auto ptr = std::unique_ptr<virtual_handle>(new virtual_handle(h));
		auto addr = ptr.get();
		handles.emplace_back(std::move(ptr));
		return addr;
	}

	RescHandle_Impl(const virtual_handle &h, const char *l = nullptr) : 
	vh(h), fd(btos_set_filenum_virt(&vh)), buf(fd, std::ios::in), stream(&buf), local_addr(l) {}
};
	
extern "C" RescHandle Resc_LocalOpen(const char *data, size_t size){
	virtual_handle h = MemoryVirtualHandle(data, size);
	return (RescHandle*)new RescHandle_Impl(h, data);
}

extern "C" RescHandle Resc_FileOpen(const char *filename){
	int fd = open(filename, O_RDONLY, 0);
	ElfRescInfo info = GetElfRescInfo(fd);
	if(info.position){
		virtual_handle h = FileOffsetVirtualHandle(fd, info.position, info.size, true);
		return (RescHandle*)new RescHandle_Impl(h);
	}else{
		close(fd);
		return nullptr;
	}
}


extern "C" RescHandle Resc_FDOpen(int fd){
	ElfRescInfo info = GetElfRescInfo(fd);
	if(info.position){
		virtual_handle h = FileOffsetVirtualHandle(fd, info.position, info.size);
		return (RescHandle*)new RescHandle_Impl(h);
	}else{
		return nullptr;
	}
}

extern "C" void Resc_Close(RescHandle h){
	RescHandle_Impl *impl = (RescHandle_Impl*)h;
	close(impl->fd);
	delete (RescHandle_Impl*)h;
}

static bool starts_with(const std::string &str, const std::string &start){
    if(str.length() < start.length()) return false;
    return str.substr(0, start.length()) == start;
}

static std::string filter_filename(const std::string &name){
	if(starts_with(name, "./")){
		return name.substr(2);
	}else return name;
}

extern "C" int Resc_OpenResc(RescHandle h, const char *filename){
	RescHandle_Impl *impl = (RescHandle_Impl*)h;
	auto rdr = impl->Reader();
	while(rdr.contains_another_file()){
		if(filter_filename(rdr.get_next_file_name()) == filename){
			auto offset = rdr.get_next_file_offset();
			auto size = rdr.get_next_file_size();
			virtual_handle h = FileOffsetVirtualHandle(impl->fd, offset, size);
			return btos_set_filenum_virt(impl->AddHandle(h));
		}
		rdr.skip_next_file();
	}
	return 0;
}

extern "C" bool Resc_RescExists(RescHandle h, const char *filename){
	RescHandle_Impl *impl = (RescHandle_Impl*)h;
	auto rdr = impl->Reader();
	while(rdr.contains_another_file()){
		if(filter_filename(rdr.get_next_file_name()) == filename){
			return true;
		}
		rdr.skip_next_file();
	}
	return false;
}

const char *Resc_GetLocal(RescHandle h, const char *filename, size_t *size){
	RescHandle_Impl *impl = (RescHandle_Impl*)h;
	if(!impl->local_addr) return nullptr;
	auto rdr = impl->Reader();
	while(rdr.contains_another_file()){
		if(filter_filename(rdr.get_next_file_name()) == filename){
			if(size) *size = rdr.get_next_file_size();
			return impl->local_addr + rdr.get_next_file_offset();
		}
		rdr.skip_next_file();
	}
	return nullptr;
}

extern "C" int Resc_OpenTar(RescHandle h){
	RescHandle_Impl *impl = (RescHandle_Impl*)h;
	return impl->fd;
}

typedef std::vector<std::string> RescList_Impl;

extern "C" RescList Resc_ListBegin(RescHandle h){
	RescHandle_Impl *impl = (RescHandle_Impl*)h;
	RescList_Impl *lst = new RescList_Impl();
	auto rdr = impl->Reader();
	while(rdr.contains_another_file()){
		auto name = filter_filename(rdr.get_next_file_name());
		//tfm::printf("** %s : %s\n", name, rdr.get_next_file_size());
		if(name != "" && !rdr.is_next_directory()) lst->push_back(name);
		rdr.skip_next_file();
	}
	return (RescList)lst;
}

extern "C" size_t Resc_ListCount(RescList l){
	RescList_Impl *lst = (RescList_Impl*)l;
	return lst->size();
}

extern "C" const char *Resc_ListGetName(RescList l, size_t idx){
	RescList_Impl *lst = (RescList_Impl*)l;
	if(idx < lst->size()) return lst->at(idx).c_str();
	else return nullptr;
}

extern "C" void Resc_ListEnd(RescList l){
	delete (RescList_Impl*)l;
}

}
}