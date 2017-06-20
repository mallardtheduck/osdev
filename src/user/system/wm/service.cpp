#include "service.hpp"
#include "windows.hpp"
#include "client.hpp"

#include <dev/terminal.h>

#include <map>
#include <sstream>

using namespace std;

bt_handle stdin_handle;

map<bt_pid_t, shared_ptr<Client>> clients;

void Service(bt_pid_t root_pid){
	char stdout_path[BT_MAX_PATH]={0};
	bt_getenv("STDIN", stdout_path, BT_MAX_PATH);

	bt_handle fh=bt_fopen(stdout_path, FS_Read | FS_Write);
	stdin_handle = fh;
	bt_fioctl(fh, bt_terminal_ioctl::StartEventMode, 0, NULL);
	bt_terminal_event_mode::Enum event_mode = bt_terminal_event_mode::Both;
	bt_fioctl(fh, bt_terminal_ioctl::SetEventMode, sizeof(event_mode), (char*)&event_mode);
	
	uint16_t terminal_ext_id = bt_query_extension("TERMINAL");
	
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	bt_subscribe(bt_kernel_messages::MessageReceipt);
	bt_msg_header msg = bt_recv(true);
	while(true) {
		/*stringstream dss;
		dss << "WM: Message ID " << msg.id << " from: " << msg.from << " source: " << msg.source << " type: " << msg.type << endl;
		bt_zero(dss.str().c_str());*/
		if(msg.from == 0 && msg.source == 0 && msg.type == bt_kernel_messages::ProcessEnd) {
			bt_pid_t pid = 0;
			bt_msg_content(&msg, (void*)&pid, sizeof(pid));
			stringstream ss;
			ss << "WM: PID: " << pid << " terminated." << endl;
			bt_zero(ss.str().c_str());
			clients.erase(pid);
			if(pid == root_pid) return;
		}else if(msg.from == 0 && msg.source == 0 && msg.type == bt_kernel_messages::MessageReceipt) {
			bt_msg_header omsg;
			bt_msg_content(&msg, (void*)&omsg, sizeof(omsg));
			if(!(omsg.flags & bt_msg_flags::Reply) && clients.find(omsg.to) != clients.end()){
				clients.at(omsg.to)->SendNextEvent();
			}
		}else if(msg.from == 0 && msg.source == terminal_ext_id && msg.type == bt_terminal_message_type::InputEvent) {
			bt_terminal_event event;
			bt_msg_content(&msg, (void*)&event, sizeof(event));
			HandleInput(event);
		}else {
			if(clients.find(msg.from) == clients.end()) {
				Client *newclient = new Client(msg.from);
				if(newclient) {
					shared_ptr<Client> ptr(newclient);
					clients.insert(pair<bt_pid_t, shared_ptr<Client>>(msg.from, ptr));
				}
			}
			try {
				clients.at(msg.from)->ProcessMessage(msg);
			} catch(out_of_range&) {}
		}
		bt_next_msg(&msg);
	}
}
