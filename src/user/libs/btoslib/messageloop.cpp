#include <btos/messageloop.hpp>

using namespace std;

namespace btos_api{

	void MessageLoop::AddHandler(shared_ptr<IMessageHandler> h){
		handlers.push_back(h);
	}
	void MessageLoop::RemoveHandler(shared_ptr<IMessageHandler> h){
		for(auto i = handlers.begin(); i != handlers.end(); ++i){
			if(*i == h){
				handlers.erase(i);
				return;
			}
		}
	}

	void MessageLoop::SetCriticalHandler(function<bool(const Message&)> fn){
		criticalHandler = fn;
	}
	function<bool(const Message&)> MessageLoop::GetCriticalHandler(){
		return criticalHandler;
	}

	void MessageLoop::SetPreviewer(function<bool(const Message&)> fn){
		previewer = fn;
	}
	function<bool(const Message&)> MessageLoop::GetPreviewer(){
		return previewer;
	}

	void MessageLoop::RunLoop(){
		bt_msg_filter filter;
		filter.flags = bt_msg_filter_flags::NonReply;
		auto msg = Message::RecieveFiltered(filter);
		while(!terminate && HandleMessage(msg) && !terminate) msg.Next();
	}

	bool MessageLoop::HandleMessage(const Message &msg){
		current.reset(new Message(msg));
		if(msg.IsCritical()){
			if(!criticalHandler || !criticalHandler(msg)) return false;
		}
		if(previewer && !previewer(msg)) return false;
		for(auto h : handlers){
			if(!h->HandleMessage(msg)) return false;
		}
		return true;
	}
	
	const Message &MessageLoop::GetCurrent() const{
		return *current;
	}

	void MessageLoop::Terminate(){
		terminate = true;
		bt_msg_header msg;
		msg.flags = 0;
		msg.to = bt_getpid();
		msg.type = -1;
		msg.length = 0;
		msg.content = nullptr;
		msg.id = bt_send(msg);
	}
}
