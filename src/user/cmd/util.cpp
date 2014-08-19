#include "cmd.hpp"

using namespace std;

const string default_prompt="[$p]";
const string prompt_var="PROMPT";
const string cwd_var="CWD";
const string default_cwd="INIT:/";

string get_env(const string &name){
	char value[128];
	string ret;
	size_t size=bt_getenv(name.c_str(), value, 128);
	ret=value;
	if(size>128){
		char *buf=new char[size];
		bt_getenv(name.c_str(), value, size);
		ret=buf;
	}
	if(size) return ret;
	else return "";
}

string get_env(const string &name, const string &def_value){
	string ret=get_env(name);
	if(ret==""){
		set_env(name, def_value);
		return def_value;
	}
	return ret;
}

void set_env(const string &name, const string &value){
	bt_setenv(name.c_str(), value.c_str(), 0);
}

string get_prompt(){
	return get_env(prompt_var, default_prompt);
}

string get_cwd(){
	return get_env(cwd_var, default_cwd);
}

void set_cwd(const string &value){
	set_env(cwd_var, value);
}
