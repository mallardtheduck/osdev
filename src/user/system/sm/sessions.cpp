#include "sessions.hpp"
#include <btos/envvars.hpp>

using namespace std;
using namespace btos_api;

static const string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS");

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
	return Process::Spawn(leadElx);
}

