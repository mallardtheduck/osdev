#ifndef _MESSAGE_HPP
#define _MESSAGE_HPP

#include <btos.h>
#include <memory>

namespace btos_api{

	class Message{
	private:
		bt_msg_header header;
		bt_msg_filter filter;
		mutable std::unique_ptr<void> content;
	public:
		static Message Recieve();
		static Message RecieveFiltered(const bt_msg_filter &filter);
		static Message RecieveFrom(bt_pid_t pid, uint16_t source = 0);
		static Message RecieveReply(const Message &msg);

		Message(const bt_msg_header &h);

		bt_msg_header Header() const;
		bool IsValid() const;
		uint64_t ID() const;
		uint64_t ReplyTo() const;
		uint32_t Flags() const;
		uint16_t Source() const;
		uint64_t To() const;
		uint64_t From() const;
		uint32_t Type() const;
		size_t Length() const;
		bool IsCritical() const;

		void *Content() const;

		template<typename T> T Content() const{
			void *c = Content();
			if(c && header.length >= sizeof(T)){
				return *reinterpret_cast<T*>(c);
			}else{
				return T();
			}
		}

		void SendReply(void *c, size_t size) const;
		
		template<typename T> void SendReply(T c) const{
			SendReply(reinterpret_cast<void*>(&c), sizeof(c));
		}

		void Acknowledge();
		void Next();
	};

}

#endif
