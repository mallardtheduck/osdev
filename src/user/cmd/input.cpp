#include "cmd.hpp"
#include <iostream>
#include <cstdint>
#include <sstream>
#include <cctype>
#include "../../include/keyboard.h"

using namespace std;

bt_filehandle input_fh=0;
bool convert_input=false;

void open_input(){
	string device=get_env("STDIN");
	if(device==""){
		device="DEV:/" + get_env("INPUT_DEVICE");
		convert_input=true;
	}
	input_fh=bt_fopen(device.c_str(), FS_Read);
}

char get_char(){
	if(!input_fh) open_input();
	if(convert_input){
		uint32_t val;
		while(bt_fread(input_fh, sizeof(val), (char*)&val)){
			if(KB_char(val)){
				return val;
			}
		}
		return '\0';
	}else{
		char ret='\0';
		bt_fread(input_fh, sizeof(ret), &ret);
		return ret;
	}
}

string input_line(){
	stringstream ret;
	if(!input_fh) open_input();
	streampos pos=cout.tellp();
	while(char c=get_char()){
		if(c=='\n') break;
		else if(c==0x08){
			string data=ret.str();
			if(data.length())data.erase(data.length()-1);
			ret.str(data);
			ret.seekp(0, ios::end);
		}else ret << c;
		cout.seekp(pos);
		cout << ret.str();
		streampos newpos=cout.tellp();
		cout << ' ';
		cout.seekp(newpos);

	}
	cout << endl;
	return ret.str();
}

vector<string> parse_input(const string &input){
	vector<string> ret;
	stringstream current;
	bool quoted=false, escape=false;
	for(const char &c : input){
		if(!escape && !quoted && isspace(c)){
			string cstr=current.str();
			if(cstr.length()) ret.push_back(cstr);
			current.str("");
		}else if(!escape && c=='"'){
			quoted=!quoted;
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

string get_input(){
	cout << prompt_string();
	return input_line();
}
