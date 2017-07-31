#include <sm/sm.h>
#include <btos/envvars.hpp>
#include <btos/message.hpp>

#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

namespace btos_api{
namespace sm{
	
static bt_pid_t sm_pid;

static bool Init(){
	if(!sm_pid){
		string pid_str = GetEnv("SM_PID");
		sm_pid = strtoull(pid_str.c_str(), NULL, 10);
		if(!sm_pid){
			cout << "ERROR: Could not communicate with SM." << endl;
			return false;
		}
		return true;
	}
	return true;
}

static bt_msg_header SendMessage(sm_RequestType::Enum type, size_t size, void* content, bool waitreply){
	if(!sm_pid  && !Init()) return bt_msg_header();
	bt_msg_header msg;
	msg.flags = 0;
	msg.to = sm_pid;
	msg.type = type;
	msg.length = size;
	msg.content = content;
	msg.id = bt_send(msg);
	if(waitreply) {
		bt_msg_header ret;
		bt_msg_filter filter;
		filter.flags = bt_msg_filter_flags::Reply;
		filter.reply_to = msg.id;
		ret = bt_recv_filtered(filter);
		while(ret.reply_id != msg.id){
			stringstream ss;
			ss << "LIBSM: Spurious message!" << endl;
			ss << "Message id: " << ret.id << endl;
			ss << "From : " << ret.from << endl;
			ss << "Flags : " << ret.flags << endl;
			ss << "Reply ID: " << ret.reply_id << " (Waiting for: " << msg.id << ")" << endl;
			bt_zero(ss.str().c_str());
			bt_next_msg_filtered(&ret, filter);
		}
		return ret;
	}
	else return bt_msg_header();
}

template<typename T> static bt_msg_header SendMessage(sm_RequestType::Enum type, const T& content, bool waitreply){
	return SendMessage(type, sizeof(T), (void*)&content, waitreply);
}

extern "C"  void SM_SetServerPID(bt_pid_t pid){
	sm_pid = pid;
}

bt_pid_t SM_GetService(const string &name){
	Message m = SendMessage(sm_RequestType::GetService, name.length(), (void*)name.c_str(), true);
	return m.Content<bt_pid_t>();
}

extern "C" bt_pid_t SM_GetService(const char *name){
	return SM_GetService(string(name));
}

bt_pid_t SM_StartService(const string &name){
	Message m = SendMessage(sm_RequestType::StartService, name.length(), (void*)name.c_str(), true);
	return m.Content<bt_pid_t>();
}

extern "C" bt_pid_t SM_StartService(const char *name){
	return SM_StartService(string(name));
}

void SM_ReleaseService(const string &name){
	SendMessage(sm_RequestType::ReleaseService, name.length(), (void*)name.c_str(), false);
}

extern "C" void SM_ReleaseService(const char *name){
	return SM_ReleaseService(string(name));
}

void SM_StopService(const string &name){
	SendMessage(sm_RequestType::StopService, name.length(), (void*)name.c_str(), false);
}

extern "C" void SM_StopService(const char *name){
	return SM_StopService(string(name));
}

extern "C" size_t SM_GetServiceCount(){
	Message m = SendMessage(sm_RequestType::GetServiceCount, nullptr, true);
	return m.Content<size_t>();
}

extern "C" sm_ServiceInfo SM_GetServiceInfo(size_t index){
	Message m = SendMessage(sm_RequestType::GetServiceCount, index, true);
	return m.Content<sm_ServiceInfo>();
}

}
}
