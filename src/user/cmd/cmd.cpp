#include "cmd.hpp"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

int main(int argc, char **argv){
	cout << "BT/OS Command prompt" << endl;
	print_os_version();
	bool cont;
	do{
		string input=get_input();
		vector<string> p=parse_input(input);
		cont=run_command(p);
	}while(cont);
	return 0;
}