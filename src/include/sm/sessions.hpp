#ifndef _SESSIONS_HPP
#define _SESSIONS_HPP

#include <string>
#include <utility>
#include <map>
#include <functional>
#include <vector>
#include <set>

#include <btos/process.hpp>
#include <sm/services.hpp>

namespace btos_api{
namespace sm{

class Session{
private:
	struct ServiceInstance{
		Process proc;
		Service service;
		std::set<bt_pid_t> refs;
		
		ServiceInstance(Process p, Service s) : proc(p), service(s) {}
	};

	Process lead;
	std::vector<Process> procs;
	std::map<std::string, ServiceInstance> services;
	std::function<std::pair<bool, Service>(const std::string&)> serviceResolver;
	
	Session(const Session&) = delete;
public:
	Session(const Process &p);
	Session(Session&&) = default;
	
	void SetServiceResolver(std::function<std::pair<bool, Service>(const std::string&)> fn);
	std::function<std::pair<bool, Service>(const std::string&)> GetServiceResolver();
	
	void Run();
	void End();
};

class SessionType{
private:
	std::string name;
	std::string leadElx;
	
public:
	SessionType() = default;
	SessionType(const std::string &n, const std::string &l);

	std::string GetName();
	void SetName(const std::string &n);

	std::string GetLeadElx();
	void SetLeadElx(const std::string &l);

	Session Start();
};

}
}

#endif
