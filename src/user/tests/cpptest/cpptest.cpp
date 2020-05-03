#include <btos.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <dev/terminal.h>
#include <btos/directory.hpp>

using namespace btos_api;

extern "C" bt_handle btos_get_handle(int fd);

class global_test{
	public:
	global_test(){
		std::cout << "Global constructor." << std::endl;
	}
	~global_test(){
		std::cout << "Global destructor." << std::endl;
	}
} global_test_inst;

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
    std::cout << "Testing exception handling..." << std::endl;
	try{
		throw 42;
	}catch(int ex){
		std::cout << "Exception test: " << ex << std::endl;
	}
    std::cout << "Enter some text: ";
    getline(std::cin, input);
    std::cout << "You entered: " << input << std::endl;

	Directory dir("info:/", FS_Read);
	for(auto d : dir){
		std::cout << "File: " << d.filename << std::endl;
	}
	return 0;
}
