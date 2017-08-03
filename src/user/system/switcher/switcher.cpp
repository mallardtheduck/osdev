#include <fstream>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <btos.h>
#include <dev/keyboard.h>
#include <dev/terminal.h>
#include <dev/terminal_ioctl.h>
#include <crt_support.h>
#include <btos/envvars.hpp>
#include <ncurses/cursesp.h>
#include "switcher.hpp"
#include "switcherapp.hpp"

using namespace std;

//extern "C" btos_api::bt_handle btos_get_handle(int fd);

vector<term> get_term_list(){
    vector<term> ret;
    ifstream terms("INFO:/TERMS");
    string s;
	string backend;
	string termid=GetEnv("TERMID");
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

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
	bt_term_SetInfoLine(false);
	//uint64_t keycode = (/*KeyFlags::Control |*/ KeyFlags::NonASCII | KeyCodes::Escape);
	//bt_term_RegisterGlobalShortcut(keycode);

    int res;

    try {
        SwitcherApp app;
        app.handleArgs(argc, argv);
        res = app();
        endwin();
    } catch (const NCursesException *e) {
        endwin();
        std::cerr << e->message << std::endl;
        res = e->errorno;
    } catch (const NCursesException &e) {
        endwin();
        std::cerr << e.message << std::endl;
        res = e.errorno;
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        res = EXIT_FAILURE;
    }
    return res;
}

//int main(){
//    string title="SWITCHER";
//    bt_term_stdout();
//    string termid=GetEnv("TERMID");
//    uint64_t cterm=atoi(termid.c_str());
//	bt_term_SetTitle(title.c_str());
//	uint64_t keycode = (/*KeyFlags::Control |*/ KeyFlags::NonASCII | KeyCodes::Escape);
//	bt_term_RegisterGlobalShortcut(keycode);
//	keycode |= KeyFlags::Right;
//	bt_term_RegisterGlobalShortcut(keycode);
//    while(true) {
//        bt_term_ClearScreen();
//        vector<term> terms = get_term_list();
//        for (const term &t : terms) {
//            if (t.id != cterm) cout << t.id << " : " << t.title << endl;
//        }
//        cout << "n : " << "New terminal." << endl;
//        cout << '?';
//        string input;
//        getline(cin, input);
//        if (input == "n") {
//            string shell = GetEnv("SHELL");
//			bt_term_NewTerminal(shell.c_str());
//        } else {
//            uint64_t new_id = atoi(input.c_str());
//			bt_term_SwitchTerminal(new_id);
//        }
//    }
//}
