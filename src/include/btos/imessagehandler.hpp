#ifndef _IMESSAGEHANDELR_HPP
#define _IMESSAGEHANDELR_HPP

#include "bt_msg.h"
#include "message.hpp"
#include <functional>

namespace btos_api{

	class IMessageHandler{
	public:
		virtual bool HandleMessage(const Message &msg) = 0;

		virtual ~IMessageHandler() {}
	};

	class CustomHandler : public IMessageHandler{
	private:
		std::function<bool(const Message &msg)> handler;
	public:
		CustomHandler(std::function<bool(const Message &msg)> fn) : handler(fn) {}
		bool HandleMessage(const Message &msg) override { return handler(msg); } 
	};

}

#endif
