#include "to_string.hpp"
#include <btos.h>

#include <sm/sessions.hpp>
#include <sm/sm.h>
#include <btos/ini.hpp>
#include <btos/messageloop.hpp>
#include <btos/imessagehandler.hpp>
#include <btos/processlist.hpp>
#include <btos/envvars.hpp>

#include <algorithm>
#include <type_traits>

#include <sstream>

#define dbgpf(...) do{snprintf(dbgbuf, 128, __VA_ARGS__); bt_zero(dbgbuf);}while(false)
#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)

using namespace std;
namespace btos_api{
namespace sm{

Session::Session(const Process &p) : lead(p), procs{ lead } {}

void Session::SetServiceResolver(shared_ptr<IServiceResolver> sr){
	serviceResolver = sr;
}

shared_ptr<IServiceResolver> Session::GetServiceResolver(){
	return serviceResolver;
}

void Session::AddProcess(bt_pid_t pid){
	ProcessList lst;
	for(auto p : lst){
		if(p.PID() == pid && (procs.find(p.Parent()) != procs.end() || p.Parent() == bt_getpid())){
			procs.insert(p.GetProcess());
		}
	}
}

void Session::RemoveProcess(bt_pid_t pid){
	for(auto s : services){
		s.second->RemoveRef(pid);
	}
	procs.erase(pid);
}

void Session::CleanUpServices(){
	for(auto i = services.begin(); i != services.end(); ){
		DBG("SM: Service: " << i->second->GetService().Name() << " users: " << i->second->GetRefCount() <<  " sticky: " << i->second->IsSticky());
		if(!i->second->IsSticky() && i->second->GetRefCount() == 0) {
			DBG("SM: Cleaning up service " << i->second->GetService().Name() << " (no users).");
			i->second->Stop();
			i = services.erase(i);
		}else if(i->second->GetProcess().GetStatus() == bt_proc_status::Ended){
			DBG("SM: Cleaning up service " << i->second->GetService().Name() << " (process " << i->second->GetProcess().GetPID() << " dead).");
			DBG("SM: Status: " << i->second->GetProcess().GetStatus());
			i = services.erase(i);
		}
		else ++i;
	}
}

pair<bool, shared_ptr<ServiceInstance>> Session::GetService(const string &name){
	if(services.find(name) != services.end()){
		return {true, services.at(name)};
	}else return StartService(name);
}

pair<bool, shared_ptr<ServiceInstance>> Session::StartService(const string &name, bool sticky){
	if(services.find(name) != services.end()){
		if(sticky) services.at(name)->SetSticky(true);
		return {true, services.at(name)};
	}
	if(serviceResolver){
		auto r = serviceResolver->GetService(name);
		if(r.first){
			auto s = r.second;
			auto i = make_shared<ServiceInstance>(s.Start());
			i->SetSticky(sticky);
			services.insert(make_pair(name, i));
			return {true, i};
		}
	}
	return {false, nullptr};
}

void Session::ReleaseService(const string &name, bt_pid_t pid){
	if(services.find(name) != services.end()){
		services.at(name)->RemoveRef(pid);
	}
}

void Session::StopService(const string &name){
	if(services.find(name) != services.end()){
		services.at(name)->Stop();
		services.erase(name);
	}
}

sm_ServiceInfo Session::ServiceInfo(const string &name){
	sm_ServiceInfo ret;
	if(serviceResolver){
		auto service = serviceResolver->GetService(name);
		if(service.first){
			ret = service.second.Info();
			if(services.find(name) != services.end()){
				ret.running = true;
				ret.pid = services.at(name)->GetProcess().GetPID();
				ret.users = services.at(name)->GetRefCount();
			}
		}
	}
	return ret;
}

void Session::Run(){
	bt_subscribe(bt_kernel_messages::ProcessStart);
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	
	MessageLoop msgLoop;
	msgLoop.AddHandler(make_shared<CustomHandler>( [&](const Message &msg) -> bool{
		if(msg.From() == 0 && msg.Source() == 0){
			if(msg.Type() == bt_kernel_messages::ProcessStart){
				auto pid = msg.Content<bt_pid_t>();
				AddProcess(pid);
			} else if(msg.Type() == bt_kernel_messages::ProcessEnd){
				auto pid = msg.Content<bt_pid_t>();
				DBG("SM: Process " << pid << " ending.");
				if(pid == lead.GetPID()){
					End();
					return false;
				} else if(procs.find(pid) != procs.end()){
					RemoveProcess(pid);
					CleanUpServices();
				}else{
					DBG("SM: Process " << pid << " not part of session.");
				}
			}
		} else {
		//if(procs.find(msg.From()) != procs.end()){
			switch(msg.Type()){
				case sm_RequestType::GetService:{
					string name = (char*)msg.Content();
					bt_pid_t servicePid = 0;
					auto i = GetService(name);
					if(i.first){
						i.second->AddRef(msg.From());
						servicePid = i.second->GetProcess().GetPID();
						procs.insert(servicePid);
					}
					msg.SendReply(servicePid);
				}break;
				case sm_RequestType::StartService:{
					string name = (char*)msg.Content();
					bt_pid_t servicePid = 0;
					auto i = StartService(name, true);
					if(i.first){
						i.second->AddRef(msg.From());
						servicePid = i.second->GetProcess().GetPID();
						procs.insert(servicePid);
					}
					msg.SendReply(servicePid);
				}break;
				case sm_RequestType::ReleaseService:{
					string name = (char*)msg.Content();
					ReleaseService(name, msg.From());
					CleanUpServices();
				}break;
				case sm_RequestType::StopService:{
					string name = (char*)msg.Content();
					StopService(name);
				}break;
				case sm_RequestType::GetServiceCount:{
					if(serviceResolver){
						msg.SendReply(serviceResolver->GetServices().size());
					}else{
						msg.SendReply(size_t(0));
					}
				}break;
				case sm_RequestType::GetServiceInfo:{
					if(serviceResolver){
						auto index = msg.Content<size_t>();
						auto svcs = serviceResolver->GetServices();
						if(svcs.size() > index){
							auto info = ServiceInfo(svcs[index].Name());					
							msg.SendReply(info);
						}else{
							msg.SendReply(sm_ServiceInfo());
						}
					}else{
						msg.SendReply(sm_ServiceInfo());
					}
				}break;
			}
		}
		return true;
	}));
	msgLoop.RunLoop();
}

void Session::End(){
	for(auto s : services) s.second->Stop();
	services.clear();
	for(auto p : procs) p.Kill();
	procs.clear();
}

SessionType::SessionType(const string &n, const string &l, const vector<string> &s) : name(n), leadElx(l), autoServices(s)
{}

string SessionType::GetName(){
	return name;
}

void SessionType::SetName(const string &n){
	name = n;
}

string SessionType::GetLeadElx(){
	return leadElx;
}

void SessionType::SetLeadElx(const string &l){
	leadElx = l;
}

Session SessionType::Start(){
	SetEnv("SM_PID", to_string(bt_getpid()));
	auto c = ParseCmd(leadElx);
	Session ret {Process::Spawn(c.first, c.second)};
	for(auto s : autoServices){
		ret.StartService(s, true);
	}
	return ret;
}

void SessionType::AddAutoService(const string &name){
	autoServices.push_back(name);
}
void SessionType::SetAutoServices(const vector<string> &svcs){
	autoServices = svcs;
}
vector<string> SessionType::GetAutoServices(){
	return autoServices;
}

}
}

