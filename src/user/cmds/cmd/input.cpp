#include "cmd.hpp"
#include <sstream>
#include <fstream>
#include <unistd.h>

using namespace std;

extern "C" bt_handle btos_get_handle(int fd);

string input_line(){
    string ret;
    getline(cin, ret);
    return ret;
}

string get_input(){
    bool input_tty=(bool)isatty(fileno(stdin));
   	if(input_tty) cout << get_prompt();
	return input_line();
}
