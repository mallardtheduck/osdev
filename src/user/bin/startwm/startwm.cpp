#include <btos.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <crt_support.h>
#include <dev/terminal.h>
#include <dev/terminal_ioctl.h>
#include <btos/table.hpp>

using namespace std;

string GDSPath = ":/btos/system/gds.elx";
string WMPath = ":/btos/system/wm.elx";
string ShellPath = ":/btos/bin/wmmenu.elx";

const string ProcInfoPath = "info:/procs";

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

int main(){
    cout << "Starting GUI..." << endl;
	string systemdrive = get_env("SYSTEMDRIVE");
	GDSPath = systemdrive + GDSPath;
	WMPath = systemdrive + WMPath;
	ShellPath = systemdrive + ShellPath;
	const char *args[2] = {WMPath.c_str(), ShellPath.c_str()};
	bt_pid_t pid = bt_spawn(GDSPath.c_str(), 2, (char**)args);
	bt_wait(pid);
	bt_term_stdout();
	bt_term_HidePointer();
	bt_term_PointerAutoHide(true);
	cout << "Ending remaining GUI processes...";
	cout.flush();
	bool found = true;
	while(found){
		found = false;
		ifstream procinfostream(ProcInfoPath);
		table procs = parsecsv(procinfostream);
		for(auto row: procs.rows){
			if(strtoul(row["parent"].c_str(), NULL, 0) == bt_getpid()){
				bt_kill(strtoul(row["PID"].c_str(), NULL, 0));
				found = true;
			}
		}
	}
	cout << "Done." << endl;
}
