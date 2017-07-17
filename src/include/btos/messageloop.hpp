#ifndef _MESSAGELOOP_HPP
#define _MESSAGELOPP_HPP

#include <btos.h>
#include "imessagehandler.hpp"
#include "message.hpp"
#include <vector>
#include <memory>
#include <functional>

namespace btos_api{
	
	class MessageLoop : public IMessageHandler{
	private:
		std::vector<std::shared_ptr<IMessageHandler>> handlers;
		std::function<bool(Message&)> criticalHandler;
		std::function<bool(Message&)> previewer;
	public:
		void AddHandler(std::shared_ptr<IMessageHandler> h);
		void RemoveHandler(std::shared_ptr<IMessageHandler> h);

		void SetCriticalHandler(std::function<bool(Message&)> fn);
		std::function<bool(Message&)> GetCriticalHandler();

		void SetPreviewer(std::function<bool(Message&)> fn);
		std::function<bool(Message&)> GetPreviewer();

		void RunLoop();
		bool HandleMessage(const Message &msg) override;
	};
	
}

#endif
