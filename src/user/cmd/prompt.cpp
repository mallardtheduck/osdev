#include "cmd.hpp"
#include <sstream>

using namespace std;

string prompt_string(){
	stringstream ret;
	string prompt=get_prompt();
	for(auto i=prompt.begin(); i!=prompt.end(); ++i){
		if(*i!='$'){
			ret << *i;
		}else{
			i++;
			if(i==prompt.end()) break;
			if(*i=='$') ret << '$';
			if(*i=='p') ret << get_cwd();
		}
	}
	return ret.str();
}