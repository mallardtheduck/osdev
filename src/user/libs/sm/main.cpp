#include <sm/sm.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace sm;

vector<string> argv_to_vec(int argc, char **argv){
	vector<string> ret;
	for(int i = 0; i < argc; ++i){
		ret.push_back(argv[i]);
	}
	return ret;
}

int main(int argc, char **argv){
	auto args = argv_to_vec(argc, argv);
	if(args.size() < 2){
		cout << "Usage: " << args[0] << " command" << endl;
		return 0;
	}

	if(args[1] == "listservices"){
		size_t svccount = SM_GetServiceCount();
		cout << svccount << " services available:" << endl;
		for(size_t i = 0; i< svccount; ++i){
			auto info = SM_GetServiceInfo(i);
			cout << info.name << endl;
		}
	}else if(args[1] == "startservice"){
		if(args.size() < 3){
			cerr << "Service name needed." << endl;
			return 0; 
		}
		auto pid = SM_StartService(args[2]);
		cout << "Service \"" << args[2] << "\" started as PID: " << pid << endl;
	}else if(args[1] == "stopservice"){
		if(args.size() < 3){
			cerr << "Service name needed." << endl;
			return 0; 
		}
		SM_StopService(args[2]);
		cout << "Service \"" << args[2] << "\" stopped." << endl;
	}else{
		cout << "Unknown command \"" << args[1] << "\"." << endl;
	}
	return 0;
}
