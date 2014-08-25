#include "cmd.hpp"
#include <sstream>

using namespace std;

bool is_match(const string &pattern, const string &filename){
	size_t fnpos=0;
	bool matchany=false;
	for(const char &c : pattern){
		if(c=='?'){
			fnpos++;
			if(filename.length() < fnpos) return false;
		}else if(c=='*'){
			matchany=true;
		}else if(c==filename[fnpos]){
			fnpos++;
		}else if(matchany){
			while(c!=filename[fnpos]){
				fnpos++;
				if(fnpos>=filename.length()) return false;
			}
		}else return false;
	}
	return true;
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
		if(entry.type == FS_File && is_match(filepart, entry.filename)) ret.push_back(pathpart + entry.filename);
	}
	bt_dclose(dir);
	return ret;
}

vector<string> resolve_wildcards(const string &str){
	vector<string> ret;
	if(str.front()=='[' && str.back()==']'){
		string cut=str.substr(1, str.length()-2);
		ret=split(cut, ',');
	}else{
		ret.push_back(str);
	}
	bool again=false;
	do{
		for(auto i=ret.begin(); i!=ret.end(); ++i){
			const string &s=*i;
			if(s.find('*') != string::npos || s.find('?') != string::npos){
				ret.erase(i);
				vector<string> matches=find_matches(s);
				ret.reserve(matches.size());
				ret.insert(ret.end(), matches.begin(), matches.end());
				again=true;
				break;
			}
		}
	}while(again==true);
	return ret;
}
