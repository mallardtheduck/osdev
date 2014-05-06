#include "strutil.hpp"

string to_upper(const string &str){
	string ret;
	for(size_t i=0; i<str.size(); ++i){
		if(str[i] >= 'a' && str[i] <= 'z') ret+=str[i]-'a'+'A';
		else ret+=str[i];
	}
}

bool starts_with(const string &str, const string &cmp){
	if(cmp.size() > str.size()) return false;
	for(int i=0; i<cmp.size(); ++i){
		if(str[i]!=cmp[i]) return false;
	}
	return true;
}

vector<string> split_string(const string &str, const char c){
	vector<string> ret;
	string current;
	for(int i=0; i<str.size(); ++i){
		if(str[i]==c && current!=""){
			ret.push_back(current);
			current="";
			
		}else{
			current+=c;
		}
	}
	if(current!="") ret.push_back(current);
	return ret;
}
