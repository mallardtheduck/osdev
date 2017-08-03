#include "switcherapp.hpp"
#include "switcher.hpp"
#include <sstream>

using namespace std;

SwitcherApp::SwitcherApp() : NCursesApplication(true)
{}

int SwitcherApp::run(){
	Root_Window->erase();
	Root_Window->noutrefresh();
	vector<string> items;
	auto terms = get_term_list();
	for(auto t : terms){
		items.push_back(t.title);
	}
	for(size_t i = 0; i < 10; ++i){
		stringstream ss;
		ss << i;
		items.push_back(ss.str());
	}
	items.push_back("New session...");
	Menu m(items);
	m();

	return 0;
}

int SwitcherApp::titlesize() const{
	return 1;
}

void SwitcherApp::title(){
	titleWindow->bkgd(screen_titles());
	titleWindow->erase();
	titleWindow->addstr(0, 0, "space:Toggle  enter:Accept  q:Cancel");
	titleWindow->noutrefresh();
}


