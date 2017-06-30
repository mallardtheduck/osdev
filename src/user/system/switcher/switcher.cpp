#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <btos.h>
#include <dev/video_dev.h>
#include <dev/keyboard.h>
#include <dev/terminal.h>
#include <dev/terminal_ioctl.h>
#include <crt_support.h>
#include "switcher.hpp"

using namespace std;

//extern "C" btos_api::bt_handle btos_get_handle(int fd);

struct term{
    uint64_t id;
    string title;
};

vector<term> get_term_list(){
    vector<term> ret;
    ifstream terms("INFO:/TERMS");
    string s;
	string backend;
	string termid=get_env("TERMID");
    uint64_t cterm=atoi(termid.c_str());
	while(getline(terms, s)){
        if(s[0]=='#') continue;
        vector<string> line=split(s, ',');
        if(line.size()>=3) {
			if((uint64_t)atoi(line[0].c_str()) == cterm) backend = line[2];
			break;
        }
    }
    while(getline(terms, s)){
        if(s[0]=='#') continue;
        vector<string> line=split(s, ',');
        if(line.size()>=3 && line[2] == backend) {
            term t;
            t.id = atoi(line[0].c_str());
            t.title=line[1];
            ret.push_back(t);
        }
    }
    return ret;
}

int main(){
    string title="SWITCHER";
    bt_term_stdout();
    string termid=get_env("TERMID");
    uint64_t cterm=atoi(termid.c_str());
	bt_term_SetTitle(title.c_str());
	uint64_t keycode = (/*KeyFlags::Control |*/ KeyFlags::NonASCII | KeyCodes::Escape);
	bt_term_RegisterGlobalShortcut(keycode);
	keycode |= KeyFlags::Right;
	bt_term_RegisterGlobalShortcut(keycode);
    while(true) {
        bt_term_ClearScreen();
        vector<term> terms = get_term_list();
        for (const term &t : terms) {
            if (t.id != cterm) cout << t.id << " : " << t.title << endl;
        }
        cout << "n : " << "New terminal." << endl;
        cout << '?';
        string input;
        getline(cin, input);
        if (input == "n") {
            string shell = get_env("SHELL");
			bt_term_NewTerminal(shell.c_str());
        } else {
            uint64_t new_id = atoi(input.c_str());
			bt_term_SwitchTerminal(new_id);
        }
    }
}
