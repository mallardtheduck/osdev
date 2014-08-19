#include "cmd.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void print_os_version(){
	display_file("INFO:/VERSION");
}

void display_file(const string &path){
	ifstream file(path);
    string line;
    while(getline(file, line)) cout << line << endl;
}