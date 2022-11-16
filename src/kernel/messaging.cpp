#include "kernel.hpp"
#include "utils/ministl.hpp"
#include "locks.hpp"

namespace bt_msg_flags = btos_api::bt_msg_flags;
namespace bt_msg_filter_flags = btos_api::bt_msg_filter_flags;
namespace thread_msg_status = btos_api::thread_msg_status;
namespace bt_kernel_messages = btos_api::bt_kernel_messages;

using bt_msg_header = btos_api::bt_msg_header;
using bt_msg_filter = btos_api::bt_msg_filter;

struct MessageContent : private nonmovable{
private:
	size_t refcount = 0;
	vector<char> content;
public:

	MessageContent() = default;
	MessageContent(const btos_api::bt_msg_header &header){
		if(header.length){
			content.resize(header.length);
			memcpy(&content[0], header.content, header.length);
		}
	}

	void IncrementRefCount(){
		++refcount;
	}

	void DecrementRefCount(){
		if(--refcount == 0) delete this;
	}

	char *GetPtr(){
		return &content[0];
	}

	vector<char> &GetVector(){
		return content;
	}

	size_t GetSize(){
		return content.size();
	}
};

struct Message{
	bt_msg_header header;
	RefCountPointer<MessageContent> content;

	Message() = default;
	Message(const btos_api::bt_msg_header &h) : header(h), content(new MessageContent(h)){
		if(header.length) header.content = content->GetPtr();
		else header.content = nullptr;
	}
};

class MessageManager : public IMessageManager{
private:
	friend class MessageRecieveHandle;

	vector<Message> messages;
	ILock *messageLock = NewLock();
	
	uint64_t idCounter = 0;

	vector<pair<bt_pid_t, bt_kernel_messages::Enum>> subscribers;

	uint64_t NextID(){
		auto hl = messageLock->LockRecursive();
		return ++idCounter;
	}

	bool GetMessage(uint64_t id, Message &msg){
		auto hl = messageLock->LockRecursive();
		for(auto &m : messages){
			if(m.header.id == id){
				msg = m;
				return true;
			}
		}
		return false;
	}

	bool HaveMessage(uint64_t id){
		auto hl = messageLock->LockRecursive();
		for(auto &m : messages){
			if(m.header.id == id) return true;
		}
		return false;
	}

	void AddMessage(const Message &msg){
		bool added = false;
		while(!added){
			bool wait = false;
			{
				auto hl = messageLock->LockRecursive();
				if(msg.header.from != 0 && !(msg.header.flags & bt_msg_flags::Reply)){
					for(auto &m : messages){
						if(!(m.header.flags &bt_msg_flags::Reply) && m.header.from == msg.header.from && m.header.to == msg.header.to){
							wait = true;
							break;
						}
					}
				}
				if(!wait){
					if(GetProcessManager().GetProcessStatusByID(msg.header.to) != btos_api::bt_proc_status::DoesNotExist){
						messages.push_back(msg);
					}
					added = true;
				}
			}
			if(wait) CurrentThread().SetBlock([&]{
				if(!messageLock->TryTakeExclusive()) return false;
				bool ret = true;
				for(auto &m : messages){
					if(!(m.header.flags &bt_msg_flags::Reply) &&m.header.from == msg.header.from && m.header.to == msg.header.to){
						ret = false;
						break;
					}
				}
				messageLock->Release();
				return ret;
			});
		}
	}

	void RemoveMessage(uint64_t id){
		auto hl = messageLock->LockRecursive();
		size_t index = SIZE_MAX;
		for(size_t i = 0; i < messages.size(); ++i){
			if(messages[i].header.id == id){
				index = i;
				break;
			}
		}
		if(index != SIZE_MAX) messages.erase(index);
	}

	void SendMessageReciept(const bt_msg_header &header){
		auto hl = messageLock->LockRecursive();
		for(auto &sub : subscribers){
			if(sub.first == header.from && sub.second == bt_kernel_messages::MessageReceipt){
				bt_msg_header msg;
				msg.type = bt_kernel_messages::MessageReceipt;
				msg.to = sub.first;
				msg.content = (void*)&header;
				msg.source = 0;
				msg.from = 0;
				msg.flags = 0;
				msg.critical = false;
				msg.length = sizeof(bt_msg_header);
				((bt_msg_header*)msg.content)->length = 0;
				((bt_msg_header*)msg.content)->content = nullptr;
				//dbgpf("MSG: Sending reciept for %i sent to %i.\n", (int)((bt_msg_header*)msg.content)->id, (int)((bt_msg_header*)msg.content)->to);
				SendMessage(msg);
			}
		}
	}
public:

	uint64_t SendMessage(bt_msg_header &msgHeader) override{
		msgHeader.valid = true;
		msgHeader.recieved = false;
		msgHeader.replied = false;

		Message msg = msgHeader;
		if(msg.header.to != 0 && GetProcessManager().GetProcessStatusByID(msg.header.to) == btos_api::bt_proc_status::DoesNotExist){
			dbgpf("MSG: Attempted to send message to non-existent process!\n");
			return 0;
		}
		if(msg.header.flags & bt_msg_flags::Reply){
			Message prev;
			if(!GetMessage(msg.header.reply_id, prev)) {
				dbgout("MSG: Attempted reply to non-existent message!\n");
				return 0;
			}
			if(prev.header.to != msg.header.from || prev.header.from != msg.header.to) {
				dbgout("MSG: Reply to/from mismatch!\n");
				dbgpf("Expected from: %i to: %i, got from: %i to: %i\n", (int)prev.header.to, (int)prev.header.from, (int)msg.header.from, (int)msg.header.to);
				return 0;
			}
			if(prev.header.replied)	return 0;
			{
				auto hl = messageLock->LockRecursive();
				Message omsg;
				if (GetMessage(msg.header.from, omsg)) omsg.header.replied = true;
			}
		}

		msg.header.id = NextID();
		msgHeader.id = msg.header.id;
		AddMessage(msg);
		//dbgpf("MSG: Sent message ID %i from PID %i to PID %i.\n", (int)msg.id, (int)msg.from, (int)msg.to);
		//sch_yield_to(msg.to);
		CurrentThread().Yield();
		//dbgpf("MSG: Message %llu sent by PID %llu.\n", msg.header.id, CurrentProcess().ID());
		return msg.header.id;
	}

	bool RecieveMessage(bt_msg_header &msg, IProcess &proc = CurrentProcess()) override{
		auto hl = messageLock->LockRecursive();
		auto cid = proc.GetCurrentMessageID();
		Message cmsg;
		if(GetMessage(cid, cmsg)){
			msg = cmsg.header;
			CurrentThread().SetMessagingStatus(thread_msg_status::Processing);
			//dbgpf("MSG: Message %llu recieved by PID %llu.\n", msg.id, CurrentProcess().ID());
			return true;
		}
		for(auto &m : messages){
			if(m.header.to == proc.ID()){
				proc.SetCurrentMessageID(m.header.id);
				msg = m.header;
				CurrentThread().SetMessagingStatus(thread_msg_status::Processing);
				//dbgpf("MSG: Message %llu recieved by PID %llu.\n", msg.id, CurrentProcess().ID());
				return true;
			}
		}
		return false;
	}

	bool RecieveMessage(bt_msg_header &msg, const bt_msg_filter &filter, IProcess &proc = CurrentProcess()) override{
		auto hl = messageLock->LockRecursive();
		auto cid = proc.GetCurrentMessageID();
		Message cmsg;
		if(GetMessage(cid, cmsg) && DoesMessageMatch(cmsg.header, filter)){
			msg = cmsg.header;
			CurrentThread().SetMessagingStatus(thread_msg_status::Processing);
			//dbgpf("MSG: Message %llu recieved by PID %llu.\n", msg.id, CurrentProcess().ID());
			return true;
		}
		for(auto &m : messages){
			if(m.header.to == proc.ID() && DoesMessageMatch(m.header, filter)){
				proc.SetCurrentMessageID(m.header.id);
				msg = m.header;
				CurrentThread().SetMessagingStatus(thread_msg_status::Processing);
				//dbgpf("MSG: Message %llu recieved by PID %llu.\n", msg.id, CurrentProcess().ID());
				return true;
			}
		}
		return false;
	}

	bt_msg_header AwaitMessage(IProcess &proc = CurrentProcess()) override{
		bt_msg_header ret;
		auto &currentThread = CurrentThread();
		while(!RecieveMessage(ret, proc)){
			currentThread.SetMessagingStatus(thread_msg_status::Waiting);
			auto unBlocked = currentThread.SetAbortableBlock([&]{
				if(!messageLock->TryTakeExclusive()) return false;
				auto ret = false;
				for(auto &m : messages){
					if(m.header.to == proc.ID()){
						ret = true;
						break;
					}
				}
				messageLock->Release();
				return ret;
			});
			if(!unBlocked) return {};
		}
		//dbgpf("MSG: Message %llu recieved by PID %llu.\n", ret.id, CurrentProcess().ID());
		return ret;
	}

	bt_msg_header AwaitMessage(const bt_msg_filter &filter, IProcess &proc = CurrentProcess()) override{
		auto cid = proc.GetCurrentMessageID();
		Message cmsg;
		if(GetMessage(cid, cmsg) && DoesMessageMatch(cmsg.header, filter)){
			//dbgpf("MSG: Message %llu recieved by PID %llu.\n", cmsg.header.id, CurrentProcess().ID());
			return cmsg.header;
		}
		while(true){
			{
				auto hl = messageLock->LockRecursive();
				for(auto &m : messages){
					if(m.header.to == proc.ID() && DoesMessageMatch(m.header, filter)){
						CurrentThread().SetMessagingStatus(thread_msg_status::Processing);
						//dbgpf("MSG: Message %llu recieved by PID %llu.\n", m.header.id, CurrentProcess().ID());
						return m.header;
					}
				}
			}
			auto &currentThread = CurrentThread();
			currentThread.SetMessagingStatus(thread_msg_status::Waiting);
			auto filterCopy = filter;
			auto unBlocked = currentThread.SetAbortableBlock([&]{
				if(!messageLock->TryTakeExclusive()) return false;
				auto ret = false;
				for(auto &m : messages){
					if(m.header.to == proc.ID() && DoesMessageMatch(m.header, filterCopy)){
						ret = true;
						break;
					}
				}
				messageLock->Release();
				return ret;
			});
			if(!unBlocked) return {};
		}
	}
	
	vector<char> MessageContent(bt_msg_header &msg) override{
		Message message;
		if(GetMessage(msg.id, message)){
			return message.content->GetVector();
		}
		return {};
	}

	void AcknowledgeMessage(bt_msg_header &msg, bool setStatus = true, IProcess &proc = CurrentProcess()) override{
		{
			auto hl = messageLock->LockRecursive();
			if(!HaveMessage(msg.id)) return;
			if(proc.GetCurrentMessageID() == msg.id) proc.SetCurrentMessageID(0);
			RemoveMessage(msg.id);
			if(setStatus) CurrentThread().SetMessagingStatus(thread_msg_status::Normal);
		}
		SendMessageReciept(msg);
	}

	void AwaitNextMessage(bt_msg_header &msg) override{
		AcknowledgeMessage(msg, false);
		msg = AwaitMessage();
	}

	void AwaitNextMessage(const bt_msg_filter &filter, bt_msg_header &msg) override{
		AcknowledgeMessage(msg, false);
		msg = AwaitMessage(filter);
	}

	void ClearMessages(IProcess &proc = CurrentProcess()) override{
		auto pid = proc.ID();
		auto hl = messageLock->LockRecursive();
		bool found = false;
		do{
			for(size_t i = 0; i < messages.size(); ++i){
				auto msg = messages[i].header;
				if(msg.to == pid || msg.from == pid){
					messages.erase(i);
					if(msg.to == pid) SendMessageReciept(msg);
					found = true;
					break;
				}
			}
			found = false;
		}while(found);
		do{
			for(size_t i = 0; i < subscribers.size(); ++i){
				if(subscribers[i].first == pid){
					subscribers.erase(i);
					found = true;
					break;
				}
			}
			found = false;
		}while(found);
	}

	bool RecieveMessageReply(bt_msg_header &msg, uint64_t msg_id) override{
		bt_msg_filter filter;
		filter.flags = bt_msg_filter_flags::Reply;
		filter.reply_to = msg_id;
		return RecieveMessage(msg, filter);
	}

	bt_msg_header AwaitMessageReply(uint64_t msg_id, IProcess &proc = CurrentProcess()) override{
		bt_msg_filter filter;
		filter.flags = bt_msg_filter_flags::Reply;
		filter.reply_to = msg_id;
		return AwaitMessage(filter, proc);
	}

	bool HasMessageBeenProcessed(uint64_t msg_id) override{
		return !HaveMessage(msg_id);
	}

	bool DoesMessageMatch(const bt_msg_header &msg, const bt_msg_filter &filter) override{
		if(msg.critical) return true;
		bool ret = true;
		if((filter.flags & bt_msg_filter_flags::NonReply) && (msg.flags & bt_msg_flags::Reply)) ret = false;
		if((filter.flags & bt_msg_filter_flags::From) && msg.from != filter.pid) ret = false;
		if((filter.flags & bt_msg_filter_flags::Reply) && msg.reply_id != filter.reply_to) ret = false;
		if((filter.flags & bt_msg_filter_flags::Type) && msg.type != filter.type) ret = false;
		if((filter.flags & bt_msg_filter_flags::Source) && msg.source != filter.source) ret = false;
		if((filter.flags & bt_msg_filter_flags::Invert)) ret = !ret;
		return ret;
	}

	IMessageRecieveHandle* CreateRecieveHandle(const bt_msg_filter &filter) override;

	void Subscribe(btos_api::bt_kernel_messages::Enum message, IProcess &proc = CurrentProcess()) override{
		auto pid = proc.ID();
		auto hl = messageLock->LockExclusive();
		for(auto &sub : subscribers){
			if(sub.first == pid && sub.second == message) return;
		}
		subscribers.push_back({pid, message});
	}

	void UnSubscribe(btos_api::bt_kernel_messages::Enum message, IProcess &proc = CurrentProcess()) override{
		auto pid = proc.ID();
		auto hl = messageLock->LockExclusive();
		for(size_t i = 0; i < subscribers.size(); ++i){
			auto &sub = subscribers[i];
			if(sub.first == pid && sub.second == message){
				subscribers.erase(i);
				return;
			}
		}
	}

	void SendKernelEvent(btos_api::bt_kernel_messages::Enum message, const void *content, size_t size) override{
		auto hl = messageLock->LockRecursive();
		for(auto &sub : subscribers){
			if(sub.second == message){
				bt_msg_header msg;
				msg.type = message;
				msg.to = sub.first;
				msg.content = malloc(size);
				msg.length = size;
				msg.source = 0;
				msg.from = 0;
				msg.flags = 0;
				msg.critical = false;
				memcpy(msg.content, content, size);
				SendMessage(msg);
			}
		}
	}
};

class MessageRecieveHandle : public IMessageRecieveHandle{
private:
	MessageManager &manager;

	bt_pid_t pid;
	bt_msg_filter filter;
	bt_msg_header msg;
public:
	MessageRecieveHandle(MessageManager &m, bt_pid_t p, bt_msg_filter f) : manager(m), pid(p), filter(f) {
		msg.valid = false;
	}

	void Close() override{}

	bool Wait() override{
		msg.valid = false;
		auto proc = GetProcess(pid);
		if(!proc || !proc->CanLock() || !manager.messageLock->TryTakeExclusive()) return false;
		manager.RecieveMessage(msg, filter, *proc);
		manager.messageLock->Release();
		return msg.valid;
	}

	bt_msg_header Read() override{
		return msg;
	}
};

IMessageRecieveHandle* MessageManager::CreateRecieveHandle(const bt_msg_filter &filter){
	return new MessageRecieveHandle(*this, CurrentProcess().ID(), filter);
}

static ManualStaticAlloc<MessageManager> theMessageManager;

void Messaging_Init(){
	dbgout("MSG: Init messaging...\n");
	theMessageManager.Init();
}

IMessageManager &GetMessageManager(){
	return *theMessageManager;
}
