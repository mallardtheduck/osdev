#include "switcher.hpp"
#include "../../include/btos_api.h"
#include "../../include/terminal.h"
#include "../../include/btos_stubs.h"
#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <video_dev.h>

using namespace std;

extern "C" btos_api::bt_handle btos_get_handle(int fd);

struct term{
    uint64_t id;
    string title;
};

vector<term> get_term_list(){
    vector<term> ret;
    ifstream terms("INFO:/TERMS");
    string s;
    while(getline(terms, s)){
        if(s[0]=='#') continue;
        vector<string> line=split(s, ',');
        if(line.size()>=2) {
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
    btos_api::bt_filehandle fh=btos_get_handle(fileno(stdout));
    string termid=get_env("TERMID");
    uint64_t cterm=atoi(termid.c_str());
    bt_fioctl(fh, bt_terminal_ioctl::SetTitle , title.length(), (char*)title.c_str());
    while(true) {
        bt_fioctl(fh, bt_terminal_ioctl::ClearScreen, 0, NULL);
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
            bt_fioctl(fh, bt_terminal_ioctl::NewTerminal, shell.length(), (char *) shell.c_str());
        } else {
            uint64_t new_id = atoi(input.c_str());
            bt_fioctl(fh, bt_terminal_ioctl::SwtichTerminal, sizeof(new_id), (char *) &new_id);
        }
    }
}