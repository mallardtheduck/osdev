#ifndef _HANDLE_HPP
#define _HANDLE_HPP

#include <btos.h>

namespace btos_api{

	class Handle{
	protected:
		bt_handle_t handle;
		bool owned;

		Handle(bt_handle_t h, bool o);
		Handle(const Handle&) = delete;
		Handle &operator=(const Handle&) = delete;
	public:
		Handle(bt_handle_t h);
		Handle(Handle &&h);
		
		Handle &operator=(Handle&&) = default;
		
		virtual ~Handle();

		bool Query() const;
		bt_handle_t GetHandle() const;
	};

}

#endif
