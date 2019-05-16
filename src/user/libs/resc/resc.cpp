#include <btos/resc.h>
#include "tar.hpp"

#include <memory>
#include <iostream>
#include <fstream>

#include <libelf.h>
#include <gelf.h>
#include <unistd.h>
#include <fcntl.h>

struct membuf : std::streambuf{
	char *begin, *end;
	
	membuf(const char *b, const char *e) : begin((char*)b), end((char*)e){
		this->setg(begin, begin, end);
	}

	virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode) override{
		if(dir == std::ios_base::cur) gbump(off);
		else if(dir == std::ios_base::end)	setg(begin, end + off, end);
		else if(dir == std::ios_base::beg)	setg(begin, begin + off, end);
		
		return gptr() - eback();
	}

	virtual pos_type seekpos(std::streampos pos, std::ios_base::openmode mode) override{
		return seekoff(pos - pos_type(off_type(0)), std::ios_base::beg, mode);
	}
};

struct offsetbuf : std::filebuf{
	std::unique_ptr<std::ifstream> file;
	pos_type offset;
	off_type size;

	virtual pos_type seekoff(off_type off, std::ios_base::seekdir dir, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override{
		pos_type ret;
		if(dir == std::ios_base::beg){
			std::filebuf::seekoff(offset, std::ios_base::beg, mode);
			ret = std::filebuf::seekoff(off, std::ios_base::cur, mode) - offset;
		}else if(dir == std::ios_base::end){
			std::filebuf::seekoff(off, std::ios_base::beg, mode);
			ret = std::filebuf::seekoff(size - off, std::ios_base::cur, mode) - offset;
		}else if(dir == std::ios_base::cur){
			ret = std::filebuf::seekoff(off, std::ios_base::cur, mode) - offset;
		}
		return ret;
	}

	virtual pos_type seekpos(std::streampos pos, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out) override{
		return seekoff(pos - pos_type(off_type(0)), std::ios_base::beg, mode);
	}
	
	offsetbuf(std::unique_ptr<std::ifstream> &f, pos_type o, off_type s) : file(std::move(f)), offset(o), size(s){
		seekoff(pos_type(off_type(0)), std::ios_base::beg);
	}
};

namespace btos{
namespace resc{
	
struct RescHandle_Impl{
	std::unique_ptr<std::streambuf> buf;
	std::unique_ptr<std::istream> stream;
	tar::reader reader;
	
	template <typename strT = std::istream>
	RescHandle_Impl(std::streambuf *b) : buf(b), stream(new strT(buf.get())), reader(*stream) {}
};
	
extern "C" RescHandle Resc_LocalOpen(const char *data, size_t size){
	RescHandle_Impl *rh = new RescHandle_Impl(new membuf(data, data + size));
	return (RescHandle)rh;
}

struct ElfRescInfo{
	std::streampos position;
	std::streamsize size;
};

std::string elf_get_section_name(Elf64_Word offset, Elf *e){
	size_t shidx;
	elf_getshstrndx(e, &shidx);
	return elf_strptr(e, shidx, offset);
}

ElfRescInfo GetElfRescInfo(const std::string &filename){
	ElfRescInfo info;
	int fd = open(filename.c_str(), O_RDONLY, 0);
	Elf *e = elf_begin(fd, ELF_C_READ, NULL);
	Elf_Scn *scn = NULL;
	GElf_Shdr shdr;
	while ((scn = elf_nextscn(e, scn))) {
		gelf_getshdr(scn, &shdr);
		if (shdr.sh_type == SHT_PROGBITS && elf_get_section_name(shdr.sh_name, e) == "resc") {
			info.position = shdr.sh_offset;
			info.size = shdr.sh_size;
			break;
		}
	}
	elf_end(e);
	close(fd);
	return info;
}

extern "C" RescHandle Resc_FileOpen(const char *filename){
	ElfRescInfo info = GetElfRescInfo(filename);
	if(info.position){
		std::unique_ptr<std::ifstream> stream(new std::ifstream(filename));
		RescHandle_Impl *rh = new RescHandle_Impl(new offsetbuf(stream, info.position, info.size));
		return (RescHandle)rh;
	}else{
		return nullptr;
	}
}

/*
extern "C" RescHandle Resc_FDOpen(int fd){
	
}

extern "C" int Resc_OpenResc(RescHandle h, const char *filename){
	
}

extern "C" bool Resc_RescExists(RescHandle h, const char *filename){
	
}

extern "C" int Resc_OpenTar(RescHandle h){
	
}

std::istream &Resc_OpenRescStream(RescHandle h, const std::string &filename){
	
}

std::istream &Resc_OpenTarStream(RescHandle h){

}
*/
}
}