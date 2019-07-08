#include <btos/multiwait.hpp>

namespace btos_api{
	
bt_handle_t make_wait_handle(const std::vector<Handle*> &handles, MultiWait::WaitMode mode){
	std::vector<bt_handle_t> handle_ts;
	for(auto h : handles) handle_ts.push_back(h->GetHandle());
	if(mode == MultiWait::WaitMode::Any) return bt_make_wait_any(handle_ts.data(), handle_ts.size());
	else return bt_make_wait_all(handle_ts.data(), handle_ts.size());
}

MultiWait::MultiWait(const std::vector<Handle*> &h, WaitMode mode) : Handle(make_wait_handle(h, mode)), handles(h)
{}

Handle *MultiWait::GetTriggerHandle(){
	size_t index = bt_wait_index(handle);
	if(index < handles.size()) return handles[index];
	else return nullptr;
}

}