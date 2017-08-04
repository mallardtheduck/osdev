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
#include <btos/table.hpp>
#include <ncurses/cursesp.h>
#include "switcher.hpp"
#include "switcherapp.hpp"

using namespace std;

vector<term> get_term_list(){
    vector<term> ret;
    ifstream terms("INFO:/TERMS");
	auto tbl = parsecsv(terms);
    string s;
	string backend;
	string termid=GetEnv("TERMID");
    uint64_t cterm=atoi(termid.c_str());
	for(auto r : tbl.rows){
		if((uint64_t)atoi(r["ID"].c_str()) == cterm) backend = r["backend"];
		break;
    }
    for(auto r : tbl.rows){
        if(r["backend"] == backend && (uint64_t)atoi(r["ID"].c_str()) != cterm) {
            term t;
            t.id = atoi(r["ID"].c_str());
            t.title=r["title"];
            ret.push_back(t);
        }
    }
    return ret;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
	bt_term_SetInfoLine(false);

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

