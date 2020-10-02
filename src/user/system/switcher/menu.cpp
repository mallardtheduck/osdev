#pragma GCC diagnostic ignored "-Wdeprecated"

#include "menu.hpp"

using namespace std;

class IdentifiedMenuItem : public NCursesMenuItem{
private:
	size_t id;
public:
	void SetID(size_t i){ id = i; }
	size_t GetID(){ return id; }

	IdentifiedMenuItem(const char *name, size_t i) : NCursesMenuItem(name), id(i) {}
};

MenuItems::~MenuItems(){
    for(auto i : itemList) {
        delete i;
    }
}

Menu make_menu(const string &title, const vector<pair<string, size_t>> &in){
	int h = in.size() + 2;
	int w = [&]()->int{
		int ret = title.length();
		for(auto &i : in){
			if((int)i.first.length() > ret) ret = i.first.length();
		}
		return ret + 3;
	}();
	int y = (LINES - h) / 2;
	int x = (COLS - w) / 2;
	
	return Menu(y, x, h, w, title, in);
}

Menu::Menu(int y, int x, int h, int w, const string &title, const vector<pair<string, size_t>> &in) : NCursesMenu(h, w, y, x), items(in){
    set_format(lines() - 1, 1); // Make menu large.

    // Compose list of menu items.
    itemList.reserve(items.size() + 1U);
    for(auto &i : items) {
        itemList.push_back(new IdentifiedMenuItem(i.first.c_str(), i.second));
    }
    itemList.push_back(new NCursesMenuItem());

    // Initialize NCursesMenu.
    InitMenu(&itemList[0], true, false);
    attron(COLOR_PAIR(3));
    frame(title.c_str());
    attroff(COLOR_PAIR(3));
}

size_t Menu::getSelection(){
	size_t selection = 0;
	
	auto cur = current_item();
	auto idcur = dynamic_cast<IdentifiedMenuItem*>(cur);
	if(idcur){
		selection = idcur->GetID();
	}

	return selection;
}

int Menu::virtualize(int c){
    switch (c) {
        // Down.
        case 'j':  return REQ_DOWN_ITEM;
        // Up.
        case 'k':  return REQ_UP_ITEM;

        // Quit accepting the selection.
        case '\n':
                   return MAX_COMMAND + 1;
        // Cancel.
        case 'q':  return MAX_COMMAND + 1;

        // Pass the rest of the keys to predefined handler.
        default: return NCursesMenu::virtualize(c);
    }
}

void Menu::On_Menu_Init(){
}
