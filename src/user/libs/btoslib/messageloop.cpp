#include <btos/messageloop.hpp>

using namespace std;

namespace btos_api{

	void MessageLoop::AddHandler(shared_ptr<IMessageHandler> h){
		handlers.push_back(h);
	}
	void MessageLoop::RemoveHandler(shared_ptr<IMessageHandler> h){
		for(auto i = handlers.begin(); i != handlers.end(); ++i){
			if(*i = h){
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
		auto msg = Message::Recieve();
		while(true){
			if(!HandleMessage(msg)) return;
			msg.Next();
		}
	}

	bool MessageLoop::HandleMessage(const Message &msg){
		if(msg.IsCritical()){
			if(criticalHandler) criticalHandler(msg);
			else return false;
		}
		if(previewer) previewer(msg);
		for(auto h : handlers){
			if(!h->HandleMessage(msg)) return false;
		}
		return true;
	}
	
}
