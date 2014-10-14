#include "cmd.hpp"
#include <iostream>
#include <cstdint>
#include <sstream>
#include <cctype>
#include <ioctl.h>
#include <drivers.h>
#include <cstdlib>
#include <fstream>
#include <terminal.h>
#include "../../include/keyboard.h"

using namespace std;

bt_filehandle input_fh=0;
bool input_tty=true;

extern "C" bt_handle btos_get_handle(int fd);

void open_input(){
    bt_filehandle fh=btos_get_handle(fileno(stdin));
	if(!fh) {
        cerr << "Error: Could not open input file/device: " << get_env("STDIN") << endl;
        exit(-1);
	}
	input_fh=fh;
    size_t type=bt_fioctl(input_fh, bt_ioctl::DevType, 0, NULL);
    if(type!=driver_types::TERMINAL && (type & driver_types::INPUT)!=driver_types::INPUT) input_tty=false;
}

char get_char() {
    if (!input_fh) open_input();
    char ret = '\0';
    size_t bytes = bt_fread(input_fh, sizeof(ret), &ret);
    if (!input_tty && bytes == 0) {
        cerr << "Warning: End of input file/device reached." << endl;
        exit(0);
    }
    return ret;

}

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
    if(!input_fh) open_input();
	if(input_tty) cout << prompt_string();
	return input_line();
}
