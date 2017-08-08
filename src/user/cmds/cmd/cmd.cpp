#include "cmd.hpp"
#include <cmd/scripting.hpp>
#include <iostream>
#include <fstream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

bool run_command(const string &input){
	vector<string> p=parse_command(input);
    vector<command> cmds=getcommands(p);
    for(command &c : cmds) {
        c.openio();
        if(!run_command(c)) {
            return false;
        }
        c.closeio();
    }
	return true;
}

void run_interactive(){
 	run_command("ver");
	while(true){
		string input=get_input();
        if(!run_command(input)) break;
	};
}

void run_script(const string &file, vector<string> args){
	ifstream script {file};
	ScriptContext context {script};
	context.Run(args);
}

int main(int argc, char **argv){
	vector<string> args{ &argv[0], &argv[argc] };
	if(args.size() == 1){
	    run_interactive();
	}else{
		if(args[1] == "-s" && args.size() >= 3){
			auto file = args[2];
			vector<string> sc_args;
			if(args.size() > 3){
				for(size_t i = 3; i < args.size(); ++i)	sc_args.push_back(args[i]);
			}
			run_script(file, sc_args);
		}else if(args[1] == "-c" && args.size() == 3){
			run_command(args[2]);
		}else{
			cout << "Usage:" << endl;
			cout << args[0] << " : for interative mode." << endl;
			cout << args[0] << " -s filename : to run script." << endl;
			cout << args[0] << " -c command : to run single command." << endl;
		}
	}
	return 0;
}
