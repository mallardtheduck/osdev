#include "service.hpp"
#include "windows.hpp"

#include <btos_stubs.h>
#include <terminal.h>

#include <sstream>

using namespace std;

void Service(){
	char stdout_path[BT_MAX_PATH]={0};
	bt_getenv("STDIN", stdout_path, BT_MAX_PATH);

	bt_handle fh=bt_fopen(stdout_path, FS_Read | FS_Write);
	bt_fioctl(fh, bt_terminal_ioctl::StartEventMode, 0, NULL);
	bt_terminal_event_mode::Enum event_mode = bt_terminal_event_mode::Both;
	bt_fioctl(fh, bt_terminal_ioctl::SetEventMode, sizeof(event_mode), (char*)&event_mode);
	
	bt_msg_filter terminal_filter;
	terminal_filter.flags = (bt_msg_filter_flags::Enum) (bt_msg_filter_flags::From | bt_msg_filter_flags::Source);
	terminal_filter.pid = 0;
	terminal_filter.source = bt_query_extension("TERMINAL");
	bt_msg_header header = bt_recv_filtered(terminal_filter);
	while(true){
		bt_terminal_event event;
		bt_msg_content(&header, (void*)&event, sizeof(event));
		stringstream ss;
		ss << "WM: Input message ID:" << header.id << endl;
		ss << "WM: Header addr:" << &header << endl;
		bt_zero(ss.str().c_str());
		HandleInput(event);
		bt_next_msg_filtered(&header, terminal_filter);
	}
}