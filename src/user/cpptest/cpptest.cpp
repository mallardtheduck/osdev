#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <btos_stubs.h>
#include <terminal.h>

extern "C" bt_handle btos_get_handle(int fd);

std::vector<std::string> args2vector(int argc, char **argv){
	std::vector<std::string> ret;
	for(int i=0; i<argc; ++i){
		ret.push_back(argv[i]);
	}
	return ret;
}

int main(int argc, char **argv){
	std::cout << "Hello world!" << std::endl;
	std::vector<std::string> args=args2vector(argc, argv);
	for(auto i=args.begin(); i!=args.end(); ++i){
		std::cout << *i << std::endl;
	}
	std::ifstream file("info:/procs");
	while(!file.eof()){
		std::string line;
		getline(file, line);
		std::cout << line << std::endl;
	}
    std::cout << "std::cout works" << std::endl;
    std::cerr << "std::cerr works" << std::endl;
    std::string input;
    std::cout << "Enter some text: ";
    getline(std::cin, input);
    std::cout << "You entered: " << input << std::endl;
	return 0;
}