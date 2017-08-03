#ifndef _MENU_HPP
#define _MENU_HPP

#include <ncurses/cursesm.h>
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <btos.h>

class MenuItems
{
protected:
    std::vector<NCursesMenuItem *> itemList;

    ~MenuItems()
    {
        typedef std::vector<NCursesMenuItem *>::const_iterator it;
        for (it i = itemList.begin(); i != itemList.end(); ++i) {
            delete *i;
        }
    }
};

class Menu : private MenuItems, public NCursesMenu
{
public:
    explicit Menu(const std::vector<std::string> &in)
        : NCursesMenu(lines(), cols()), accepted(false), items(in)
    {
        set_format(lines() - 1, 1); // Make menu large.
        set_mark("*");              // Use * as a marker.
        options_off(O_ONEVALUE);    // Allow multi-selection.

        // Compose list of menu items.
        itemList.reserve(items.size() + 1U);
        typedef std::vector<std::string>::const_iterator it;
        for (it i = items.begin(); i != items.end(); ++i) {
            itemList.push_back(new NCursesMenuItem(i->c_str()));
        }
        itemList.push_back(new NCursesMenuItem());

        // Initialize NCursesMenu.
        InitMenu(&itemList[0], false, false);
		panel.reset(new NCursesPanel(1, items.size(), lines()-1, 1));
    }

    std::vector<std::string> getSelection()
    {
        std::vector<std::string> selection;

        // Empty selection if choice wasn't confirmed.
        if (!accepted) {
            return selection;
        }

        // Use selected items.
        typedef std::vector<NCursesMenuItem *>::const_iterator it;
        for (it i = itemList.begin(); i != itemList.end(); ++i) {
            if ((*i)->value()) {
                selection.push_back((*i)->name());
            }
        }

        // Or just the current item.
        if (selection.empty()) {
            selection.push_back(current_item()->name());
        }

        return selection;
    }

    virtual int virtualize(int c)
    {
		std::stringstream ss;
		ss << "KEY: " << c << std::endl;
		bt_zero(ss.str().c_str());
        switch (c) {
            // Down.
            case 'j':  return REQ_DOWN_ITEM;
            // Up.
            case 'k':  return REQ_UP_ITEM;
            // Toggle item and don't move cursor.
            case ' ':  return REQ_TOGGLE_ITEM;
            case 't':  return REQ_TOGGLE_ITEM;
            // Toggle item and move cursor down.
            case 'T':  current_item()->set_value(!current_item()->value());
                       return REQ_DOWN_ITEM;

            // Quit accepting the selection.
            case '\n': accepted = true;
                       return MAX_COMMAND + 1;
            // Cancel.
            case 'q':  return MAX_COMMAND + 1;

            // Pass the rest of the keys to predefined handler.
            default: return NCursesMenu::virtualize(c);
        }
    }

//  virtual void On_Menu_Init()
//  {
//    NCursesWindow W(::stdscr);
//   	panel->move(0, 0);
//    panel->clrtoeol();
//    for(int i=1; i<=count(); i++)
//      panel->addch('0' + i);
//    panel->bkgd(W.getbkgd());
//    refresh();
//  }

//  virtual void On_Menu_Termination()
//  {
//    panel->move(0, 0);
//    panel->clrtoeol();
//    refresh();
//  }

//  virtual void On_Item_Init(NCursesMenuItem& item)
//  {
//    panel->move(0, item.index());
//    panel->attron(A_REVERSE);
//    panel->printw("%1d", 1+item.index());
//    panel->attroff(A_REVERSE);
//    refresh();
//  }

//  virtual void On_Item_Termination(NCursesMenuItem& item)
//  {
//    panel->move(0, item.index());
//    panel->attroff(A_REVERSE);
//    panel->printw("%1d", 1+item.index());
//    refresh();
//  }

private:
    bool accepted;
    const std::vector<std::string> items;
	std::unique_ptr<NCursesPanel> panel;
};

#endif
