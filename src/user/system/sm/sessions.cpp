#include "sessions.hpp"
#include "to_string.hpp"
#include <btos/envvars.hpp>
#include <btos/ini.hpp>
#include <btos.h>

using namespace std;
using namespace btos_api;

static const string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/");

SessionType::SessionType(const std::string &n, const std::string &l) : name(n), leadElx(l)
{}

string SessionType::GetName(){
	return name;
}

void SessionType::SetName(const string &n){
	name = n;
}

string SessionType::GetLeadElx(){
	return leadElx;
}

void SessionType::SetLeadElx(const string &l){
	leadElx = l;
}

Process SessionType::Start(){
	SetEnv("SM_PID", to_string(bt_getpid()));
	return Process::Spawn(leadElx);
}

std::pair<bool, SessionType> GetSessionType(string &name){
	auto sessionFilePath = SessionsPath + name + ".ini";
	auto entry = bt_stat(sessionFilePath.c_str());
	if(entry.valid && entry.type == FS_File){
		auto file = ReadIniFile(sessionFilePath);
		auto section = file["session"];
		auto name = section["name"];
		auto leadElx = EnvInterpolate(section["lead"]);
		return {true, SessionType{name, leadElx}};
	}
	return {false, {}};
}
