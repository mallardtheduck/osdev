#include "gds.hpp"
#include "screen.hpp"
#include "drawingop.hpp"
#include "fonts.hpp"
#include <iostream>

using namespace std;

char dbgbuf[128];

void set_env(const string &name, const string &value) {
	bt_setenv(name.c_str(), value.c_str(), 0);
}

int main(int argc, char **argv) {
	cout << "BT/OS GDS" << endl;
	GetFontManager();
	bt_pid_t root_pid = 0;
	if(argc > 1) {
		int s_argc = 0;
		char **s_argv = NULL;
		if(argc > 2) {
			s_argc = argc - 2;
			s_argv = &argv[2];
		}
		char elxpath[BT_MAX_PATH];
		btos_path_parse(argv[1], elxpath, BT_MAX_PATH);
		root_pid = bt_spawn(elxpath, s_argc, s_argv);
		if(!root_pid) {
			cout << "Could not load " << argv[1] << endl;
		}
	}
	try {
		Service(root_pid);
	} catch(exception &e) {
		cout << "Exception:" << e.what() << endl;
	}
	GetScreen()->RestoreMode();
	return 0;
}
