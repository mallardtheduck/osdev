#include "serviceresolver.hpp"
#include <btos/envvars.hpp>
#include <btos/directory.hpp>
#include <btos/ini.hpp>

using namespace sm;
using namespace std;

static const string ServicesPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/SERVICES/");

SessionServiceResolver::SessionServiceResolver(){
	UpdateCache();
}

void SessionServiceResolver::UpdateCache(){
	Directory dir{ServicesPath.c_str(), FS_Read};
	for(auto f : dir){
		if(f.type == FS_File){
			auto file = ReadIniFile(ServicesPath + f.filename);
			auto section = file["service"];
			auto name = section["name"];
			auto path = EnvInterpolate(section["path"]);
			serviceCache.insert(make_pair(name, Service{name, path}));
		}
	}
}

pair<bool, Service> SessionServiceResolver::GetService(const std::string &name){
	if(serviceCache.find(name) != serviceCache.end()){
		return {true, serviceCache.at(name)};
	}else{
		return {false, {}};
	}
}

vector<Service> SessionServiceResolver::GetServices(){
	vector<Service> ret;
	for(auto s : serviceCache){
		ret.push_back(s.second);
	}
	return ret;
}
