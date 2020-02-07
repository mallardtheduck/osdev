#include <btos/ini.hpp>
#include <btos/registry.hpp>
#include <btos/directory.hpp>

#include <crt_support.h>

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <memory>
#include <cstdio>
#include <sstream>

#include "package.hpp"
#include "packagefile.hpp"

using std::vector;
using std::string;
using std::map;
using std::cout;
using std::endl;

using namespace btos_api;
namespace reg = btos_api::registry;

bool starts_with(const string &str, const string &start){
    if(str.length() < start.length()) return false;
    return str.substr(0, start.length()) == start;
}

string get_or_blank(const map<string, string> &section, const string &key){
    if(section.find(key) != section.end()) return section.at(key);
    else return "";
}

string ParsePath(const string &path){
	std::unique_ptr<char[]> buffer {new char[BT_MAX_PATH]};
	if(btos_path_parse(path.c_str(), buffer.get(), BT_MAX_PATH)){
		return {buffer.get()};
	}
	return {};
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
		cout << "  Feature name: " << f.name << endl;
		cout << "  Description: " << f.description << endl;
		cout << "  Type: " << f.type << endl;
		cout << "  Version: " << f.ver << endl << endl;
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
		cout << padRight(f.path, maxNameLen) << " ";
		if(f.type == FS_Directory){
			cout << padRight("<DIR>", maxSizeLen + 6);
		}else{
			cout << std::setw(maxSizeLen) << std::dec << f.size << " bytes";
		}
		cout << " @0x" << std::hex << f.offset << endl;
	}
}

void InstallPackage(const string &filePath, const string &path){
	size_t proglen = 0;
	auto progressFn = [&](const PackageFile::InstallProgress &p){
		size_t pos = cout.tellp();
		if(proglen){
			cout << string(proglen, ' ') << std::flush;
			cout.seekp(pos);
		}
		std::stringstream ss;
		ss << "Installing file " << p.step << " of " << p.steps << " (" << p.desc << ")";
		proglen = ss.str().length();
		cout << ss.str() << std::flush;
		if(p.step != p.steps) cout.seekp(pos);
		else{
			cout << endl;
			proglen = 0;
		}
	};
	
	auto installPath = ParsePath(path);
	if(installPath.back() == '/') installPath = installPath.substr(0, installPath.length() - 1);
	PackageFile pkgFile(filePath);
	cout << "Installing package \"" << pkgFile.GetInfo().name << "\" to \"" << installPath << "\"..." << endl;
	auto res = pkgFile.Install(installPath, progressFn);
	if(res.success) cout << "Install successful." << endl;
	else{
		cout << "Install failed:" << endl;
		for(const auto &m : res.messages){
			cout << "  " << m << endl;
		}
	}
}

static void DeleteDirectory(const string &path){
	btos_api::Directory dir(path.c_str(), FS_Read);
	for(const auto &i : dir){
		auto fullPath = ParsePath(path + '/' + i.filename);
		if(i.type == FS_Directory){
			DeleteDirectory(fullPath);
		}else{
			remove(fullPath.c_str());
		}
		if(bt_stat(fullPath.c_str()).type != FS_Invalid){
			cout << "Failed to delete \"" << fullPath << "\"" << endl;
		}
	}
	remove(path.c_str());
	if(bt_stat(path.c_str()).type != FS_Invalid){
		cout << "Failed to remove directory \"" << path << "\"" << endl;
	}
}

void UninstallPackage(const string &name, const string &path, bool keepFiles){
	reg::PackageInfo info;
	if(!path.empty()){
		auto fullPath = ParsePath(path);
		if(fullPath.back() == '/') fullPath = fullPath.substr(0, fullPath.length() - 1);
		info = reg::GetPackageByPath(fullPath);
		if(info.name.empty()){
			cout << "Package not found at path \"" << path << "\"." << endl;
			return;
		}
	}else{
		info = reg::GetPackageByName(name);
		if(info.name.empty()){
			cout << "Package \"" << name << "\" is not installed." << endl;
			return;
		}
	}
	
	if(!keepFiles){
		auto subs = reg::GetSubPackages(info.id);
		if(!subs.empty()){
			cout << "Package has sub-packages installed. Cannot delete packages files (use -k to uninstall without deleting)." << endl;
			cout << "Sub-packages:" << endl;
			for(auto &s : subs){
				cout << "  " << s << endl;
			}
			return;
		}
	}
	
	cout << "Uninistalling package \"" << info.name << "\" from \"" << info.path << "\"";
	if(!keepFiles) cout << " and deleting all files";
	cout << "..." << endl;
	
	auto features = reg::GetFeatures(info.id);
	for(auto &f : features){
		auto feat = reg::GetFeatureByName(f);
		reg::DeleteFeature(feat.id);
	}
	reg::DeletePackage(info.id);
	
	if(!keepFiles) DeleteDirectory(info.path);
	cout << "Uninstall complete." << endl;
}

