#include <btos.h>
#include <dev/terminal.h>

uint16_t bt_terminal_ext_id;

void bt_terminial_init(){
	if(bt_terminal_ext_id == 0) bt_terminal_ext_id = bt_query_extension("TERMINAL");
}

uint32_t bt_terminal_api_call(uint16_t fn, uint32_t b, uint32_t c, uint32_t d){
	bt_terminial_init();
	uint32_t a = (bt_terminal_ext_id << 16) + fn;
	return btos_call(a, b, c, d);
}

bt_handle_t bt_terminal_create_backend(){
	return bt_terminal_api_call(ENUM_GET(bt_terminal_api, RegisterBackend), 0, 0, 0);
}

bt_handle_t bt_terminal_create_terminal(bt_handle_t backend){
	return bt_terminal_api_call(ENUM_GET(bt_terminal_api, CreateTerminal), backend, 0, 0);
}

void bt_terminal_read_buffer(bt_handle_t terminal, size_t size, uint8_t *buf){
	bt_terminal_api_call(ENUM_GET(bt_terminal_api, ReadBuffer), terminal, size, (uint32_t)buf);
}

void bt_terminal_queue_event(bt_handle_t terminal, bt_terminal_event *event){
	bt_terminal_api_call(ENUM_GET(bt_terminal_api, QueueEvent), terminal, (uint32_t)event, 0);
}

bt_pid_t bt_terminal_run(bt_handle_t terminal, const char *command){
	bt_pid_t ret;
	bt_terminal_api_call(ENUM_GET(bt_terminal_api, TerminalRun), terminal, (uint32_t)command, (uint32_t)&ret);
	return ret;
}

size_t bt_terminal_get_pos(bt_handle_t terminal){
	return (size_t) bt_terminal_api_call(ENUM_GET(bt_terminal_api, GetTerminalPos), terminal, 0, 0);
}

size_t bt_terminal_get_title(bt_handle_t terminal, size_t size, char *buf){
	return bt_terminal_api_call(ENUM_GET(bt_terminal_api, GetTerminalTitle), terminal, size, (uint32_t)buf);
}

uint32_t bt_terminal_get_id(bt_handle_t terminal){
	return bt_terminal_api_call(ENUM_GET(bt_terminal_api, GetTerminalID), terminal, 0, 0);
}
