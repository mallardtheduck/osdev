#include <sm/services.hpp>
#include <btos/ini.hpp>
#include <cstring>
#include <dev/rtc.h>
#include <sstream>

#define dbgpf(...) do{snprintf(dbgbuf, 128, __VA_ARGS__); bt_zero(dbgbuf);}while(false)
#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;

namespace btos_api{
namespace sm{

ServiceInstance::ServiceInstance(Process p, Service s, bool st) : proc(p), service(s), sticky(st) {}

Process ServiceInstance::GetProcess(){
	return proc;
}
Service ServiceInstance::GetService(){
	return service;
}

void ServiceInstance::AddRef(bt_pid_t pid){
	refs.insert(pid);
}
void ServiceInstance::RemoveRef(bt_pid_t pid){
	refs.erase(pid);
}
bool ServiceInstance::HasRef(bt_pid_t pid){
	return refs.find(pid) != refs.end();
}
size_t ServiceInstance::GetRefCount(){
	return refs.size();
}

void ServiceInstance::SetSticky(bool s){
	sticky = s;
}
bool ServiceInstance::IsSticky(){
	return sticky;
}

void ServiceInstance::Stop(){
	DBG("SM: Service " << service.Name() << " status: " << proc.GetStatus()); 
	if(proc.GetStatus() != bt_proc_status::Running) return;
	bt_msg_header msg;
	msg.flags = 0;
	msg.to = proc.GetPID();
	msg.type = sm_ServiceRequest::StopService;
	msg.length = 0;
	DBG("SM: Instructing service to stop.");
	msg.id = bt_send(msg);
	for(size_t i = 0; i < 10; ++i){
		bt_rtc_sleep(100);
		if(proc.GetStatus() != bt_proc_status::Running) return;
	}
	DBG("SM: Killing service.");
	proc.Kill();
}

ServiceInstance Service::Start(){
	return {Process::Spawn(path), *this};
}

string Service::Name(){
	return name;
}

string Service::Path(){
	return path;
}

sm_ServiceInfo Service::Info(){
	sm_ServiceInfo ret;
	strncpy(ret.name, name.c_str(), BT_MAX_SEGLEN-1);
	ret.running = false;
	ret.users = 0;
	ret.pid = 0;
	return ret;
}

}
}
