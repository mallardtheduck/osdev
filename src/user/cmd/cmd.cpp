#include "cmd.hpp"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

int main(int argc, char **argv){
	run_command({"ver"});
	bool cont;
	do{
		string input=get_input();
		vector<string> p=parse_input(input);
		cont=run_command(p);
	}while(cont);
	return 0;
}