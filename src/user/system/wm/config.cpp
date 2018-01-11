#include "config.hpp"
#include "ini.hpp"

using namespace std;

static const string configSection = "WM";

static IniFile config;

void ParseConfig(const string &path){
	config = ReadIniFile(path);
}

string GetConfigValue(const string &name){
	if(config.find(configSection) != config.end()){
		if(config[configSection].find(name) != config[configSection].end()){
			return config[configSection][name];
		}
	}
	return "";
}
