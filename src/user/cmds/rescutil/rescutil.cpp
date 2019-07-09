#include <btos/resc.h>
#include <util/clipp.hpp>
#include <util/tinyformat.hpp>

#include <string>
#include <iostream>
#include <array>

#include <unistd.h>
#include <fcntl.h>

using namespace clipp;
namespace r = btos_api::resc;

void list(const std::string &input){
	auto resc = r::Resc_FileOpen(input);
	if(resc){
		auto ls = r::Resc_ListBegin(resc);
		auto size = r::Resc_ListCount(ls);
		for(size_t i = 0; i < size; ++i){
			tfm::printf("%s\n", r::Resc_ListGetName(ls, i));
		}
		r::Resc_ListEnd(ls);
		r::Resc_Close(resc);
	}else{
		tfm::format(std::cerr, "Could not open resources from \"%s\"!\n", input);
	}
}

void extract(const std::string &input, const std::string &rescname, std::string output){
	if(output == "") output = rescname;
	auto resc = r::Resc_FileOpen(input);
	if(resc){
		auto in = r::Resc_OpenResc(resc, rescname);
		if(in){
			auto out = open(output.c_str(), O_WRONLY);
			if(out){
				std::array<char, 1024> buf;
				int count = 1;
				while(count){
					count = read(in, buf.begin(), 1024);
					write(out, buf.begin(), count);
				}
				tfm::printf("Extracted \"%s\" from \"%s\" successfully as \"%s\".\n", rescname, input, output);
				close(out);
			}else{
				tfm::format(std::cerr, "Could not open file \"%s\" for output!", output);
			}
			close(in);
		}else{
			tfm::format(std::cerr, "Could not open resource file \"%s\" from \"%s\"!", rescname, input);
		}
		r::Resc_Close(resc);
	}else{
		tfm::format(std::cerr, "Could not open resources from \"%s\"!\n", input);
	}
}

void extractTar(const std::string &input, std::string output){
	if(output == "") output = "resc.tar";
	auto resc = r::Resc_FileOpen(input);
	if(resc){
		auto in = r::Resc_OpenTar(resc);
		if(in){
			auto out = open(output.c_str(), O_WRONLY);
			if(out){
				std::array<char, 1024> buf;
				int count = 1;
				while(count){
					count = read(in, buf.begin(), 1024);
					write(out, buf.begin(), count);
				}
				tfm::printf("Extracted .tar archive from \"%s\" successfully as \"%s\".\n", input, output);
				close(out);
			}else{
				tfm::format(std::cerr, "Could not open file \"%s\" for output!", output);
			}
			close(in);
		}else{
			tfm::format(std::cerr, "Could not open .tar archive from \"%s\"!", input);
		}
		r::Resc_Close(resc);
	}else{
		tfm::format(std::cerr, "Could not open resources from \"%s\"!\n", input);
	}
}

int main(int argc, char **argv){
	enum class Mode{
		Help, List, Extract, ExtractTar
	};
	auto mode = Mode::Help;
	std::string rescname;
	std::string input;
	std::string output;
	
	auto helpCmd = (
		command("help", "--help").set(mode, Mode::Help) % "Display usage help"
	);
	auto listCmd = (
		command("list", "l").set(mode, Mode::List) % "List resource files"
	);
	auto extractCmd = (
		command("extract", "x").set(mode, Mode::Extract) % "Extract a resource file",
		value("resource-name").set(rescname) % "Name of resource file"
	);
	auto extractTarCmd = (
		command("extract-tar", "xtar").set(mode, Mode::ExtractTar) % "Extract resources as .tar archive"
	);
	
	auto cli = (
		helpCmd | (
			(listCmd | extractCmd | extractTarCmd), 
			value("input-file").set(input) % "Name of resource-containing executable or library",
			opt_value("output-file").set(output) % "Name of output file"
		)
	);
	
	if(parse(argc, argv, cli)){
		switch(mode){
			case Mode::Help:{
				auto fmt = doc_formatting{}.start_column(2).alternatives_min_split_size(1);
				std::cout << make_man_page(cli, argv[0], fmt);
				break;
			}	
			case Mode::List:
				list(input);
				break;
			case Mode::Extract:
				extract(input, rescname, output);
				break;
			case Mode::ExtractTar:
				extractTar(input, output);
		}
	}else{
		std::cerr << usage_lines(cli, argv[0]) << std::endl;
	}
}