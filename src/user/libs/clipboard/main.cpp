#define BTOS_NO_USING
#include <btos/clipboard.hpp>
#include <util/clipp.hpp>

#include <string>
#include <iostream>
#include <fstream>

using namespace clipp;
namespace c = btos_api::clipboard;

template<class Elem, class Traits>
static void hex_dump(const void* aData, std::size_t aLength, std::basic_ostream<Elem, Traits>& aStream, std::size_t aWidth = 16){
	const char* const start = static_cast<const char*>(aData);
	const char* const end = start + aLength;
	const char* line = start;
	while (line != end)	{
		aStream << "0x";
		aStream.width(4);
		aStream.fill('0');
		aStream << std::hex << std::uppercase << line - start << " : ";
		std::size_t lineLength = std::min(aWidth, static_cast<std::size_t>(end - line));
		for (std::size_t pass = 1; pass <= 2; ++pass)		{	
			for (const char* next = line; next != end && next != line + aWidth; ++next){
				char ch = *next;
				switch(pass){
				case 1:
					aStream << (ch < 32 ? '.' : ch);
					break;
				case 2:
				    if(next != line && next != (line + lineLength)) aStream << " ";
					aStream.width(2);
					aStream.fill('0');
					aStream << std::hex << std::uppercase << static_cast<int>(static_cast<unsigned char>(ch));
					break;
				}
			}
			if (pass == 1 && lineLength != aWidth) aStream << std::string(aWidth - lineLength, ' ');
			aStream << " ";
		}
		aStream << std::endl;
		line = line + lineLength;
	}
}

static void Copy(const std::string &file, const std::string &type){
    std::unique_ptr<std::ifstream> filestream;
    if(!file.empty()){
        filestream.reset(new std::ifstream(file));
        if(!filestream->good()) return;
    }
    
    std::istream &is = filestream ? *filestream : std::cin;
    std::istreambuf_iterator<char> begin(is), end;
    std::vector<char> data(begin, end);
    
    c::CopyCut(c::Clipboard::Primary, type, data);
}

static void Paste(bool any){
    auto hdr = c::GetContentHeader(c::Clipboard::Primary);
    if(any || (hdr.type.length() > 5 && hdr.type.substr(0, 5) == "text/")){
        auto data = c::Paste(c::Clipboard::Primary, hdr.id);
        if(!data.empty()){
            for(char c : data) std::cout << c;   
        }
        std::cout << std::endl;
    }
}

static void Dump(){
    auto hdr = c::GetContentHeader(c::Clipboard::Primary);
    auto data = c::Paste(c::Clipboard::Primary, hdr.id);
    std::cout << "Type: " << (hdr.type.empty() ? "-empty-" : hdr.type) << " Size: " << data.size() << std::endl;
    hex_dump(data.data(), data.size(), std::cout);
}

enum class Command{
	Copy, Paste, Dump, Help
};

int main(int argc, char **argv){
	Command cmd = Command::Help;
	std::string file;
	std::string type;
	bool any = false;
	
	auto copyCmd = (
	   command("copy", "c").set(cmd, Command::Copy) % "Copy data to clipboard" &
	   value("type").set(type) % "Data MIME type",
	   option("-f", "--file") & value("file").set(file) % "Copy from file instead of STDIN"
	);
	
	auto pasteCmd = (
	    command("paste", "p").set(cmd, Command::Paste) % "Paste (display) text-based clipboard content",
	    option("-a", "--any").set(any, true) % "Output any clipboard data as text, not just \"text/*\" MIME types"
	);
	
	auto dumpCmd = (
	    command("dump", "d").set(cmd, Command::Dump) % "Dump (as hex) any clipboard content"
	);
	
	auto helpCmd = (
		command("help", "--help").set(cmd, Command::Help) % "Display usage help"
	);
	
	auto cli = (copyCmd | pasteCmd | dumpCmd | helpCmd);
	
	auto parse_result = parse(argc, argv, cli);
	//debug::print(std::cout, parse_result);
	if(parse_result){
		switch(cmd){
			case Command::Copy:{
			    Copy(file, type);
			    break;
			}
			case Command::Paste:{
			    Paste(any);
			    break;
			}
			case Command::Dump:{
			    Dump();
			    break;
			}
			case Command::Help:{
			   	auto fmt = doc_formatting{}.first_column(2).alternatives_min_split_size(1);
				std::cout << make_man_page(cli, argv[0], fmt);
				break;
			}
		}
	}else{
		std::cerr << usage_lines(cli, argv[0]) << std::endl;
	}
}