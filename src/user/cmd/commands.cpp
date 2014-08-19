#include "cmd.hpp"
#include <fstream>
#include <iostream>

using namespace std;

void print_os_version(){
	display_file("INFO:/VERSION");
}

void display_file(const string &path){
	ifstream file(path);
	if(file.is_open()){
    	string line;
    	while(getline(file, line)) cout << line << endl;
    }
}

void list_files(const string &path){
	bt_dirhandle dir=bt_dopen(path.c_str(), FS_Read);
	if(!dir) return;
	directory_entry entry=bt_dread(dir);
	while(entry.valid){
		cout << entry.filename << '\t' << entry.size << endl;
		entry=bt_dread(dir);
	}
	bt_dclose(dir);
}

void display_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << "Usage:" << endl;
		cout << commandline[0] << " filename" << endl;

	}
	display_file(commandline[1]);
}

void ls_command(vector<string> commandline){
	if(commandline.size() < 2){
		list_files(get_cwd());
	}else{
		list_files(commandline[1]);
	}
}

void cd_command(vector<string> commandline){
	if(commandline.size() < 2){
		cout << get_cwd() << endl;
	}else{
		set_cwd(commandline[1]);
	}
}

bool run_command(vector<string> commandline){
	if(!commandline.size()) return true;
	const string command=commandline[0];
	if(command=="cat"){
		display_command(commandline);
		return true;
	}else if(command=="ls"){
      	ls_command(commandline);
      	return true;
    }else if(command=="cd"){
    	cd_command(commandline);
    	return true;
    }else if(command=="exit"){
		return false;
	}
	cout << "Unknown command." << endl;
	return true;
}