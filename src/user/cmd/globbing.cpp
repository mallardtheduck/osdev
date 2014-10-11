#include "cmd.hpp"
#include <sstream>

using namespace std;

bool is_match(const string &opattern, const string &ofilename){
    if(ofilename=="." || ofilename=="..") return false;
	string pattern=to_lower(opattern);
	string filename=to_lower(ofilename);
	size_t fnpos=0;
	bool matchany=false;
	for(const char &c : pattern){
		if(c=='?'){
			fnpos++;
			if(filename.length() < fnpos) {
				return false;
			}
		}else if(c=='*'){
			matchany=true;
		}else if(c==filename[fnpos]){
			fnpos++;
		}else if(matchany){
			while(c!=filename[fnpos]){
				fnpos++;
				if(fnpos>=filename.length()){
					return false;
				}
			}
			matchany=false;
			fnpos++;
		}else{
			return false;
		}
	}
	if(fnpos<filename.length() && !matchany){
		return false;
	}
	else return true;
}

vector<string> find_matches(const string &s){
	string fullpath=parse_path(s);
	string filepart=path_file(fullpath);
	string pathpart=path_path(fullpath);
	vector<string> ret;
	bt_dirhandle dir=bt_dopen(pathpart.c_str(), FS_Read);
	if(!dir) return ret;
	bt_directory_entry entry=bt_dread(dir);
	while(entry.valid){
		if(is_match(filepart, entry.filename)) ret.push_back(pathpart + entry.filename);
		entry=bt_dread(dir);
	}
	bt_dclose(dir);
	return ret;
}

vector<string> glob(const string &str){
	vector<string> ret;
	if(str.front()=='[' && str.back()==']'){
		string cut=str.substr(1, str.length()-2);
		ret=split(cut, ',');
		for(string &s : ret){
			s=parse_path(s);
		}
	}else{
		ret.push_back(str);
	}
	bool again=false;
	do{
		again=false;
		for(auto i=ret.begin(); i!=ret.end(); ++i){
			const string &s=*i;
			if(s.find('*') != string::npos || s.find('?') != string::npos){
				vector<string> matches=find_matches(s);
				ret.erase(i);
				ret.reserve(matches.size());
				ret.insert(ret.end(), matches.begin(), matches.end());
				again=true;
				break;
			}
		}
	}while(again==true);
	return ret;
}
