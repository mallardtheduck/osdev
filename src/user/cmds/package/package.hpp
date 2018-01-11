#ifndef _PACKAGE_HPP
#define _PACKAGE_HPP

#include <string>
#include <map>

void ImportPackage(const std::string &infpath, const std::string &path);
void PackageFileInfo(const std::string &filePath);
void PackageFileList(const std::string &filePath);
void InstallPackage(const std::string &filePath, const std::string &path);
void UninstallPackage(const std::string &name, const std::string &path, bool keepFiles);

std::string get_or_blank(const std::map<std::string, std::string> &section, const std::string &key);
bool starts_with(const std::string &str, const std::string &start);

std::string ParsePath(const std::string &path);

#endif