#include "cmd.hpp"
#include <iostream>

#pragma GCC diagnostic ignored "-Wunused-parameter"

using namespace std;

int main(int argc, char **argv){
	cout << "BT/OS Command prompt" << endl;
	print_os_version();
	get_input();
	display_file("INFO:/ENV");
}