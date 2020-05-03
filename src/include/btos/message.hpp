#ifndef _MESSAGE_HPP
#define _MESSAGE_HPP

#include "handle.hpp"

#include <btos.h>
#include <memory>
#include <type_traits>

namespace btos_api{

	class Message{
	private:
		bt_msg_header header;
		bt_msg_filter filter;
		mutable std::unique_ptr<char[]> content;
	public:
		static Message Recieve();
		static Message RecieveFiltered(const bt_msg_filter &filter);
		static Message RecieveFrom(bt_pid_t pid, uint16_t source = 0);
		static Message RecieveReply(const Message &msg);

		Message(const bt_msg_header &h);
		Message(const Message &other) : Message(other.header){}
		Message &operator=(const Message &other);

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
			static_assert(std::is_pod<T>::value, "Message content must be a POD!");
			void *c = Content();
			if(c && header.length >= sizeof(T)){
				return *reinterpret_cast<T*>(c);
			}else{
				return T();
			}
		}

		uint64_t SendReply(void *c, size_t size, uint32_t type = 0) const;
		uint64_t SendReply(uint32_t type = 0) const;
		
		template<typename T> uint64_t SendReply(T c, uint32_t type = 0) const{
			static_assert(std::is_pod<T>::value, "Message content must be a POD!");
			return SendReply(reinterpret_cast<void*>(&c), sizeof(c), type);
		}

		void Acknowledge();
		void Next();
	};
	
	class MessageWait : public Handle{
	public:
		MessageWait(const bt_msg_filter &filter);
		Message GetMessage();
	};

}

#endif
