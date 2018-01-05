#include <vector>
#include <string>
#include <iostream>
#include <util/clipp.hpp>

#include "package.hpp"

using std::vector;
using std::string;

using namespace clipp;

enum class Command{
	Help,
	Import
};

int main(int argc, char **argv){
	Command cmd = Command::Help;
	string file;
	string path;
	
	auto importCmd = (
		command("import").set(cmd, Command::Import),
		value("info-file").set(file) % "Package info file to import",
		value("install-path").set(path) % "Path to package install location"
	);
	
	auto cli = (importCmd | command("help").set(cmd, Command::Help));
	
	if(parse(argc, argv, cli)){
		switch(cmd){
			case Command::Help:
				std::cout << make_man_page(cli, argv[0]);
				break;
			case Command::Import:
				ImportPackage(file, path);
				break;
		}
	}else{
		std::cout << usage_lines(cli, argv[0]) << std::endl;
	}
	
    return 0;
}