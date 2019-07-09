#include <btos/handle.hpp>
#include <utility>

namespace btos_api{
	
	Handle::Handle(bt_handle_t h, bool o) : handle(h), owned(o) {}

	Handle::Handle(bt_handle_t h) : handle(h), owned(true) {}

	Handle::Handle(Handle &&h){
		*this = std::move(h);
	}

	Handle::~Handle(){
		if(owned && handle) bt_closehandle(handle);
	}
	
	Handle &Handle::operator=(Handle &&h){
		handle = h.handle;
		owned = h.owned;
		h.handle = 0;
		h.owned = false;
		return *this;
	}

	bool Handle::Query() const{
		return bt_queryhandle(handle);
	}

	bt_handle_t Handle::GetHandle() const{
		return handle;
	}
	
	void Handle::Wait(){
		bt_waithandle(handle);
	}
}
