#include "sessions.hpp"
#include "to_string.hpp"
#include <btos.h>

#include <btos/envvars.hpp>
#include <btos/ini.hpp>
#include <btos/messageloop.hpp>
#include <btos/imessagehandler.hpp>
#include <btos/processlist.hpp>

#include <algorithm>

using namespace std;
using namespace btos_api;

static const string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/");

Session::Session(const Process &p) : lead(p), procs{ lead } {}

void Session::Run(){
	bt_subscribe(bt_kernel_messages::ProcessStart);
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	
	MessageLoop msgLoop;
	msgLoop.AddHandler(make_shared<CustomHandler>( [&](const Message &msg) -> bool{
		if(msg.From() == 0 && msg.Source() == 0){
			if(msg.Type() == bt_kernel_messages::ProcessStart){
				auto pid = msg.Content<bt_pid_t>();
				ProcessList lst;
				for(auto p : lst){
					if(p.PID() == pid && find(procs.begin(), procs.end(), p.Parent()) != procs.end()){
						procs.push_back(p.GetProcess());
					}
				}
			} else if(msg.Type() == bt_kernel_messages::ProcessEnd){
				auto pid = msg.Content<bt_pid_t>();
				if(pid == lead.GetPID()){
					for(auto p : procs) p.Kill();
					procs.clear();
					return false;
				} else if(find(procs.begin(), procs.end(), pid) != procs.end()){
					remove(procs.begin(), procs.end(), pid);
				}
			}
		}
		return true;
	}));
	msgLoop.RunLoop();
}

void Session::End(){
}

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

Session SessionType::Start(){
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
