#include <btos.h>
#include <cmd/utils.hpp>
#include <cmd/path.hpp>
#include <cmd/commands.hpp>
#include <algorithm>
#include <sstream>
#include <btos/envvars.hpp>

#include <fstream>

using namespace std;

namespace btos_api{
namespace cmd{

const string default_prompt="[$cwd$]";
const string prompt_var="PROMPT";
const string cwd_var="CWD";
const string default_cwd="INIT:/";

uint64_t tempcounter=0;

string get_env(const string &name){
	return GetEnv(name);
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
	return EnvInterpolate(get_env(prompt_var, default_prompt));
}

string get_cwd(){
	return get_env(cwd_var, default_cwd);
}

void set_cwd(const string &value){
	set_env(cwd_var, value);
}

string to_lower(const string &str){
	string ret(str);
	transform(str.begin(), str.end(), ret.begin(), ::tolower);
	return ret;
}

void trim(string& str){
	string::size_type pos = str.find_last_not_of(' ');
	if(pos != string::npos) {
		str.erase(pos + 1);
		pos = str.find_first_not_of(' ');
		if(pos != string::npos) str.erase(0, pos);
	}
	else{
		str.erase(str.begin(), str.end());
	}
}

vector<string> split(const string &str, char delim) {
	vector<string> elems;
	stringstream ss(str);
	string item;
	while(getline(ss, item, delim)) {
		trim(item);
		if(item!=""){
			elems.push_back(item);
		}
	}
	return elems;
}

vector<string> get_paths(){
    string path=get_env("PATH");
    vector<string> ret=split(path, ',');
    if(find(ret.begin(), ret.end(), ".") == ret.end()) ret.push_back(".");
    return ret;
}

bool ends_with(const string &str, const string &end){
    if (str.length() >= str.length()) {
        return (0 == str.compare(str.length() - end.length(), end.length(), end));
    } else {
        return false;
    }
}

string tempfile(){
    stringstream ret;
    string temppath=get_env("TEMP");
    if(!temppath.length()) temppath=".";
    ret << temppath << "/" << "temp_cmd_" << bt_getpid() << "_" << tempcounter << ".tmp";
    tempcounter++;
    string path=parse_path(ret.str());
    if(path.length()){
        FILE *fh=fopen(path.c_str(), "w");
        fclose(fh);
    }
    return path;
}

enum class cmd_token{
    arg,
    input,
    output,
};

vector<command> getcommands(const vector<string> &parsed, const string &default_output, const string &default_input){
    vector<command> ret;
    command current { default_input, default_output };
    cmd_token next=cmd_token::arg;
    for(const string &p : parsed){
        if(next==cmd_token::arg) {
            if (p == "|") {
                string file = tempfile();
                current.set_output(file);
                ret.push_back(current);
                current = command(file, default_output);
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

vector<string> parse_command(const string &input){
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

}
}
