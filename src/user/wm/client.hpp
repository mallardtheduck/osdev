#ifndef _CLIENT_HPP
#define _CLIENT_HPP

#include <btos_stubs.h>

class Client
{
public:
	Client();
	~Client();
	
	void ProcessMessage(bt_msg_header msg);
};

#endif // _CLIENT_HPP
