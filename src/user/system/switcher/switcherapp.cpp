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

using namespace std;
namespace reg = btos_api::registry;

static const string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/");
static const string SessionManager = EnvInterpolate("$systemdrive$:/BTOS/SYSTEM/SESSION.ELX");

void NewSession();

SwitcherApp::SwitcherApp() : NCursesApplication(true){
}

int SwitcherApp::run(){
	bt_term_SetTitle("SWITCHER");
	uint64_t keycode = (/*KeyFlags::Control |*/ KeyFlags::NonASCII | KeyCodes::Escape);
	bt_term_RegisterGlobalShortcut(keycode);
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
			bt_term_SwitchTerminal(id);
			bt_term_WaitActive();
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

struct SessionEntry{
	string id;
	string name;
};

static string to_lower(string str){
	for(size_t i = 0; i < str.length(); ++i){
		if(str[i] >= 'A' && str[i] <= 'Z') str[i] = (str[i] - 'A') + 'a';
	}
	return str;
}

static bool hasEnding (const string &fullString, const string &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

static vector<SessionEntry> GetSessionEntries(){
	vector<SessionEntry> ret;
	auto addSession = [&](const string &fname, const string &id){
		auto info = bt_stat(fname.c_str());
		if(info.type == FS_File){
			auto ini = ReadIniFile(fname);
			SessionEntry e;
			e.id = id;
			auto section = ini["session"];
			e.name = section["name"];
			ret.push_back(e);
		}
	};
	Directory d {SessionsPath.c_str(), FS_Read};
	for(auto f : d){
		string fname = f.filename;
		if(f.type == FS_File && hasEnding(to_lower(fname), ".ini")){
			addSession(SessionsPath + fname, fname.substr(0, fname.length() - 4));
		}
	}
	auto feats = reg::GetFeaturesByType("sm.ses");
	for(auto &f : feats){
		auto feat = reg::GetFeatureByName(f);
		auto fname = reg::GetFeaturePath(feat.id);
		addSession(fname, f);
	}
	return ret;
}

void NewSession(){
	auto entries = GetSessionEntries();
	vector<pair<string, size_t>> items;
	for(size_t i = 0; i < entries.size(); ++i){
		items.push_back({entries[i].name, i});
	}

	items.push_back({"Cancel", 0xFFFFFFFF});
	Menu m = make_menu("New", items);
	m();

	auto idx = m.getSelection();
	if(idx != 0xFFFFFFFF){
		auto entry = entries[idx];
		string cmd = SessionManager + " " + entry.id;
		bt_term_NewTerminal(cmd.c_str());
	}
	bt_term_WaitActive();
}


