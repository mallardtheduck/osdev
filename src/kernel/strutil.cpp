#include "strutil.hpp"

string to_upper(const string &str){
	size_t buflen=str.length()+1;
	char *buf=(char*)malloc(buflen);
	memset(buf, 0, buflen);
	strncpy(buf, str.c_str(), buflen);
	for(size_t i=0; i<buflen; ++i){
		if(buf[i] >= 'a' && buf[i] <= 'z') buf[i]=buf[i]-'a'+'A';
	}
	string ret(buf);
	free(buf);
	return ret;
}

bool starts_with(const string &str, const string &cmp){
	if(cmp.size() > str.size()) return false;
	for(size_t i=0; i<cmp.size(); ++i){
		if(str[i]!=cmp[i]) return false;
	}
	return true;
}

vector<string> split_string(const string &str, const char c){
	vector<string> ret;
	string current;
	for(size_t i=0; i<str.size(); ++i){
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
