#include "service.hpp"
#include "windows.hpp"
#include "client.hpp"

#include <dev/terminal.h>
#include <dev/terminal_ioctl.h>
#include <btos/message.hpp>
#include <btos/messageloop.hpp>

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
	bt_term_stdout();
	bt_term_StartEventMode();
	bt_term_SetEventMode(bt_terminal_event_mode::Both);
	
	uint16_t terminal_ext_id = bt_query_extension("TERMINAL");
	
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	bt_subscribe(bt_kernel_messages::MessageReceipt);

	MessageLoop msgLoop;
	msgLoop.SetPreviewer([&](const Message &msg) -> bool {
		/*stringstream dss;
		dss << "WM: Message ID " << msg.id << " from: " << msg.from << " source: " << msg.source << " type: " << msg.type << endl;
		bt_zero(dss.str().c_str());*/
		if(msg.From() == 0 && msg.Source() == 0 && msg.Type() == bt_kernel_messages::ProcessEnd) {
			bt_pid_t pid = msg.Content<bt_pid_t>();
			stringstream ss;
			ss << "WM: PID: " << pid << " terminated." << endl;
			bt_zero(ss.str().c_str());
			if(clients.find(pid) != clients.end()){
				msgLoop.RemoveHandler(clients[pid]);
				clients.erase(pid);
			}
			if(pid == root_pid) return false;
		}else if(msg.From() == 0 && msg.Source() == 0 && msg.Type() == bt_kernel_messages::MessageReceipt) {
			bt_msg_header omsg = msg.Content<bt_msg_header>();
			if(!(omsg.flags & bt_msg_flags::Reply) && clients.find(omsg.to) != clients.end()){
				clients.at(omsg.to)->SendNextEvent();
			}
		}else if(msg.From() == 0 && msg.Source() == terminal_ext_id && msg.Type() == bt_terminal_message_type::InputEvent) {
			bt_terminal_event event = msg.Content<bt_terminal_event>();
			HandleInput(event);
		}else {
			if(clients.find(msg.From()) == clients.end()) {
				auto newclient = make_shared<Client>(msg.From());
				if(newclient) {
					clients.insert(pair<bt_pid_t, shared_ptr<Client>>(msg.From(), newclient));
					msgLoop.AddHandler(newclient);
				}
			}
		}
		return true;
	});
	msgLoop.RunLoop();
}
