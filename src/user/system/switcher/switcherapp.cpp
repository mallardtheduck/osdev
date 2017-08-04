#include "switcherapp.hpp"
#include "switcher.hpp"
#include <vector>

#include <dev/terminal_ioctl.h>
#include <dev/keyboard.h>
#include <btos/envvars.hpp>
#include <btos/directory.hpp>
#include <btos/ini.hpp>

using namespace std;

static const string SessionsPath = EnvInterpolate("$systemdrive$:/BTOS/CONFIG/SESSIONS/");
static const string SessionManager = EnvInterpolate("$systemdrive$:/BTOS/SYSTEM/SESSION.ELX");

void NewSession();

SwitcherApp::SwitcherApp() : NCursesApplication(false)
{}

int SwitcherApp::run(){
	bt_term_SetTitle("SWITCHER");
	uint64_t keycode = (/*KeyFlags::Control |*/ KeyFlags::NonASCII | KeyCodes::Escape);
	bt_term_RegisterGlobalShortcut(keycode);

	while(true){
		vector<pair<string, size_t>> items;
		auto terms = get_term_list();
		for(auto t : terms){
			items.push_back({t.title, t.id});
		}
		items.push_back({"New session...", 0});
		Menu m(items);
		m();

		auto id = m.getSelection();
		if(id){
			bt_term_SwitchTerminal(id);
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
	Directory d {SessionsPath.c_str(), FS_Read};
	for(auto f : d){
		string fname = f.filename;
		if(f.type == FS_File && hasEnding(to_lower(fname), ".ini")){
			auto ini = ReadIniFile(SessionsPath + fname);
			SessionEntry e;
			e.id = fname.substr(0, fname.length() - 4);
			auto section = ini["session"];
			e.name = section["name"];
			ret.push_back(e);
		}
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
	Menu m(items);
	m();

	auto idx = m.getSelection();
	if(idx != 0xFFFFFFFF){
		auto entry = entries[idx];
		string cmd = SessionManager + " " + entry.id;
		bt_term_NewTerminal(cmd.c_str());
	}
}


