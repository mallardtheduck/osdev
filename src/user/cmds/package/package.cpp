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
	Import,
	Info
};

int main(int argc, char **argv){
	Command cmd = Command::Help;
	string file;
	string path;
	
	auto importCmd = (
		command("import").set(cmd, Command::Import) % "Import package.inf file into registry",
		value("info-file").set(file) % "Package info file to import",
		value("install-path").set(path) % "Path to package install location"
	);
	
	auto infoCmd = (
		command("info").set(cmd, Command::Info) % "Display information about a package file",
		value("package-file").set(file) % "Package file"
	);
	
	auto cli = (command("help").set(cmd, Command::Help) | importCmd | infoCmd);
	
	if(parse(argc, argv, cli)){
		switch(cmd){
			case Command::Help:{
					auto fmt = doc_formatting{}.start_column(2).alternatives_min_split_size(1);
					std::cout << make_man_page(cli, argv[0], fmt);
				}
				break;
			case Command::Import:
				ImportPackage(file, path);
				break;
			case Command::Info:
				PackageFileInfo(file);
				break;
		}
	}else{
		std::cerr << usage_lines(cli, argv[0]) << std::endl;
	}
	
    return 0;
}