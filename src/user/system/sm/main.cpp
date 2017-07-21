#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "sessions.hpp"

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
	cout << "BT/OS Session Manager" << endl;

	if(args.size() < 2){
		cerr << "SM: No session type specified." << endl;
		return 0;
	}

	auto sessionType = GetSessionType(args[1]);

	if(sessionType.first){
		auto p = sessionType.second.Start();
		p.Wait();
		cout << "SM: Ending session..." << flush;
		cout << "Done." << endl;
	}else{
		cerr << "SM: Session type \"" << args[1] << "\" not found." << endl;
	}
	
	return 0;
}
