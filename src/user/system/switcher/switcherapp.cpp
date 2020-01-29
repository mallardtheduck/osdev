#define BTOS_NO_USING

#include "switcherapp.hpp"
#include "switcher.hpp"
#include <vector>
#include <sstream>

#include <dev/terminal_ioctl.h>
#include <dev/keyboard.h>
#include <btos/envvars.hpp>
#include <btos/directory.hpp>
#include <btos/ini.hpp>
#include <btos/registry.hpp>
#include <sm/sessions.hpp>

using namespace std;
namespace reg = btos_api::registry;
namespace sm = btos_api::sm;

static const string SessionManager = btos_api::EnvInterpolate("$systemdrive$:/BTOS/SYSTEM/SESSION.ELX");

void NewSession();

SwitcherApp::SwitcherApp() : NCursesApplication(true){
}

int SwitcherApp::run(){
	btos_api::bt_term_SetTitle("SWITCHER");
	uint64_t keycode = (/*KeyFlags::Control |*/ KeyFlags::NonASCII | KeyCodes::Escape);
	btos_api::bt_term_RegisterGlobalShortcut(keycode);
	Root_Window->setpalette(COLOR_WHITE, COLOR_BLACK);
	init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    init_pair(3, COLOR_BLUE, COLOR_WHITE);

	while(true){
		vector<pair<string, size_t>> items;
		auto terms = get_term_list();
		for(auto t : terms){
			stringstream titlestr;
			titlestr << "[" << t.id << "] " << t.title;
			items.push_back({titlestr.str(), t.id});
		}
		items.push_back({"New session...", 0});
		Menu m = make_menu("Switcher", items);
		m();

		auto id = m.getSelection();
		if(id){
			btos_api::bt_term_SwitchTerminal(id);
			btos_api::bt_term_WaitActive();
		}else{
			NewSession();
		}
	}

	return 0;
}

int SwitcherApp::titlesize() const{
	return 0;
}

void SwitcherApp::title(){
}


void NewSession(){
	auto entries = sm::GetSessionTypes();
	vector<pair<string, size_t>> items;
	for(size_t i = 0; i < entries.size(); ++i){
		items.push_back({entries[i].GetName(), i});
	}

	items.push_back({"Cancel", 0xFFFFFFFF});
	Menu m = make_menu("New", items);
	m();

	auto idx = m.getSelection();
	if(idx != 0xFFFFFFFF){
		auto &entry = entries[idx];
		string cmd = SessionManager + " " + entry.GetID();
		btos_api::bt_term_NewTerminal(cmd.c_str());
	}
	btos_api::bt_term_WaitActive();
}


