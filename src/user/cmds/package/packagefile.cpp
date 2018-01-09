#include "packagefile.hpp"
#include "package.hpp"
#include <btos/ini.hpp>
#include <memory>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <algorithm>
#include <sys/stat.h>

#include <btos.h>
#include <btos/directory.hpp>

using std::string;
using std::unique_ptr;
using std::stringstream;
using std::vector;
using std::ofstream;

namespace reg = btos_api::registry;

const size_t MaxInfSize = 1 * 1024 * 1024;
const size_t ReadBufferSize = 4096;

vector<int> parse_version(const string &str){
	vector<int> ret;
	string cur;
	bool first = true;
	for(auto c : str){
		if(first && tolower(c) == 'v') continue;
		first = false;
		
		if(isdigit(c)) cur += c;
		else{
			if(!cur.empty()){
				ret.push_back(atoi(cur.c_str()));
				cur.clear();
			}
			if(c == '.' || c == '-') continue;
			ret.push_back((tolower(c) - 'a') + 1);
		}
	}
	if(!cur.empty()) ret.push_back(atoi(cur.c_str()));
	return ret;
}

bool compare_versions(vector<int> old, vector<int> tst){
	for(size_t i = 0; i < std::min(old.size(), tst.size()); ++i){
		if(tst[i] > old[i]) return true;
		if(tst[i] < old[i]) return false;
	}
	if(tst.size() > old.size()) return true;
	return false;
}

static string filter_filename(const string &name){
	if(starts_with(name, "./")){
		return name.substr(2);
	}else return name;
}

static string get_install_path(const string &contentPath, const string &name){
	auto filename = filter_filename(name);
	return filename.substr(contentPath.length());
}

static bool is_content(const string &contentPath, const string &name){
	auto filename = filter_filename(name);
	if(starts_with(filename, contentPath) && get_install_path(contentPath, name) != "") return true;
	else return false;
}

void PackageFile::Parse(){
	tar::reader rdr(stream);
	while(rdr.contains_another_file()){
		if(rdr.get_next_file_size() <= MaxInfSize && filter_filename(rdr.get_next_file_name()) == "package.inf"){
			stringstream infStream;
			{
				auto size = rdr.get_next_file_size();
				unique_ptr<char[]> buffer{new char[size]};
				rdr.read_next_file(buffer.get());
				infStream.write(buffer.get(), size);
				infStream.seekg(0);
			}
			auto infFile = btos_api::ReadIniFile(infStream);
			if(infFile.find("package") != infFile.end()){
				auto pkgsection = infFile["package"];
				packageInfo.name = get_or_blank(pkgsection, "name");
				packageInfo.description = get_or_blank(pkgsection, "description");
				packageInfo.ver = get_or_blank(pkgsection, "version");
				packageInfo.path = "NOT YET INSTALLED";
				contentPath = filter_filename(get_or_blank(pkgsection, "contentPath"));
				if(packageInfo.name == "" || contentPath == "") return;
				if(contentPath.back() != '/') contentPath += '/';
				
				for(auto &s : infFile){
					if(starts_with(s.first, "feature")){
						reg::FeatureInfo featinfo;
						featinfo.package = -1;
						featinfo.name = get_or_blank(s.second, "name");
						featinfo.description = get_or_blank(s.second, "description");
						featinfo.path = get_or_blank(s.second, "path");
						featinfo.file = get_or_blank(s.second, "file");
						featinfo.type = get_or_blank(s.second, "type");
						featinfo.ver = get_or_blank(s.second, "version");
						featinfo.flags = 0;
						
						if(featinfo.name == "") continue;
						if(featinfo.ver == "") featinfo.ver = packageInfo.ver;
						features.push_back(featinfo);
					}
				}
			}
		}else{
			rdr.skip_next_file();
		}
	}
	stream.seekg(0);
}

void PackageFile::ParseContent(){
	tar::reader rdr(stream);
	while(rdr.contains_another_file()){
		if(is_content(contentPath, rdr.get_next_file_name())){
			auto installPath = get_install_path(contentPath, rdr.get_next_file_name());
			auto offset = rdr.get_next_file_offset();
			auto size = rdr.get_next_file_size();
			auto type = rdr.get_next_file_size() == 0 ? FS_Directory : FS_File;
			content.push_back({installPath, offset, size, type});
		}
		rdr.skip_next_file();
	}
	stream.seekg(0);
}

PackageFile::PackageFile(const string &path){
	stream.open(path);
	Parse();
}

reg::PackageInfo PackageFile::GetInfo(){
	return packageInfo;
}

vector<reg::FeatureInfo> PackageFile::GetFeatures(){
	return features;
}

vector<PackageFile::ContentFile> PackageFile::GetContent(){
	if(content.empty()) ParseContent();
	return content;
}

PackageFile::InstallStatus PackageFile::Install(const string &path){
	InstallStatus status = {false, 0, {}};
	if(!CheckVersion(status)) return status;
	if(!CheckPathConflicts(status, path)) return status;
	if(!CheckFeatureConflicts(status)) return status;
	if(!ExtractFiles(status, path)) return status;
	status.messages.push_back("Not implemented!");
	return status;
}

bool PackageFile::CheckVersion(PackageFile::InstallStatus &status){
	auto curPkg = reg::GetPackageByName(packageInfo.name);
	if(!curPkg.ver.empty()){
		auto curVer = parse_version(curPkg.ver);
		auto newVer = parse_version(packageInfo.ver);
		if(!compare_versions(curVer, newVer)){
			stringstream ss;
			ss << "The currently installed package version (" << curPkg.ver;
			ss << ") is the same or newer than the package version (" << packageInfo.ver << ").";
			status.messages.push_back(ss.str());
			return false;
		}
	}
	return true;
}

bool PackageFile::CheckPathConflicts(PackageFile::InstallStatus &status, const string &path){
	auto curPkg = reg::GetPackageByName(packageInfo.name);
	if(!curPkg.path.empty()){
		if(path != curPkg.path){
			stringstream ss;
			ss << "A version of this package is already installed at \"" << curPkg.path << "\".";
			status.messages.push_back(ss.str());
			return false;
		}
	}else{
		auto stat = bt_stat(path.c_str());
		if(stat.type == FS_Directory){
			Directory dir(path.c_str(), FS_Read);
			if(dir.begin() != dir.end()){
				stringstream ss;
				ss << "\"" << path << "\" exists and is not empty.";
				status.messages.push_back(ss.str());
				return false;
			}
		}else if(stat.type != FS_Invalid){
			stringstream ss;
			ss << "\"" << path << "\" exists and is not a directory.";
			status.messages.push_back(ss.str());
			return false;
		}
	}
	return true;
}

bool PackageFile::CheckFeatureConflicts(PackageFile::InstallStatus &status){
	auto curPkg = reg::GetPackageByName(packageInfo.name);
	bool ok = true;
	for(auto &f : features){
		auto feat = reg::GetFeatureByName(f.name);
		if(f.package && f.package != curPkg.id){
			stringstream ss;
			ss << "Feature \"" << f.name << "\" is already installed as part of another package (\"";
			auto pkg = reg::GetPackageById(f.package);
			ss << pkg.name << "\").";
			status.messages.push_back(ss.str());
			ok = false;
		}
	}
	return ok;
}

bool PackageFile::ExtractFiles(PackageFile::InstallStatus &status, const string &path){
	auto stat = bt_stat(path.c_str());
	if(stat.type != FS_Directory){
		auto res = mkdir(path.c_str(), 777);
		if(res){
			stringstream ss;
			ss << "Could not create directory \"" << path << "\".";
			status.messages.push_back(ss.str());
			return false;
		}
	}
	ParseContent();
	for(auto &c : content){
		string finalPath = ParsePath(path + "/" + c.path);
		if(!starts_with(finalPath, path)){
			stringstream ss;
			ss << "Invalid path: \"" << c.path <<"\".";
			status.messages.push_back(ss.str());
			return false;
		}
		if(c.type == FS_Directory){
			auto res = mkdir(finalPath.c_str(), 777);
			if(res){
				stringstream ss;
				ss << "Could not create directory \"" << finalPath << "\".";
				status.messages.push_back(ss.str());
				return false;
			}
		}else if(c.type == FS_File){
			ofstream file(finalPath);
			if(!file){
				stringstream ss;
				ss << "Could not create file \"" << finalPath << "\".";
				status.messages.push_back(ss.str());
				return false;
			}
			unique_ptr<char[]> buffer { new char[ReadBufferSize] };
			for(uint64_t p = 0; p < c.size; p += ReadBufferSize){
				uint64_t rdsz = std::min(c.size - p, (uint64_t)ReadBufferSize);
				stream.seekg(c.offset + p);
				stream.read(buffer.get(), rdsz);
				file.write(buffer.get(), rdsz);
			}
			stream.seekg(0);
		}
	}
	return true;
}

