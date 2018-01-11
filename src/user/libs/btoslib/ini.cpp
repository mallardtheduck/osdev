#include <btos/ini.hpp>
#include <btos/table.hpp>
#include <fstream>

namespace btos_api{

//
// ReadIniLine ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Parses a .INI file line
IniLine ReadIniLine(const std::string &line){
	//Parameters:
	// line - a string representation of the line to parse
	//Returns: the parsed line as an IniLine (std::pair)
	//-------------------------------------------------------------------------

	IniLine ret;
	bool key=true;
	std::string curRead;

	//For each character in the string
	for(auto i=line.begin(); i!=line.end(); ++i){
		//If we are reading the key and we encounter an '=', then
		//the key is finished and we start reading the value.
		if(key && (*i == '=' || *i == ':')){
			key=false;
			//Trim the key
			trim(curRead);
			ret.first=curRead;
			curRead="";
			continue;
		//If we encouter the start of a comment, or the end of a line,
		//we've finished.
		}else if(!key && (*i==';' || *i=='\n')){
			break;
		}
		curRead+=*i;
	}
	//Trim the value
	trim(curRead);
	//If the value is quoted, remove the quotes.
	if(curRead[0]=='"' && curRead[curRead.size()-1]=='"'){
		curRead.erase(curRead.begin());
		curRead.erase(curRead.rbegin().base()-1);
	}
	ret.second=curRead;
	return ret;
}

//
// ReadIniSection +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Reads and parses a .INI file section
IniSection ReadIniSection(std::istream &file){
	//Parameters:
	// file - the file to read a section from
	//Returns: the parsed section as an IniSection (std::map)
	//-------------------------------------------------------------------------

	IniSection ret;
	char c;

	while(!file.eof()){
		//Peek at next character
		c=file.peek();
		//If it isn't whitespace, the start of a section header or comment,
		//then we are interested in it.
		if(!isspace(c) && c!='[' && c!=';'){
			//Read and parse the line
			std::string line;
			std::getline(file, line);
			ret.insert(ReadIniLine(line));
		}else if(c==';'){
			//It's a comment. Ignore it.
			std::string bitbucket;
			std::getline(file, bitbucket);
		}else if(c=='['){
			//It's the start of the next section, we've finished this one.
			break;
		}else{
			//It's whitespace, read and discard it.
			file.read(&c, 1);
		}
	}
	return ret;
}

//
// ReadIniFile ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Reads and parses a .INI file
IniFile ReadIniFile(std::istream &file){
	//Parameters:
	// file - the file to read/parse
	//Returns: The parsed .INI file as an IniFile (std::map)
	//-------------------------------------------------------------------------

	IniFile ret;
	char c;

	while(!file.eof()){
		//Read one character
		file.read(&c, 1);
		//Is it the start of a section header?
		if(c=='['){
			std::string curSection;
			//Read in the rest of the section header
			while(!file.eof()){
				file.read(&c, 1);
				if(c!=']' && c!='\n'){
					curSection+=c;
				}else{
					break;
				}
			}
			//Read and parse the section
			ret[curSection]=ReadIniSection(file);
		}
	}
	return ret;
}

IniFile ReadIniFile(const std::string &filename){
	std::ifstream file(filename.c_str());
	return ReadIniFile(file);
}

}

