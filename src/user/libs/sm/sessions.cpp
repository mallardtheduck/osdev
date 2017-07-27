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

using namespace std;
namespace btos_api{
namespace sm{

Session::Session(const Process &p) : lead(p), procs{ lead } {}

void Session::SetServiceResolver(function<pair<bool, Service>(const string&)> fn){
	serviceResolver = fn;
}

function<pair<bool, Service>(const string&)> Session::GetServiceResolver(){
	return serviceResolver;
}

void Session::AddProcess(bt_pid_t pid){
	ProcessList lst;
	for(auto p : lst){
		if(p.PID() == pid && procs.find(p.Parent()) != procs.end()){
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
		if(!i->second->IsSticky() && i->second->GetRefCount() == 0) {
			i->second->Stop();
			i = services.erase(i);
		}else ++i;
	}
}

pair<bool, shared_ptr<ServiceInstance>> Session::GetService(const string &name){
	if(services.find(name) != services.end()){
		return {true, services.at(name)};
	}else return StartService(name);
}

pair<bool, shared_ptr<ServiceInstance>> Session::StartService(const string &name, bool sticky){
	if(services.find(name) != services.end()){
		return {true, services.at(name)};
	}
	if(serviceResolver){
		auto r = serviceResolver(name);
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
				if(pid == lead.GetPID()){
					End();
					return false;
				} else if(procs.find(pid) != procs.end()){
					RemoveProcess(pid);
					CleanUpServices();
				}
			}
		}
		if(procs.find(msg.From()) != procs.end()){
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

SessionType::SessionType(const std::string &n, const std::string &l) : name(n), leadElx(l)
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
	return Process::Spawn(leadElx);
}

}
}

