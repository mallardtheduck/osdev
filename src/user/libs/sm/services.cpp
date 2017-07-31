#include <sm/services.hpp>
#include <btos/ini.hpp>
#include <cstring>

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
	strncpy(ret.name, name.c_str(), BT_MAX_SEGLEN);
	return ret;
}

}
}
