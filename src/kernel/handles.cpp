#include "kernel.hpp"

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