#include "cmd.hpp"
#include <sstream>
#include <iostream>

using namespace std;

bool is_absolute(const string &path){
	for(const char &c : path){
		if(c=='/') return false;
		if(c==':') return true;
	}
	return false;
}

string get_drive(const string &path){
	stringstream ret;
	for(const char &c : path){
		ret <<  c;
		if(c==':') break;
	}
	return ret.str();
}

string parse_path(string path){
	if(!is_absolute(path)){
		if(path[0]=='/'){
			path=get_drive(get_cwd()) + path;
		}else{
			path=get_cwd() + "/" + path;
		}
	}
	vector<string> sections;
	stringstream current;
	bool has_drive=false;
	for(const char &c : path){
		if(c==':'){
			string cstr=current.str();
			if(!has_drive && cstr.length()){
				cstr += ':';
				sections.push_back(cstr);
				current.str("");
				has_drive=true;
			}else{
				return "";
			}
		}else if(c=='/'){
			string cstr=current.str();
			if(cstr==".."){
				if(sections.size() > 1){
					sections.pop_back();
				}else{
					return "";
				}
			}else if(cstr=="."){
				//ignore...
			}else if(cstr.length()){
				sections.push_back(cstr);
			}
			current.str("");
		} else current << c;
	}
	if(current.str().length()){
		string cstr=current.str();
		if(cstr==".."){
			if(sections.size() > 1){
				sections.pop_back();
			}else{
				return "";
			}
		}else if(cstr=="."){
			//ignore...
		}else sections.push_back(cstr);
	}
	stringstream final;
	for(const string &s : sections){
		final << s << '/';
	}
	string result=final.str();
	if(sections.size() > 1){
		result.erase(result.length()-1);
	}
	return result;
}