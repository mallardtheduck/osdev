#ifndef _WAITING_HPP
#define _WAITING_HPP

bt_handle_info create_wait_any_handle(bt_handle_info *handles, size_t count);
bt_handle_info create_wait_all_handle(bt_handle_info *handles, size_t count);
size_t get_wait_index(bt_handle_info &handle);

#endif