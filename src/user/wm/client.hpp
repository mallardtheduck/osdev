#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include "window.hpp"

#include <btos_stubs.h>
#include <map>
#include <memory>
#include <deque>
#include <wm/wm.h>

class Window;

class Client: public std::enable_shared_from_this<Client>{
private:
	bool msgPending = false;
	bt_pid_t pid;
	std::map<uint64_t, std::shared_ptr<Window>> windows;
	std::deque<wm_Event> eventQ;
	
	std::shared_ptr<Window> currentWindow;
public:
	Client(bt_pid_t pid);
	~Client();
	
	void ProcessMessage(const bt_msg_header &msg);
	void SendEvent(const wm_Event &e);
	void SendNextEvent();
};

#endif // _CLIENT_HPP
