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
		virtual ~Handle();

		bool Query();
		bt_handle_t GetHandle();
	};

}

#endif
