#include <btos.h>
#include <sstream>
#include "switcher.hpp"

using namespace std;

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