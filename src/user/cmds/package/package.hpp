#ifndef _PACKAGE_HPP
#define _PACKAGE_HPP

#include <string>
#include <map>

void ImportPackage(const std::string &infpath, const std::string &path);

std::string get_or_blank(const std::map<std::string, std::string> &section, const std::string &key);
bool starts_with(const std::string &str, const std::string &start);

#endif