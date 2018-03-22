#include <btos/message.hpp>

namespace btos_api{

	Message Message::Recieve(){
		bt_msg_header h = bt_recv(true);
		Message ret{h};
		ret.filter.flags = 0;
		return ret;
	}

	Message Message::RecieveFiltered(const bt_msg_filter &filter){
		bt_msg_header h = bt_recv_filtered(filter, true);
		Message ret = h;
		ret.filter = filter;
		return ret;
	}

	Message Message::RecieveFrom(bt_pid_t pid, uint16_t source){
		bt_msg_filter f;
		f.flags = bt_msg_filter_flags::From;
		f.pid = pid;
		if(source){
			f.flags |= bt_msg_filter_flags::Source;
			f.source = source;
		}
		return Message::RecieveFiltered(f);
	}

	Message Message::RecieveReply(const Message &msg){
		bt_msg_filter f;
		f.flags = bt_msg_filter_flags::Reply;
		f.reply_to = msg.header.id;
		return Message::RecieveFiltered(f);
	}

	Message::Message(const bt_msg_header &h){
		header = h;
		filter.flags = 0;
	}

	Message &Message::operator=(const Message &other){
		header = other.header;
		filter = other.filter;
		content.reset();
		return *this;
	}

	bt_msg_header Message::Header() const{
		return header;
	}

	bool Message::IsValid() const{
		return header.valid;
	}

	uint64_t Message::ID() const{
		return header.id;
	}

	uint64_t Message::ReplyTo() const{
		return header.reply_id;
	}

	uint32_t Message::Flags() const{
		return header.flags;
	}

	uint16_t Message::Source() const{
		return header.source;
	}

	uint64_t Message::To() const{
		return header.to;
	}

	uint64_t Message::From() const{
		return header.from;
	}

	uint32_t Message::Type() const{
		return header.type;
	}

	size_t Message::Length() const{
		return header.length;
	}

	bool Message::IsCritical() const{
		return header.critical;
	}

	void *Message::Content() const{
		if(!content && header.length){
			content.reset((void*)new char[header.length + 1]);
			((char*)content.get())[header.length] = 0;
			bt_msg_content(const_cast<bt_msg_header*>(&header), content.get(), header.length);
		}
		return content.get();
	}
	
	uint64_t Message::SendReply(void *c, size_t size, uint32_t type) const{
		bt_msg_header reply;
		reply.to = From();
		reply.reply_id = ID();
		reply.flags = bt_msg_flags::Reply;
		reply.length = size;
		reply.content = c;
		reply.type = type;
		return bt_send(reply);
	}

	uint64_t Message::SendReply(uint32_t type) const{
		return Message::SendReply(nullptr, 0, type);
	}

	void Message::Acknowledge(){
		bt_msg_ack(&header);
	}

	void Message::Next(){
		content.reset();
		if(filter.flags){
			bt_next_msg_filtered(&header, filter);
		}else{
			bt_next_msg(&header);
		}
	}

}

