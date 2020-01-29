#ifndef _RESC_ELF_HPP
#define _RESC_ELF_HPP

#include <iostream>

struct ElfRescInfo{
	std::streampos position;
	std::streamsize size;
	
	ElfRescInfo() = default;
	ElfRescInfo(std::streampos p, std::streamsize s) : position(p), size(s) {}
};

ElfRescInfo GetElfRescInfo(int fd);

#endif