#ifndef MODULE_MESSAGING_HPP
#define MODULE_MESSAGING_HPP

#include <btos/bt_msg.h>

class IMessageRecieveHandle : public IHandle{
public:
	using bt_msg_header = btos_api::bt_msg_header;

	virtual uint32_t GetType(){
		return KernelHandles::MessageRecive::id;
	}

	virtual void Close() = 0;
	virtual bool Wait() = 0;

	virtual bt_msg_header Read() = 0;
};

class IMessageManager : private nonmovable{
public:
	using bt_msg_header = btos_api::bt_msg_header;
	using bt_msg_filter = btos_api::bt_msg_filter;

	virtual uint64_t SendMessage(bt_msg_header &msg) = 0;
	virtual bool RecieveMessage(bt_msg_header &msg, IProcess &proc = ::CurrentProcess()) = 0;
	virtual bool RecieveMessage(bt_msg_header &msg, const bt_msg_filter &filter, IProcess &proc = ::CurrentProcess()) = 0;
	virtual bt_msg_header AwaitMessage(IProcess &proc = ::CurrentProcess()) = 0;
	virtual bt_msg_header AwaitMessage(const bt_msg_filter &filter, IProcess &proc = ::CurrentProcess()) = 0;
	
	virtual vector<char> MessageContent(bt_msg_header &msg) = 0;
	template<typename T> bool MessageContent(bt_msg_header &msg, T &value){
		auto content = MessageContent(msg);
		if(content.size() == sizeof(T)){
			memcpy(&value, content.begin(), sizeof(T));
			return true;
		}else return false;
	}

	virtual void AcknowledgeMessage(bt_msg_header &msg, bool setStatus = true, IProcess &proc = ::CurrentProcess()) = 0;
	virtual void AwaitNextMessage(bt_msg_header &msg) = 0;
	virtual void AwaitNextMessage(const bt_msg_filter &filter, bt_msg_header &msg) = 0;

	virtual void ClearMessages(IProcess &proc = ::CurrentProcess()) = 0;

	virtual bool RecieveMessageReply(bt_msg_header &msg, uint64_t msg_id) = 0;
	virtual bt_msg_header AwaitMessageReply(uint64_t msg_id, IProcess &proc = ::CurrentProcess()) = 0;

	virtual bool HasMessageBeenProcessed(uint64_t msg_id) = 0;
	virtual bool DoesMessageMatch(const bt_msg_header &msg, const bt_msg_filter &filter) = 0;

	virtual IMessageRecieveHandle* CreateRecieveHandle(const bt_msg_filter &filter) = 0;

	virtual void Subscribe(btos_api::bt_kernel_messages::Enum message, IProcess &proc = ::CurrentProcess()) = 0;
	virtual void UnSubscribe(btos_api::bt_kernel_messages::Enum message, IProcess &proc = ::CurrentProcess()) = 0;
	virtual void SendKernelEvent(btos_api::bt_kernel_messages::Enum message, const void *content, size_t size) = 0;

	template<typename T> void SendKernelEvent(btos_api::bt_kernel_messages::Enum message, const T &content){
		SendKernelEvent(message, &content, sizeof(T));
	}

	virtual ~IMessageManager() {}
};

#endif