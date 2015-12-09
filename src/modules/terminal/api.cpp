#include <module_stubs.h>
#include <terminal.h>
#include "api.hpp"
#include "terminal.hpp"

#define MIN(a, b) ((a) < (b) ? (a) : (b)) 

template<typename P> uint64_t send_request(pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type, P param){
	size_t totalsize = sizeof(bt_terminal_backend_operation) + sizeof(P);
	bt_terminal_backend_operation *op = (bt_terminal_backend_operation*)malloc(totalsize);
	op->handle = handle;
	op->type = type;
	op->datasize = sizeof(P);
	memcpy(op->data, &param, sizeof(P));
	btos_api::bt_msg_header msg;
	memset((void*)&msg, 0, sizeof(msg));
	msg.to = pid;
	msg.source = terminal_extension_id;
	msg.type = bt_terminal_message_type::BackendOperation;
	msg.content = op;
	msg.length = totalsize;
	return msg_send(&msg);
}

template<typename R, typename P> R send_request_get_reply(pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type, P param){
	btos_api::bt_msg_header msg;
	uint64_t msgid = send_request(pid, handle, type, param);
	msg_recv_reply(&msg, msgid);
	R ret;
	msg_getcontent(&msg, (void*)&ret, sizeof(R));
	msg_acknowledge(&msg, false);
	return ret;
}

void terminal_uapi_fn(uint16_t fn, isr_regs */*regs*/){
	switch(fn){
		case bt_terminal_api::RegisterBackend:{
			break;
		}
		case bt_terminal_api::CreateTerminal:{
			break;
		}
		case bt_terminal_api::ReadBuffer:{
			break;
		}
	}
}

uapi_hanlder_fn terminal_uapi = &terminal_uapi_fn;

user_backend::user_backend(pid_t p, bt_handle_t h) : pid(p), handle_id(h) {}

size_t user_backend::display_read(size_t bytes, char *buf){
	for(size_t i=0; i<bytes; i+=BT_MSG_MAX){
		size_t partsize = MIN(i + BT_MSG_MAX, bytes) - i;
		uint64_t msgid = send_request(pid, handle_id, bt_terminal_backend_operation_type::DisplayRead, partsize);
		bt_msg_header msg;
		msg_recv_reply(&msg, msgid);
		size_t readsize = msg.length;
		msg_getcontent(&msg, (void*)(buf + i), readsize);
		msg_acknowledge(&msg, false);
		if(readsize != partsize) return i + readsize;
	}
	return bytes;
}

size_t user_backend::display_write(size_t /*bytes*/, char */*buf*/){
	return 0;
}
size_t user_backend::display_seek(size_t /*pos*/, uint32_t /*flags*/){
	return 0;
}

size_t user_backend::input_read(size_t /*bytes*/, char */*buf*/){
	return 0;
}

size_t user_backend::input_write(size_t /*bytes*/, char */*buf*/){
	return 0;
}

size_t user_backend::input_seek(size_t /*pos*/, uint32_t /*flags*/){
	return 0;
}

void user_backend::show_pointer(){
}

void user_backend::hide_pointer(){
}

bool user_backend::get_pointer_visibility(){
	return false;
}

void user_backend::set_pointer_bitmap(bt_terminal_pointer_bitmap */*bmp*/){
}

bt_terminal_pointer_info user_backend::get_pointer_info(){
	return bt_terminal_pointer_info();
}

void user_backend::set_pointer_autohide(bool /*val*/){
}

void user_backend::freeze_pointer(){
}

void user_backend::unfreeze_pointer(){
}

void user_backend::set_text_colours(uint8_t /*c*/){
}

uint8_t user_backend::get_text_colours(){
	return 0;
}

size_t user_backend::get_screen_mode_count(){
	return 0;
}

void user_backend::set_screen_mode(const bt_vidmode &/*mode*/){
}

bt_vidmode user_backend::get_screen_mode(size_t /*index*/){
	return bt_vidmode();
}

bt_vidmode user_backend::get_current_screen_mode(){
	return bt_vidmode();
}

void user_backend::set_screen_scroll(bool /*v*/){
}

bool user_backend::get_screen_scroll(){
	return true;
}

void user_backend::set_text_access_mode(bt_vid_text_access_mode::Enum /*mode*/){
}

bt_video_palette_entry user_backend::get_palette_entry(uint8_t /*entry*/){
	return bt_video_palette_entry();
}

void user_backend::clear_screen(){
}

void user_backend::register_global_shortcut(uint16_t /*keycode*/, uint64_t /*termid*/){
}

bool user_backend::is_active(uint64_t /*id*/){
	return false;
}

void user_backend::set_active(uint64_t /*id*/){
}

void user_backend::open(uint64_t /*id*/){
}

void user_backend::close(uint64_t /*id*/){
}

void user_backend::switch_terminal(uint64_t /*id*/){
}

bool user_backend::can_create(){
	return false;
}