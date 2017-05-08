#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include "window.hpp"
#include "menus.hpp"

#include <btos.h>
#include <map>
#include <memory>
#include <deque>
#include <wm/wm.h>

class Window;
class Menu;

class Client: public std::enable_shared_from_this<Client>{
private:
	bool msgPending = false;
	bt_pid_t pid;
	std::map<uint64_t, std::shared_ptr<Window>> windows;
	std::map<uint64_t, std::shared_ptr<Menu>> menus;
	std::deque<wm_Event> eventQ;
	
	std::shared_ptr<Window> currentWindow;
	std::shared_ptr<Menu> currentMenu;
public:
	Client(bt_pid_t pid);
	~Client();
	
	void ProcessMessage(const bt_msg_header &msg);
	void SendEvent(const wm_Event &e);
	void SendNextEvent();
};

#endif // _CLIENT_HPP
