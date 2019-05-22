#include <util/tinyformat.hpp>
#include "resctest_resc.tar.h"

#include <btos/resc.h>

#include <sstream>
#include <vector>
#include <string>
#include <iostream>

#include <unistd.h>
#include <fcntl.h>
#include <ext/stdio_filebuf.h>

namespace resc = btos_api::resc;

void listRescs(resc::RescHandle resc){
	auto lst = resc::Resc_ListBegin(resc);
	auto count = resc::Resc_ListCount(lst);
	tfm::printf("List: %p Count: %s\n", lst, count);
	tfm::printf("Outputting list of resources:\n");
	for(size_t i = 0; i < count; ++i){
		tfm::printf("  %s\n", resc::Resc_ListGetName(lst, i));
	}
	tfm::printf("Closing resource list.\n");
	resc::Resc_ListEnd(lst);
}

void outputAsFile(resc::RescHandle resc, const char *filename){
	int fd = resc::Resc_OpenResc(resc, filename);
	if(!fd){
		tfm::printf("Open of \"%s\" failed!\n", filename);
		return;
	}
	tfm::printf("stdio-compatible fd: %s\n", fd);
	tfm::printf("Converting to C++ stream and outputting contents:\n");
	__gnu_cxx::stdio_filebuf<char> filebuf(fd, std::ios::in);
	std::istream is(&filebuf);
	for (std::string line; std::getline(is, line);){
		tfm::printf("  %s\n", line);
	}
	close(fd);
}

int main(int argc, char **argv){
	std::vector<std::string> args(argv, argv + argc);
	
	tfm::printf("Opening local resources at: %p size: %s\n", resctest_resc_data, resctest_resc_size);
	auto resc = resc::Resc_LocalOpen(resctest_resc_data, resctest_resc_size);
	tfm::printf("RescHandle: %p\n", resc);
	
	tfm::printf("Getting list of local resources.\n");
	listRescs(resc);
	
	tfm::printf("Opening 'test.txt' using file access\n");
	outputAsFile(resc, "test.txt");
	
	tfm::printf("Getting local address and size of 'test.txt'\n");
	size_t sz;
	auto addr = resc::Resc_GetLocal(resc, "test.txt", &sz);
	tfm::printf("Address: %p Size: %s\n", addr, sz);
	tfm::printf("Outputting contents via std::string:\n");
	std::string c(addr, addr + sz);
	tfm::printf("  %s", c);
	
	std::string filename = args[0];
	if(args.size() > 1) filename = args[1];
	
	tfm::printf("Opening resources from \"%s\".\n", filename);
	auto rs2 = resc::Resc_FileOpen(filename);
	tfm::printf("RescHandle: %p\n", rs2);
	tfm::printf("Does 'test.txt' exist in this file?\n");
	bool test = resc::Resc_RescExists(rs2, "test.txt");
	if(test){
		tfm::printf("Yes, opening 'test.txt' using file access\n");
		outputAsFile(rs2, "test.txt");
	}else{
		tfm::printf("No.\n");
	}
	tfm::printf("Getting list of resources from \"%s\".\n", filename);
	listRescs(rs2);
	tfm::printf("Closing resources from \"%s\".\n", filename);
	resc::Resc_Close(rs2);
	
	return 0;
}