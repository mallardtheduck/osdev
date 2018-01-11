#ifndef _INI_HPP
#define _INI_HPP

#include <map>
#include <string>
#include <iostream>

namespace btos_api{

typedef std::pair<std::string, std::string> IniLine;
typedef std::map<std::string, std::string> IniSection;
typedef std::map<std::string, IniSection> IniFile;

IniFile ReadIniFile(std::istream &file);
IniFile ReadIniFile(const std::string &filename);
IniSection ReadIniSection(std::istream &file);
IniLine ReadIniLine(const std::string &line);

}

#endif
