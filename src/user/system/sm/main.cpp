#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <sstream>

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
	auto sessionFilePath = SessionsPath + name + ".ini";
	auto entry = bt_stat(sessionFilePath.c_str());
	if(!entry.valid || entry.type != FS_File){
		auto feat = reg::GetFeatureByName(name);
		std::stringstream ss;
		ss << "\'" << name << "\' is a feature." << std::endl;
		ss << feat.description << std::endl;
		bt_zero(ss.str().c_str());
		if(feat.type == "sm.ses"){
			auto pkg = reg::GetPackageById(feat.package);
			sessionFilePath = pkg.path + feat.path + feat.file;
			entry = bt_stat(sessionFilePath.c_str());
		}
	}
	if(entry.valid && entry.type == FS_File){
		auto file = ReadIniFile(sessionFilePath);
		auto section = file["session"];
		auto name = section["name"];
		auto leadElx = EnvInterpolate(section["lead"]);
		vector<string> svcs;
		if(file.find("services") != file.end()){
			auto services = file["services"];
			for(auto s : services){
				svcs.push_back(s.second);
			}
		}
		return {true, SessionType{name, leadElx, svcs}};
	}
	return {false, {}};
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
