#include "cmd.hpp"
#include <sstream>
#include <fstream>
#include <unistd.h>

using namespace std;

extern "C" bt_handle btos_get_handle(int fd);

string input_line(){
    string ret;
    getline(cin, ret);
    return ret;
}

vector<string> parse_input(const string &input){
	vector<string> ret;
	stringstream current;
	bool quoted=false, escape=false, list=false;
	for(const char &c : input){
		if(!escape && !quoted && !list && isspace(c)){
			string cstr=current.str();
			if(cstr.length()) ret.push_back(cstr);
			current.str("");
		}else if(!escape && !list && c=='"'){
			quoted=!quoted;
		}else if(!quoted && !list && c=='['){
			current << '[';
			list=true;
		}else if(!quoted && list && c==']'){
			current << ']';
			list=false;
		}else if(!escape && c=='\\'){
			escape=true;
		}else if(escape){
			if(c=='n') current << '\n';
			else current << c;
			escape=false;
		}else current << c;
	}
	if(current.str().length()) ret.push_back(current.str());
	return ret;
}

enum class cmd_token{
    arg,
    input,
    output,
};

vector<command> getcommands(vector<string> parsed){
    vector<command> ret;
    command current;
    cmd_token next=cmd_token::arg;
    for(const string &p : parsed){
        if(next==cmd_token::arg) {
            if (p == "|") {
                string file = tempfile();
                current.set_output(file);
                ret.push_back(current);
                current = command();
                current.set_input(file);
            } else if (p == ">") {
                next = cmd_token::output;
            } else if (p == "<") {
                next = cmd_token::input;
            }else{
                current.args.push_back(p);
            }
        }else if(next==cmd_token::input){
            string file=parse_path(p);
            current.set_input(file);
            next=cmd_token::arg;
        }else if(next==cmd_token::output){
            string file=parse_path(p);
            current.set_output(file);
            ofstream f(file);
            f.close();
            next=cmd_token::arg;
        }
    }
    ret.push_back(current);
    return ret;
}

string get_input(){
    bool input_tty=(bool)isatty(fileno(stdin));
   	if(input_tty) cout << prompt_string();
	return input_line();
}
