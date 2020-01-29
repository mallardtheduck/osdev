#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>
#include <algorithm>

#include <btos/processlist.hpp>
#include <btos/envvars.hpp>
#include <btos/ini.hpp>
#include <dev/terminal.hpp>
#include <btos/registry.hpp>

#include <sm/sessions.hpp>

#include "serviceresolver.hpp"

using namespace std;
using namespace btos_api::sm;
namespace reg = btos_api::registry;

static const string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/");

extern void RegTest();

vector<string> argv_to_vec(int argc, char **argv){
	vector<string> ret;
	for(int i = 0; i < argc; ++i){
		ret.push_back(argv[i]);
	}
	return ret;
}

void kill_children(){
	auto pid = bt_getpid();
	bool found = true;

	while(found){
		found = false;
		ProcessList procs;
		for(auto proc : procs){
			if(proc.Parent() == pid){
				found = true;
				auto p = proc.GetProcess();
				p.Kill();
			}
		}
	}
}

std::pair<bool, SessionType> GetSessionType(string &name){
	auto sessions = GetSessionTypes();
	
	auto ses = std::find_if(sessions.begin(), sessions.end(), [&](const SessionType &s){
		return s.GetID() == name;
	});
	if(ses != sessions.end()) return {true, *ses};
	else return {false, {}};
}


int main(int argc, char **argv){
	auto args = argv_to_vec(argc, argv);
	cout << "BT/OS Session Manager" << endl;

	if(args.size() < 2){
		cerr << "SM: No session type specified." << endl;
		return 0;
	}

	auto sessionType = GetSessionType(args[1]);

	if(sessionType.first){
		Terminal().SetTitle(sessionType.second.GetName());
		auto s = sessionType.second.Start();
		s.SetServiceResolver(make_shared<SessionServiceResolver>());
		s.Run();
		cout << "SM: Ending session..." << flush;
		kill_children();
		cout << "Done." << endl;
	}else{
		cerr << "SM: Session type \"" << args[1] << "\" not found." << endl;
	}
	
	return 0;
}
