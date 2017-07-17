#ifndef _IMESSAGEHANDELR_HPP
#define _IMESSAGEHANDELR_HPP

#include "bt_msg.h"
#include "message.hpp"

namespace btos_api{

	class IMessageHandler{
	public:
		virtual bool HandleMessage(const Message &msg) = 0;
	};

}

#endif
