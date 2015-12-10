#include <module_stubs.h>
#include <terminal.h>
#include "api.hpp"
#include "terminal.hpp"

#define MIN(a, b) ((a) < (b) ? (a) : (b)) 

template<typename P> uint64_t send_request(pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type, P *param, size_t size){
	size_t totalsize = sizeof(bt_terminal_backend_operation) + size;
	bt_terminal_backend_operation *op = (bt_terminal_backend_operation*)malloc(totalsize);
	op->handle = handle;
	op->type = type;
	op->datasize = size;
	if(size > 0) memcpy(op->data, param, size);
	btos_api::bt_msg_header msg;
	memset((void*)&msg, 0, sizeof(msg));
	msg.to = pid;
	msg.source = terminal_extension_id;
	msg.type = bt_terminal_message_type::BackendOperation;
	msg.content = op;
	msg.length = totalsize;
	return msg_send(&msg);
}

template<typename P> uint64_t send_request(pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type, P param){
	return send_request(pid, handle, type, &param, sizeof(P));
}

uint64_t send_request(pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type){
	return send_request(pid, handle, type, (void*)NULL, 0);
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

template<typename R> R send_request_get_reply(pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type){
	btos_api::bt_msg_header msg;
	uint64_t msgid = send_request(pid, handle, type);
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
		case bt_terminal_api::QueueEvent:{
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

size_t user_backend::display_write(size_t bytes, char *buf){
	for(size_t i=0; i<bytes; i+=(BT_MSG_MAX - sizeof(bt_terminal_backend_operation))){
		size_t partsize = MIN(i + BT_MSG_MAX, bytes) - i;
		uint64_t msgid = send_request(pid, handle_id, bt_terminal_backend_operation_type::DisplayRead, (buf + i), partsize);
		bt_msg_header msg;
		msg_recv_reply(&msg, msgid);
		size_t readsize = 0;
		msg_getcontent(&msg, (void*)readsize, sizeof(readsize));
		msg_acknowledge(&msg, false);
		if(readsize != partsize) return i + readsize;
	}
	return bytes;
}
size_t user_backend::display_seek(size_t pos, uint32_t flags){
	struct {
		size_t pos;
		uint32_t flags;
	}seek_params = {pos, flags};
	return send_request_get_reply<size_t>(pid, handle_id, bt_terminal_backend_operation_type::DisplaySeek, seek_params);
}

void user_backend::show_pointer(){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::ShowPointer);
}

void user_backend::hide_pointer(){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::HidePointer);
}

bool user_backend::get_pointer_visibility(){
	return send_request_get_reply<bool>(pid, handle_id, bt_terminal_backend_operation_type::GetPointerVisibility);
}

void user_backend::set_pointer_bitmap(bt_terminal_pointer_bitmap *bmp){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetPointerBitmap, bmp, bmp->datasize + sizeof(*bmp));
}

bt_terminal_pointer_info user_backend::get_pointer_info(){
	return send_request_get_reply<bt_terminal_pointer_info>(pid, handle_id, bt_terminal_backend_operation_type::GetPointerInfo);
}

void user_backend::set_pointer_autohide(bool val){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetPointerAutohide, val);
}

void user_backend::freeze_pointer(){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::FreezePointer);
}

void user_backend::unfreeze_pointer(){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::UnfreezePointer);
}

void user_backend::set_text_colours(uint8_t c){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetTextColours, c);
}

uint8_t user_backend::get_text_colours(){
	return send_request_get_reply<uint8_t>(pid, handle_id, bt_terminal_backend_operation_type::GetTextColours);
}

size_t user_backend::get_screen_mode_count(){
	return send_request_get_reply<size_t>(pid, handle_id, bt_terminal_backend_operation_type::GetScreenModeCount);
}

void user_backend::set_screen_mode(const bt_vidmode &mode){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetScreenMode, mode);
}

bt_vidmode user_backend::get_screen_mode(size_t /*index*/){
	return send_request_get_reply<bt_vidmode>(pid, handle_id, bt_terminal_backend_operation_type::GetScreenMode);
}

bt_vidmode user_backend::get_current_screen_mode(){
	return send_request_get_reply<bt_vidmode>(pid, handle_id, bt_terminal_backend_operation_type::GetCurrentScreenMode);
}

void user_backend::set_screen_scroll(bool v){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetScreenScroll, v);
}

bool user_backend::get_screen_scroll(){
	return send_request_get_reply<bool>(pid, handle_id, bt_terminal_backend_operation_type::GetScreenScroll);
}

void user_backend::set_text_access_mode(bt_vid_text_access_mode::Enum mode){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetTextAccessMode, mode);
}

bt_video_palette_entry user_backend::get_palette_entry(uint8_t entry){
	return send_request_get_reply<bt_video_palette_entry>(pid, handle_id, bt_terminal_backend_operation_type::GetPaletteEntry, entry);
}

void user_backend::clear_screen(){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::ClearScreen);
}

void user_backend::register_global_shortcut(uint16_t keycode, uint64_t termid){
	struct{
		uint16_t keycode;
		uint64_t termid;
	} shortcut_params = {keycode, termid};
	send_request(pid, handle_id, bt_terminal_backend_operation_type::RegisterGlobalShortcut, shortcut_params);
}

bool user_backend::is_active(uint64_t id){
	return send_request_get_reply<bool>(pid, handle_id, bt_terminal_backend_operation_type::IsActive, id);
}

void user_backend::set_active(uint64_t id){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetActive, id);
}

void user_backend::open(uint64_t id){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::Open, id);
}

void user_backend::close(uint64_t id){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::Close, id);
}

void user_backend::switch_terminal(uint64_t id){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SwitchTerminal, id);
}

bool user_backend::can_create(){
	return send_request_get_reply<bool>(pid, handle_id, bt_terminal_backend_operation_type::CanCreate);
}