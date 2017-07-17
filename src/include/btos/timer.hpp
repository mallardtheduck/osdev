#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <functional>
#include "handle.hpp"
#include "imessagehandler.hpp"

namespace btos_api{

	class Timer : public Handle, public IMessageHandler{
	private:
		std::function<bool(Timer&)> handler;
	public:
		Timer(uint32_t msec);
		
		void Reset();

		void SetHandler(std::function<bool(Timer&)> fn);
		std::function<bool(Timer&)> GetHandler();

		bool HandleMessage(const Message &msg) override;
	};

}

#endif
