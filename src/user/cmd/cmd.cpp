#include "cmd.hpp"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

int main(int argc, char **argv){
    command vercmd;
    vercmd.args={"ver"};
	run_command(vercmd);
	while(true){
        bool cont=true;
		string input=get_input();
		vector<string> p=parse_input(input);
        vector<command> cmds=getcommands(p);
        for(command &c : cmds) {
            c.openio();
            if(!run_command(c)) {
                cont=false;
                break;
            }
            c.closeio();
        }
        if(!cont) break;
	};
	return 0;
}