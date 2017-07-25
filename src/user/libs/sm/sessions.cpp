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
	
template<typename T> bool has_element(T container, typename T::value_type element){
	static_assert(is_same<decltype(declval<T>().begin()), decltype(declval<T>().end())>::value, "container must have valid iterators!");
	
	return find(container.begin(), container.end(), element) != container.end();
}

Session::Session(const Process &p) : lead(p), procs{ lead } {}

void Session::SetServiceResolver(function<pair<bool, Service>(const string&)> fn){
	serviceResolver = fn;
}

function<pair<bool, Service>(const string&)> Session::GetServiceResolver(){
	return serviceResolver;
}

void Session::Run(){
	bt_subscribe(bt_kernel_messages::ProcessStart);
	bt_subscribe(bt_kernel_messages::ProcessEnd);
	
	MessageLoop msgLoop;
	msgLoop.AddHandler(make_shared<CustomHandler>( [&](const Message &msg) -> bool{
		if(msg.From() == 0 && msg.Source() == 0){
			if(msg.Type() == bt_kernel_messages::ProcessStart){
				auto pid = msg.Content<bt_pid_t>();
				ProcessList lst;
				for(auto p : lst){
					if(p.PID() == pid && has_element(procs, p.Parent())){
						procs.push_back(p.GetProcess());
					}
				}
			} else if(msg.Type() == bt_kernel_messages::ProcessEnd){
				auto pid = msg.Content<bt_pid_t>();
				if(pid == lead.GetPID()){
					for(auto p : procs) p.Kill();
					procs.clear();
					for(auto s : services) s.second.proc.Kill();
					services.clear();
					return false;
				} else if(has_element(procs, pid)){
					for(auto s : services){
						if(s.second.refs.find(pid) != s.second.refs.end()){
							s.second.refs.erase(pid);
							if(s.second.refs.size() == 0) s.second.proc.Kill();
						}
					}
					for(auto i = services.begin(); i != services.end(); ){
						if(i->second.refs.size() == 0) i = services.erase(i);
						else ++i;
					}
					remove(procs.begin(), procs.end(), pid);
				}
			}
		}
		if(has_element(procs, msg.From())){
			switch(msg.Type()){
				case sm_RequestType::GetService:{
					string name = (char*)msg.Content();
					bt_pid_t servicePid = 0;
					if(services.find(name) != services.end()){
						auto &i = services.at(name);
						i.refs.insert(msg.From());
						servicePid = i.proc.GetPID();
					}else if(serviceResolver){
						auto r = serviceResolver(name);
						if(r.first){
							auto s = r.second;
							auto p = s.Start();
							ServiceInstance i {p, s};
							i.refs.insert(msg.From());
							services.insert(make_pair(name, i));
							servicePid = p.GetPID();
						}
					}
					msg.SendReply(servicePid);
				}break;
			}
		}
		return true;
	}));
	msgLoop.RunLoop();
}

void Session::End(){
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

