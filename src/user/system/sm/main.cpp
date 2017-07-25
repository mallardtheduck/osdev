#include <iostream>
#include <string>
#include <vector>
#include <tuple>

#include <btos/processlist.hpp>
#include <btos/envvars.hpp>
#include <btos/ini.hpp>

#include <sm/sessions.hpp>

using namespace std;
using namespace btos_api::sm;

static const string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/");
static const string ServicesPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/SERVICES/");


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
	if(entry.valid && entry.type == FS_File){
		auto file = ReadIniFile(sessionFilePath);
		auto section = file["session"];
		auto name = section["name"];
		auto leadElx = EnvInterpolate(section["lead"]);
		return {true, SessionType{name, leadElx}};
	}
	return {false, {}};
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


int main(int argc, char **argv){
	auto args = argv_to_vec(argc, argv);
	cout << "BT/OS Session Manager" << endl;

	if(args.size() < 2){
		cerr << "SM: No session type specified." << endl;
		return 0;
	}

	auto sessionType = GetSessionType(args[1]);

	if(sessionType.first){
		auto s = sessionType.second.Start();
		s.SetServiceResolver(&GetService);
		s.Run();
		cout << "SM: Ending session..." << flush;
		kill_children();
		cout << "Done." << endl;
	}else{
		cerr << "SM: Session type \"" << args[1] << "\" not found." << endl;
	}
	
	return 0;
}
