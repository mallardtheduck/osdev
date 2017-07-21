#include <iostream>
#include <string>
#include <vector>
#include <btos/envvars.hpp>

using namespace std;
using namespace btos_api;

vector<string> argv_to_vec(int argc, char **argv){
	vector<string> ret;
	for(int i = 0; i < argc; ++i){
		ret.push_back(argv[i]);
	}
	return ret;
}

int main(int argc, char **argv){
	auto args = argv_to_vec(argc, argv);
	cout << "BT/OS Session Manager" << endl;

	cout << EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS") << endl;

	if(args.size() < 2){
		cerr << "SM: No session type specified." << endl;
	}

	
	return 0;
}
