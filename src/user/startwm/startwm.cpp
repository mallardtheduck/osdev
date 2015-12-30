#include <btos.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <crt_support.h>
#include <dev/terminal.h>
#include "table.hpp"

using namespace std;

const string GDSPath = "hdd:/btos/system/gds.elx";
const string WMPath = "hdd:/btos/system/wm.elx";
const string ShellPath = "hdd:/btos/bin/wmmenu.elx";

const string ProcInfoPath = "info:/procs";

int main(){
    cout << "Starting GUI..." << endl;
	const char *args[2] = {WMPath.c_str(), ShellPath.c_str()};
	bt_pid_t pid = bt_spawn(GDSPath.c_str(), 2, (char**)args);
	bt_wait(pid);
	bt_fioctl(btos_get_handle(fileno(stdout)), bt_terminal_ioctl::HidePointer, 0, NULL);
	bool ph = true;
	bt_fioctl(btos_get_handle(fileno(stdout)), bt_terminal_ioctl::PointerAutoHide, sizeof(ph), (char*)ph);
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