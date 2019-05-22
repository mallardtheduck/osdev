#include <fstream>
#include <vector>
#include <string>
#include <util/tinyformat.hpp>

#include <ext/stdio_filebuf.h>
#include <istream>

#include <unistd.h>
#include <fcntl.h>

#include "tar.hpp"

int main(int argc, char **argv){
	std::vector<std::string> args(argv, argv + argc);
	if(args.size() > 1){
		auto filename = args[1];
		
		int fd = open(filename.c_str(), O_RDONLY);
		__gnu_cxx::stdio_filebuf<char> buf(fd, std::ios::in);
		std::istream file(&buf);
		
		//std::ifstream file(filename.c_str());
		
		tar::reader rdr(file);
		while(rdr.contains_another_file()){
			tfm::printf("%s\n", rdr.get_next_file_name());
			rdr.skip_next_file();
		}
	}
	return 0;
}