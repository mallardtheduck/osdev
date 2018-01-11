#ifndef _INI_HPP
#define _INI_HPP

#include <map>
#include <string>
#include <iostream>

typedef std::pair<std::string, std::string> IniLine;
typedef std::map<std::string, std::string> IniSection;
typedef std::map<std::string, IniSection> IniFile;

IniFile ReadIniFile(const std::string &filename);
IniSection ReadIniSection(std::istream &file);
IniLine ReadIniLine(const std::string &line);

void trim(std::string &str);

#endif
