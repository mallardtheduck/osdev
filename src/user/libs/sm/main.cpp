#include <sm/sm.h>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

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
		for(size_t i = 0; i< svccount; ++i){
			auto info = SM_GetServiceInfo(i);
			cout << info.name << endl;
		}
	}else{
		cout << "Unknown command \"" << args[1] << "\"." << endl;
	}
	return 0;
}
