#include <btos_module.h>
#include <dev/terminal.h>
#include "vterm.hpp"
#include "api.hpp"
#include "terminal.hpp"
#include "device.hpp"
#include <util/asprintf.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b)) 

using namespace btos_api;

template<typename P> uint64_t send_request(bt_pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type, P *param, size_t size){
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
	return API->GetMessageManager().SendMessage(msg);
}

template<typename P> uint64_t send_request(bt_pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type, P param){
	return send_request(pid, handle, type, &param, sizeof(P));
}

uint64_t send_request(bt_pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type){
	return send_request(pid, handle, type, (void*)NULL, 0);
}

template<typename R, typename P> R send_request_get_reply(bt_pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type, P param){
	btos_api::bt_msg_header msg;
	uint64_t msgid = send_request(pid, handle, type, param);
	auto kproc = API->GetProcess(0);
	msg = API->GetMessageManager().AwaitMessageReply(msgid, *kproc);
	R ret;
	auto content = API->GetMessageManager().MessageContent(msg);
	if(content.size() == sizeof(ret)) memcpy(&ret, content.begin(), sizeof(ret));
	API->GetMessageManager().AcknowledgeMessage(msg, false);
	return ret;
}

template<typename R> R send_request_get_reply(bt_pid_t pid, bt_handle_t handle, bt_terminal_backend_operation_type::Enum type){
	btos_api::bt_msg_header msg;
	uint64_t msgid = send_request(pid, handle, type);
	auto kproc = API->GetProcess(0);
	msg = API->GetMessageManager().AwaitMessageReply(msgid, *kproc);
	R ret;
	auto content = API->GetMessageManager().MessageContent(msg);
	if(content.size() == sizeof(ret)) memcpy(&ret, content.begin(), sizeof(ret));
	API->GetMessageManager().AcknowledgeMessage(msg, false);
	return ret;
}

void close_backend(i_backend *back){
	terminals->delete_backend(back);
	delete back;
}

void close_terminal(uint64_t termid){
	vterm *vt = terminals->get(termid);
	if(vt) vt->set_backend(NULL);
}

void terminal_uapi_fn(uint16_t fn, ICPUState &state){
	uint32_t backend_handle_type = (terminal_extension_id << 16) | 0x01;
	uint32_t terminal_handle_type = (terminal_extension_id << 16) | 0x02;
	switch(fn){
		case bt_terminal_api::RegisterBackend:{
			user_backend *backend = new user_backend(CurrentProcess().ID());
			auto handle = MakeGenericHandle(backend_handle_type, backend, &close_backend);
			bt_handle_t handle_id = CurrentProcess().AddHandle(handle);
			backend->set_handlde_id(handle_id);
			state.Get32BitRegister(Generic_Register::GP_Register_A) = handle_id;
			break;
		}
		case bt_terminal_api::CreateTerminal:{
			bt_handle_t backend_id = state.Get32BitRegister(Generic_Register::GP_Register_B);
			auto backend_h = CurrentProcess().GetHandle(backend_id);
			if(auto backend_handle = GenericHandleCast<i_backend*>(backend_handle_type, backend_h)){
				uint64_t terminal_id = terminals->create_terminal(backend_handle->GetData());
				if(terminal_id){
					vterm *vt = terminals->get(terminal_id);
					vt->sync(false);
					vt->activate();
					auto terminal_handle = MakeGenericHandle(terminal_handle_type, terminal_id, &close_terminal);
					auto handle_id = CurrentProcess().AddHandle(terminal_handle);
					state.Get32BitRegister(Generic_Register::GP_Register_A) = handle_id;
				}else{
					state.Get32BitRegister(Generic_Register::GP_Register_A) = 0;
				}
			}
			break;
		}
		case bt_terminal_api::ReadBuffer:{
			auto h = CurrentProcess().GetHandle((bt_handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
			if(auto handle = GenericHandleCast<uint64_t>(terminal_handle_type, h)){
				uint64_t termid = handle->GetData();
				vterm *vt = terminals->get(termid);
				if(vt) vt->read_buffer((size_t)state.Get32BitRegister(Generic_Register::GP_Register_C), (uint8_t*)state.Get32BitRegister(Generic_Register::GP_Register_D));
			}
			break;
		}
		case bt_terminal_api::QueueEvent:{
			auto h = CurrentProcess().GetHandle((bt_handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
			if(auto handle = GenericHandleCast<uint64_t>(terminal_handle_type, h)){
				uint64_t termid = handle->GetData();
				vterm *vt = terminals->get(termid);
				if(vt){
					bt_terminal_event *e = (bt_terminal_event*)state.Get32BitRegister(Generic_Register::GP_Register_C);
					switch(e->type){
						case bt_terminal_event_type::Pointer:{
							vt->queue_pointer(e->pointer);
							break;
						}
						case bt_terminal_event_type::Key:{
							vt->queue_input(e->key);
							break;
						}
					}
				}
			}
			break;
		}
		case bt_terminal_api::TerminalRun:{
			auto h = CurrentProcess().GetHandle((bt_handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
			if(auto handle = GenericHandleCast<uint64_t>(terminal_handle_type, h)){
				uint64_t termid = handle->GetData();
				vterm *vt = terminals->get(termid);
				if(vt){
					char *command = (char*)state.Get32BitRegister(Generic_Register::GP_Register_C);
					char old_terminal_id[128] = "0";
					strncpy(old_terminal_id, CurrentProcess().GetEnvironmentVariable(terminal_var), 128);
					char new_terminal_id[128]= {0};
					i64toa(vt->get_id(), new_terminal_id, 10);
					CurrentProcess().SetEnvironmentVariable(terminal_var, new_terminal_id);
					bt_pid_t pid = API->GetProcessManager().Spawn(command, {});
					CurrentProcess().SetEnvironmentVariable(terminal_var, old_terminal_id);
					*(bt_pid_t*)state.Get32BitRegister(Generic_Register::GP_Register_D) = pid;
				}
			}
			break;
		}
		case bt_terminal_api::GetTerminalPos:{
			auto h = CurrentProcess().GetHandle((bt_handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
			if(auto handle = GenericHandleCast<uint64_t>(terminal_handle_type, h)){
				uint64_t termid = handle->GetData();
				vterm *vt = terminals->get(termid);
				if(vt){
					state.Get32BitRegister(Generic_Register::GP_Register_A) = (uint32_t)vt->getpos();
				}
			}
			break;
		}
		case bt_terminal_api::GetTerminalTitle:{
			auto h = CurrentProcess().GetHandle((bt_handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
			if(auto handle = GenericHandleCast<uint64_t>(terminal_handle_type, h)){
				uint64_t termid = handle->GetData();
				vterm *vt = terminals->get(termid);
				if(vt && state.Get32BitRegister(Generic_Register::GP_Register_D) && state.Get32BitRegister(Generic_Register::GP_Register_C)){
					strncpy((char*)state.Get32BitRegister(Generic_Register::GP_Register_D), vt->get_title(), state.Get32BitRegister(Generic_Register::GP_Register_C));
					state.Get32BitRegister(Generic_Register::GP_Register_A) = strlen(vt->get_title());
				}
			}
			break;
		}
		case bt_terminal_api::GetTerminalID:{
			auto h = CurrentProcess().GetHandle((bt_handle_t)state.Get32BitRegister(Generic_Register::GP_Register_B));
			if(auto handle = GenericHandleCast<uint64_t>(terminal_handle_type, h)){
				uint64_t termid = handle->GetData();
				state.Get32BitRegister(Generic_Register::GP_Register_A) = (uint32_t)termid;
			}
			break;
		}
	}
}

user_backend::user_backend(bt_pid_t p) : pid(p), handle_id(0), active_id(0) {}

void user_backend::set_handlde_id(bt_handle_t h){
	handle_id = h;
}

size_t user_backend::display_read(size_t bytes, char *buf){
	for(size_t i = 0; i<bytes; i += BT_MSG_MAX){
		size_t partsize = MIN(i + BT_MSG_MAX, bytes) - i;
		uint64_t msgid = send_request(pid, handle_id, bt_terminal_backend_operation_type::DisplayRead, partsize);
		bt_msg_header msg;
		auto kproc = API->GetProcess(0);
		msg = API->GetMessageManager().AwaitMessageReply(msgid, *kproc);
		size_t readsize = msg.length;
		auto content = API->GetMessageManager().MessageContent(msg);
		memcpy(buf + i, content.begin(), readsize);
		API->GetMessageManager().AcknowledgeMessage(msg, false);
		if(readsize != partsize) return i + readsize;
	}
	return bytes;
}

size_t user_backend::display_write(size_t bytes, const char *buf){
	for(size_t i=0; i<bytes; i+=(BT_MSG_MAX - sizeof(bt_terminal_backend_operation))){
		size_t partsize = MIN(i + BT_MSG_MAX, bytes) - i;
		uint64_t msgid = send_request(pid, handle_id, bt_terminal_backend_operation_type::DisplayWrite, (buf + i), partsize);
		bt_msg_header msg;
		auto kproc = API->GetProcess(0);
		msg = API->GetMessageManager().AwaitMessageReply(msgid, *kproc);
		size_t readsize = 0;
		API->GetMessageManager().MessageContent(msg, readsize);
		API->GetMessageManager().AcknowledgeMessage(msg, false);
		if(readsize != partsize) return i + readsize;
	}
	return bytes;
}
size_t user_backend::display_seek(size_t pos, uint32_t flags){
	struct __attribute__((packed)) {
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

size_t user_backend::get_screen_mode_count(){
	return send_request_get_reply<size_t>(pid, handle_id, bt_terminal_backend_operation_type::GetScreenModeCount);
}

void user_backend::set_screen_mode(const bt_vidmode &mode){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetScreenMode, mode);
}

bt_vidmode user_backend::get_screen_mode(size_t index){
	return send_request_get_reply<bt_vidmode>(pid, handle_id, bt_terminal_backend_operation_type::GetScreenMode, index);
}

bt_vidmode user_backend::get_current_screen_mode(){
	return send_request_get_reply<bt_vidmode>(pid, handle_id, bt_terminal_backend_operation_type::GetCurrentScreenMode);
}

bt_video_palette_entry user_backend::get_palette_entry(uint8_t entry){
	return send_request_get_reply<bt_video_palette_entry>(pid, handle_id, bt_terminal_backend_operation_type::GetPaletteEntry, entry);
}

void user_backend::clear_screen(){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::ClearScreen);
}

void user_backend::set_cursor_position(size_t pos){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::SetCursorPosition, pos);
}

void user_backend::register_global_shortcut(uint16_t keycode, uint64_t termid){
	struct{
		uint16_t keycode;
		uint64_t termid;
	} shortcut_params = {keycode, termid};
	send_request(pid, handle_id, bt_terminal_backend_operation_type::RegisterGlobalShortcut, shortcut_params);
}

bool user_backend::is_active(uint64_t id){
	if(id == active_id) return true;
	return send_request_get_reply<bool>(pid, handle_id, bt_terminal_backend_operation_type::IsActive, id);
}

void user_backend::set_active(uint64_t id){
	active_id = id;
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

void user_backend::refresh(){
	send_request(pid, handle_id, bt_terminal_backend_operation_type::Refresh);
}

uint32_t user_backend::get_pointer_speed(){
	return 0;
}

void user_backend::set_pointer_speed(uint32_t /*speed*/){
}

const char *user_backend::desc(){
	return "user";
}