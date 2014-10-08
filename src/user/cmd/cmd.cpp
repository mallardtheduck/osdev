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
        for(const command &c : cmds) {
            if(!run_command(c)) {
                cont=false;
                break;
            }
        }
        if(!cont) break;
	};
	return 0;
}