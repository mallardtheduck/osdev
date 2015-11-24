#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include "window.hpp"

#include <btos_stubs.h>
#include <map>
#include <memory>

class Client{
private:
	std::map<uint64_t, std::shared_ptr<Window>> windows;
	
	std::shared_ptr<Window> currentWindow;
public:
	Client();
	~Client();
	
	void ProcessMessage(const bt_msg_header &msg);
};

#endif // _CLIENT_HPP
