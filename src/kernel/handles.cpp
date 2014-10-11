#include "kernel.hpp"

bt_handle_info invalid_handle={kernel_handle_types::invalid, false, NULL, NULL};

bt_handle_info create_handle(uint32_t type, void *value, handle_close_fn close){
    bt_handle_info ret;
    ret.type=type;
    ret.value=value;
    ret.close=close;
    ret.open=true;
    return ret;
}
void close_handle(bt_handle_info &handle){
    if(handle.close && handle.open) handle.close(handle.value);
    handle.open=false;
}