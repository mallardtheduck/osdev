#include "services.hpp"
#include <btos/envvars.hpp>
#include <btos/ini.hpp>

using namespace std;

static const string ServicesPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/SERVICES/");

Process Service::Start(){
	return Process::Spawn(path);
}

string Service::Name(){
	return name;
}

string Service::Path(){
	return path;
}

pair<bool, Service> GetService(std::string name){
	auto serviceFilePath = ServicesPath + name + ".ini";
	auto entry = bt_stat(serviceFilePath.c_str());
	if(entry.valid && entry.type == FS_File){
		auto file = ReadIniFile(serviceFilePath);
		auto section = file["service"];
		auto name = section["name"];
		auto path = EnvInterpolate(section["path"]);
		return {true, Service{name, path}};
	}
	return {false, {}};
}
