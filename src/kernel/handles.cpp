#include "kernel.hpp"
#include "locks.hpp"

static vector<void*> *handle_deps;
static lock handle_deps_lock;

void init_handles(){
    handle_deps = new vector<void*>();
    init_lock(handle_deps_lock);
}

bt_handle_info invalid_handle={kernel_handle_types::invalid, false, nullptr, nullptr, nullptr};

static bool null_wait(void*) {
    return true;
}

bt_handle_info create_handle(uint32_t type, void *value, handle_close_fn close, handle_wait_fn wait){
    bt_handle_info ret;
    ret.type=type;
    ret.value=value;
    ret.close=close;
    ret.wait=wait ? wait : &null_wait;
    ret.open=true;
    return ret;
}
void close_handle(bt_handle_info &handle){
    hold_lock hl(handle_deps_lock);
    auto dep = handle_deps->find(handle.value);
    if(dep != handle_deps->npos) handle_deps->erase(dep);
    if(handle.close && handle.open) handle.close(handle.value);
    handle.open=false;
}

static void ihandle_close(void *ptr){
    ((IHandle*)ptr)->Close();
}

static bool ihandle_wait(void *ptr){
    return ((IHandle*)ptr)->Wait();
}

bt_handle_info create_handle(IHandle *c){
    return create_handle(c->GetType(), (void*)c, &ihandle_close, &ihandle_wait);
}

void add_handle_dep(bt_handle_info &h){
    hold_lock hl(handle_deps_lock);
    if(handle_deps->find(h.value) == handle_deps->npos) handle_deps->push_back(h.value);
}

handle_dep_check_result handle_dep_check(bt_handle_info &h){
    if(!try_take_lock_exclusive(handle_deps_lock)) return handle_dep_check_result::NotAvailable;
    handle_dep_check_result ret;
    if(handle_deps->find(h.value) == handle_deps->npos) ret = handle_dep_check_result::Absent;
    else ret = handle_dep_check_result::Present;
    release_lock(handle_deps_lock);
    return ret;
}