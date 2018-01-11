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
	Info,
	Files,
	Install,
	Uninstall
};

int main(int argc, char **argv){
	Command cmd = Command::Help;
	string file;
	string path;
	bool keep = false;
	
	auto importCmd = (
		command("import").set(cmd, Command::Import) % "Import package.inf file into registry",
		value("info-file").set(file) % "Package info file to import",
		value("install-path").set(path) % "Path to package install location"
	);
	
	auto infoCmd = (
		command("info").set(cmd, Command::Info) % "Display information about a package file",
		value("package-file").set(file) % "Package file"
	);
	
	auto filesCmd = (
		command("files").set(cmd, Command::Files) % "Display list of files in a package",
		value("package-file").set(file) 
	);
	
	auto installCmd = (
		command("install").set(cmd, Command::Install) % "Install a package",
		value("package-file").set(file),
		value("install-path").set(path)
	);
	
	auto uninstallCmd = (
		command("uninstall", "remove").set(cmd, Command::Uninstall) % "Uninstall a package", (
			value("package-name").set(file) % "Package name" | (
				command("-p", "--path") & value("install-path").set(path)
			)
		),
		option("-k", "--keep-files").set(keep) % "Do not delete installed package files"
	);
	
	auto cli = (command("help").set(cmd, Command::Help) | installCmd | importCmd | infoCmd | filesCmd | uninstallCmd);
	
	if(parse(argc, argv, cli)){
		switch(cmd){
			case Command::Help:{
					auto fmt = doc_formatting{}.start_column(2).alternatives_min_split_size(3);
					std::cout << make_man_page(cli, argv[0], fmt);
				}
				break;
			case Command::Import:
				ImportPackage(file, path);
				break;
			case Command::Info:
				PackageFileInfo(file);
				break;
			case Command::Files:
				PackageFileList(file);
				break;
			case Command::Install:
				InstallPackage(file, path);
				break;
			case Command::Uninstall:
				UninstallPackage(file, path, keep);
				break;
		}
	}else{
		std::cerr << "Usage: " << std::endl;
		auto fmt = doc_formatting{}.start_column(2).alternatives_min_split_size(3);
		std::cerr << usage_lines(cli, argv[0], fmt) << std::endl;
	}
	
    return 0;
}