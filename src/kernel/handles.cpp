#include "kernel.hpp"

bt_handle invalid_handle={kernel_handle_types::invalid, false, NULL, NULL};

bt_handle create_handle(uint32_t type, void *value, handle_close_fn close){
    bt_handle ret;
    ret.type=type;
    ret.value=value;
    ret.close=close;
    ret.open=true;
    return ret;
}
void close_handle(bt_handle &handle){
    if(handle.close && handle.open) handle.close(handle.value);
    handle.open=false;
}