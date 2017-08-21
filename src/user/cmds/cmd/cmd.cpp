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
        if(!run_command(c)) {
            return false;
        }
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

void run_script(const string &file, vector<string> args, bool debug){
	ifstream script {file};
	if(script){
		ScriptContext context {script};
		context.SetDebugOutput(debug);
		context.Run(args);
	}else{
		cerr << "Script could not be run." << endl;
	}
}

int main(int argc, char **argv){
	vector<string> args{ &argv[0], &argv[argc] };
	if(args.size() == 1){
	    run_interactive();
	}else{
		if((args[1] == "-s" || args[1] == "-sd") && args.size() >= 3){
			auto file = args[2];
			vector<string> sc_args;
			if(args.size() > 3){
				for(size_t i = 3; i < args.size(); ++i)	sc_args.push_back(args[i]);
			}
			run_script(file, sc_args, args[1] == "-sd");
		}else if(args[1] == "-c" && args.size() == 3){
			run_command(args[2]);
		}else{
			cout << "Usage:" << endl;
			cout << args[0] << " : for interative mode." << endl;
			cout << args[0] << " -s[d] filename : to run script. d enables debugging output." << endl;
			cout << args[0] << " -c command : to run single command." << endl;
		}
	}
	return 0;
}
