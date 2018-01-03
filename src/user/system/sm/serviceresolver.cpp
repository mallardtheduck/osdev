#include "serviceresolver.hpp"
#include <btos/envvars.hpp>
#include <btos/directory.hpp>
#include <btos/ini.hpp>

#include <btos/registry.hpp>

using namespace sm;
using namespace std;

namespace reg = btos_api::registry;

static const string ServicesPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/SERVICES/");

SessionServiceResolver::SessionServiceResolver(){
	UpdateCache();
}

void SessionServiceResolver::UpdateCache(){
	auto addService = [&](const string &fname){
		auto info = bt_stat(fname.c_str());
		if(info.type == FS_File){
			auto file = ReadIniFile(fname);
			auto section = file["service"];
			auto name = section["name"];
			auto path = EnvInterpolate(section["path"]);
			string cleanup;
			if(section.find("cleanup") != section.end()){
				cleanup = EnvInterpolate(section["cleanup"]);
			}
			serviceCache.insert(make_pair(name, Service{name, path, cleanup}));
		}
	};
	Directory dir{ServicesPath.c_str(), FS_Read};
	for(auto f : dir){
		addService(ServicesPath + f.filename);
	}
	auto feats = reg::GetFeaturesByType("sm.svc");
	for(auto &f : feats){
		auto feat = reg::GetFeatureByName(f);
		auto fname = reg::GetFeaturePath(feat.id);
		addService(fname);
	}
}

pair<bool, Service> SessionServiceResolver::GetService(const std::string &name){
	if(serviceCache.find(name) != serviceCache.end()){
		return {true, serviceCache.at(name)};
	}else{
		cout << "Service \"" << name << "\" not found!" << endl;
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
