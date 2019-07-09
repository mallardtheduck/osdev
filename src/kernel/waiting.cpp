#include "kernel.hpp"

struct waitlist{
	bt_handle_info *handles;
	size_t count;
	size_t index = 0;
	
	waitlist(bt_handle_info *hs, size_t c) : handles(hs), count(c) {}
};

static void delete_waitlist(void *ptr){
	auto *wl = (waitlist*)ptr;
	delete[] wl->handles;
	delete (waitlist*)ptr;
};

static bool wait_any_waiter(void *ptr){
	waitlist *lst = (waitlist*)ptr;
	for(size_t i = 0; i < lst->count; ++i){
		auto chk = handle_dep_check(lst->handles[i]);
		if(chk == handle_dep_check_result::Present){
			if(lst->handles[i].wait(lst->handles[i].value)){
				lst->index = i;
				return true;	
			}
		}
	}
	return false;
};


static bool wait_all_waiter(void *ptr){
	waitlist *lst = (waitlist*)ptr;
	for(size_t i = 0; i < lst->count; ++i){
		auto chk = handle_dep_check(lst->handles[i]);
		if(chk == handle_dep_check_result::Present){
			if(!lst->handles[i].wait(lst->handles[i].value)){
				lst->index = i;
				return false;
			}
		}else if(chk == handle_dep_check_result::NotAvailable) return false;
	}
	return true;
};

bt_handle_info create_wait_any_handle(bt_handle_info *handles, size_t count){
	waitlist *wl = new waitlist{handles, count};
	for(size_t i = 0; i < count; ++i) add_handle_dep(handles[i]);
	return create_handle(kernel_handle_types::wait, (void*)wl, &delete_waitlist, &wait_any_waiter);
}

bt_handle_info create_wait_all_handle(bt_handle_info *handles, size_t count){
	waitlist *wl = new waitlist{handles, count};
	for(size_t i = 0; i < count; ++i) add_handle_dep(handles[i]);
	return create_handle(kernel_handle_types::wait, (void*)wl, &delete_waitlist, &wait_all_waiter);
}

size_t get_wait_index(bt_handle_info &handle){
	if(handle.type == kernel_handle_types::wait){
		return ((waitlist*)handle.value)->index;
	}else return 0;
}

static bool wait_handle_blockcheck(void *h){
    bt_handle_info *handle = (bt_handle_info*)h;
    if(handle->open && handle->wait) return handle->wait(handle->value);
    else return true;
}

void wait_handle(bt_handle_info &handle){
    sch_setblock(&wait_handle_blockcheck, (void*)&handle);
}