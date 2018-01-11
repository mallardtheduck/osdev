#ifndef _MENU_HPP
#define _MENU_HPP

#include <ncurses/cursesm.h>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <btos.h>

class MenuItems{
protected:
    std::vector<NCursesMenuItem *> itemList;

    ~MenuItems();
};

class Menu : private MenuItems, public NCursesMenu{
private:
    const std::vector<std::pair<std::string, size_t>> items;
    Menu(int y, int x, int h, int w, const std::string &title, const std::vector<std::pair<std::string, size_t>> &in);
    
    friend Menu make_menu(const std::string &title, const std::vector<std::pair<std::string, size_t>> &in);
public:
    size_t getSelection();

    int virtualize(int c) override;
    void On_Menu_Init() override;
};

Menu make_menu(const std::string &title, const std::vector<std::pair<std::string, size_t>> &in);

#endif
