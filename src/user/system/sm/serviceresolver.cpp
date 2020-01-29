#define BTOS_NO_USING
#include "serviceresolver.hpp"
#include <btos/envvars.hpp>
#include <btos/directory.hpp>
#include <btos/ini.hpp>

#include <btos/registry.hpp>
#include <btos/resc.h>

#include <algorithm>
#include <cctype>
#include <ext/stdio_filebuf.h>

namespace reg = btos_api::registry;
namespace resc = btos_api::resc;
namespace sm = btos_api::sm;

static const std::string ServicesPath = btos_api::EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/SERVICES/");

static char char_tolower(char ch){
    return static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
}

static void addService(const std::string &fname, std::map<std::string, btos_api::sm::Service> &serviceCache){
	auto info = btos_api::bt_stat(fname.c_str());
	if(info.type == FS_File){
		std::string filename = info.filename;
		if(filename.length() > 4){
			std::transform(filename.begin(), filename.end(), filename.begin(), char_tolower);
			auto ext = filename.substr(filename.length() - 4);
			
			btos_api::IniFile file;
			if(ext == ".ini"){
				file = btos_api::ReadIniFile(fname);
			}else if(ext == ".elx"){
				auto h = resc::Resc_FileOpen(fname);
				auto serviceIni = resc::Resc_OpenResc(h, "service.ini");
				if(serviceIni){
					__gnu_cxx::stdio_filebuf<char> filebuf(serviceIni, std::ios::in);
					std::istream is(&filebuf);
					file = btos_api::ReadIniFile(is);
				}
				resc::Resc_Close(h);
			}
			if(!file.empty()){
				auto varGet = [&](const std::string &key){
					if(key == "this") return fname;
					else return btos_api::GetEnv(key);
				};
				auto section = file["service"];
				auto name = section["name"];
				auto path = btos_api::Interpolate(section["path"], varGet);
				std::string cleanup;
				if(section.find("cleanup") != section.end()){
					cleanup = btos_api::Interpolate(section["cleanup"], varGet);
				}
				bool sticky = false;
				if(section.find("sticky") != section.end()){
					sticky = (section["sticky"] == "true");
				}
				serviceCache.insert(std::make_pair(name, sm::Service{name, path, cleanup, sticky}));
			}
		}
	}
};

SessionServiceResolver::SessionServiceResolver(){
	UpdateCache();
}

void SessionServiceResolver::UpdateCache(){
	btos_api::Directory dir{ServicesPath.c_str(), FS_Read};
	for(auto f : dir){
		addService(ServicesPath + f.filename, serviceCache);
	}
	auto feats = reg::GetFeaturesByType("sm.svc");
	for(auto &f : feats){
		auto feat = reg::GetFeatureByName(f);
		auto fname = reg::GetFeaturePath(feat.id);
		addService(fname, serviceCache);
	}
}

std::pair<bool, sm::Service> SessionServiceResolver::GetService(const std::string &name){
	if(serviceCache.find(name) != serviceCache.end()){
		return {true, serviceCache.at(name)};
	}else{
		std::cout << "Service \"" << name << "\" not found!" << std::endl;
		return {false, {}};
	}
}

std::vector<sm::Service> SessionServiceResolver::GetServices(){
	std::vector<sm::Service> ret;
	for(auto s : serviceCache){
		ret.push_back(s.second);
	}
	return ret;
}
