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
public:
    explicit Menu(const std::vector<std::pair<std::string, size_t>> &in);

    size_t getSelection();

    int virtualize(int c) override;
};

#endif
