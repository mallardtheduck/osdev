#include <btos/ini.hpp>
#include <btos/registry.hpp>

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "package.hpp"
#include "packagefile.hpp"

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::endl;

namespace reg = btos_api::registry;

bool starts_with(const string &str, const string &start){
    if(str.length() < start.length()) return false;
    return str.substr(0, start.length()) == start;
}

string get_or_blank(const map<string, string> &section, const string &key){
    if(section.find(key) != section.end()) return section.at(key);
    else return "";
}

void ImportPackage(const string &infpath, const string &path){
    auto file = btos_api::ReadIniFile(infpath);
    if(file.find("package") != file.end()){
        auto pkgsection = file["package"];
        reg::PackageInfo pkginfo;
        pkginfo.name = get_or_blank(pkgsection, "name");
        pkginfo.description = get_or_blank(pkgsection, "description");
        pkginfo.ver = get_or_blank(pkgsection, "version");
        pkginfo.path = path;
        if(pkginfo.name == "") return;

        int64_t pkgid;
        auto cpkg = reg::GetPackageByName(pkginfo.name);
        if(cpkg.id > 0) pkgid = cpkg.id;
        else pkgid = reg::InstallPackage(pkginfo);

        for(auto &s : file){
            if(starts_with(s.first, "feature")){
                reg::FeatureInfo featinfo;
                featinfo.package = pkgid;
                featinfo.name = get_or_blank(s.second, "name");
                featinfo.description = get_or_blank(s.second, "description");
                featinfo.path = get_or_blank(s.second, "path");
                featinfo.file = get_or_blank(s.second, "file");
                featinfo.type = get_or_blank(s.second, "type");
                featinfo.ver = get_or_blank(s.second, "version");
                featinfo.flags = 0;

                if(featinfo.name == "") continue;
                if(featinfo.ver == "") featinfo.ver = pkginfo.ver;

                if(reg::GetFeatureByName(featinfo.name).id < 0){
                    reg::InstallFeature(featinfo);
                }
            }
        }
    }
}

void PackageFileInfo(const string &filePath){
	PackageFile pkgFile(filePath);
	auto pkgInfo = pkgFile.GetInfo();
	cout << "Package name: " << pkgInfo.name << endl;
	cout << "Description: " << pkgInfo.description << endl;
	cout << "Version: " << pkgInfo.ver << endl;
	cout << endl << "Features:" << endl;
	
	auto feats = pkgFile.GetFeatures();
	for(auto &f : feats){
		cout << endl << "Feature name: " << f.name << endl;
		cout << "Description: " << f.description << endl;
		cout << "Type: " << f.type << endl;
		cout << "Version: " << f.ver << endl;
	}
}

static string padRight(const string &str, size_t len, char pad = ' '){
	if(str.length() < len){
		return str + string(len - str.length(), pad);
	}else return str;
}

void PackageFileList(const string &filePath){
	PackageFile pkgFile(filePath);
	auto fileList = pkgFile.GetContent();
	size_t maxNameLen = 0;
	size_t maxSizeLen = 0;
	for(auto &f : fileList){
		if(f.path.length() > maxNameLen) maxNameLen = f.path.length();
		auto sizeLen = ceil(log10(f.size + 1));
		if(sizeLen > maxSizeLen) maxSizeLen = sizeLen;
	}
	for(auto &f : fileList){
		cout << padRight(f.path, maxNameLen) << " " << std::setw(maxSizeLen) << std::dec << f.size << " bytes @0x" << std::hex << f.offset << endl;
	}
}
