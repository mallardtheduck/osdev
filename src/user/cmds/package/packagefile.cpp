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
#include <cmd/scripting.hpp>

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

static string to_lower(const string &str){
	string ret(str);
	transform(str.begin(), str.end(), ret.begin(), ::tolower);
	return ret;
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
					if(s.first == "hooks"){
						hooks = s.second;
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
			auto type = rdr.is_next_directory() ? FS_Directory : FS_File;
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
	if(!RunHook(status, "pre-install", path)) return status;
	if(!CheckVersion(status)) return status;
	if(!CheckPathConflicts(status, path)) return status;
	if(!CheckFeatureConflicts(status)) return status;
	if(!ExtractFiles(status, path)) return status;
	if(!ImportInfo(status, path)) return status;
	if(!RunHook(status, "post-install", path)) return status;
	status.success = true;
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
	auto curPkg = reg::GetPackageByPath(path);
	if(curPkg.id > 0 && curPkg.name != packageInfo.name){
		stringstream ss;
		ss << "Another package (" << curPkg.name << ") is already installed at the path \"" << path << "\".";
		status.messages.push_back(ss.str());
		return false;
	}
	curPkg = reg::GetPackageByName(packageInfo.name);
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
	auto sorted = content;
	std::sort(sorted.begin(), sorted.end(), [](const ContentFile &a, const ContentFile &b) -> bool{
		return a.path.length() < b.path.length();
	});
	for(auto &c : sorted){
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

bool PackageFile::ImportInfo(PackageFile::InstallStatus &/*status*/, const string &path){
	auto curPkg = reg::GetPackageByName(packageInfo.name);
	if(curPkg.id > 0){
		auto feats = reg::GetFeatures(curPkg.id);
		for(auto &f : feats){
			auto feat = reg::GetFeatureByName(f);
			reg::DeleteFeature(feat.id);
		}
		reg::DeletePackage(curPkg.id);
	}
	packageInfo.path = path;
	packageInfo.id = reg::InstallPackage(packageInfo);
	for(auto & f : features){
		f.package = packageInfo.id;
		reg::InstallFeature(f);
	}
	return true;
}

bool PackageFile::RunHook(PackageFile::InstallStatus &status, const string &hook, const string &path){
	bool success = true;
	auto run = [&](const vector<string> &cmd, bool capture) -> string{
		if(cmd.size() == 2 && to_lower(cmd[0]) == "setstatus"){
			success = cmd::IsTruthy(cmd[1]);
			return "";
		}else if(cmd.size() == 2 && to_lower(cmd[0]) == "addmessage"){
			status.messages.push_back(cmd[1]);
			return "";
		}else return cmd::RunCMDCommand(cmd, capture);
	};
	
	auto get = [&](const string &name) -> string{
		if(to_lower(name) == "install_path"){
			return path;
		}else return GetEnv(name);
	};
	
	if(hooks.find(hook) != hooks.end()){
			tar::reader rdr(stream);
			while(rdr.contains_another_file()){
				if(filter_filename(rdr.get_next_file_name()) == hooks[hook]){
					stringstream scriptStream;
					{
						auto size = rdr.get_next_file_size();
						unique_ptr<char[]> buffer{new char[size]};
						rdr.read_next_file(buffer.get());
						scriptStream.write(buffer.get(), size);
						scriptStream.seekg(0);
					}
					cmd::ScriptContext context {scriptStream, run, get};
					context.Run({});
					break;
				}
				rdr.skip_next_file();
			}
			stream.seekg(0);
	}
	return success;
}
