#include <btos/kernel_calls.h>

uint64_t bt_wait_atom(bt_handle_t a, ENUM_NAME(bt_atom_compare) cmp, uint64_t val){
	bt_handle_t handle = bt_make_wait_atom(a, cmp, val);
	bt_waithandle(handle);
	bt_closehandle(handle);
	return bt_read_atom(a);
}