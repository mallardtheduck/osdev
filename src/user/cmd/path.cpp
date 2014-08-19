#include "cmd.hpp"
#include <sstream>

using namespace std;

bool is_absolute(const string &path){
	for(const char &c : path){
		if(c=='/') return false;
		if(c==':') return true;
	}
	return false;
}

string parse_path(string path){
	if(!is_absolute(path)){
		path=get_cwd() + "/" + path;
	}
	vector<string> sections;
	stringstream current;
	bool has_drive=false;
	for(const char &c : path){
		if(c==':'){
			string cstr=current.str();
			if(!has_drive && cstr.length()){
				current << c;
				sections.push_back(cstr);
				current.str("");
			}else{
				return "";
			}
		}else if(c=='/'){
			string cstr=current.str();
			if(cstr==".."){
				sections.pop_back();
			}else if(cstr=="."){
				//ignore...
			}else if(cstr.length()){
				sections.push_back(cstr);
			}
		}
	}
	if(current.str().length()) sections.push_back(current.str());
	stringstream ret;
	bool first=true;
	for(const string &s : sections){
		if(first){
			ret << s;
			first=false;
		}else{
			ret << '/' << s;
		}
	}
	return ret.str();
}