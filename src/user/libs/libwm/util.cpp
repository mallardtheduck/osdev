#include <btos.h>
#include "libwm_internal.hpp"

using namespace std;
using namespace btos_api;

namespace libwm_internal{

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
}
