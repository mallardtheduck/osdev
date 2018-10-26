#include "cmd.hpp"
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <limits>

using namespace std;

extern "C" bt_handle btos_get_handle(int fd);

string input_line(){
    string ret;
    if(!cin.good()){
    	cin.seekg(0);
    	cin.clear();
    }
    getline(cin, ret);
    if(!cin){
    	cout << "Input failed! " << cin.rdstate() << endl; 
    }
    return ret;
}

string get_input(){
    bool input_tty=(bool)isatty(fileno(stdin));
   	if(input_tty) cout << get_prompt();
	return input_line();
}
