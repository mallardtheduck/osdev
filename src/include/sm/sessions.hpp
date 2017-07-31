#ifndef _SESSIONS_HPP
#define _SESSIONS_HPP

#include <string>
#include <utility>
#include <map>
#include <functional>
#include <set>
#include <memory>

#include <btos/process.hpp>
#include <sm/services.hpp>
#include <sm/iserviceresolver.hpp>

namespace btos_api{
namespace sm{

class Session{
private:
	Process lead;
	std::set<Process> procs;
	std::map<std::string, std::shared_ptr<ServiceInstance>> services;
	std::shared_ptr<IServiceResolver> serviceResolver;
	
	Session(const Session&) = delete;
public:
	Session(const Process &p);
	Session(Session&&) = default;
	
	void SetServiceResolver(std::shared_ptr<IServiceResolver> sr);
	std::shared_ptr<IServiceResolver> GetServiceResolver();
	
	void Run();
	void End();

	void AddProcess(bt_pid_t pid);
	void RemoveProcess(bt_pid_t pid);
	void CleanUpServices();
	std::pair<bool, std::shared_ptr<ServiceInstance>> GetService(const std::string &name);
	std::pair<bool, std::shared_ptr<ServiceInstance>> StartService(const std::string &name, bool sticky = false);
	void ReleaseService(const std::string &name, bt_pid_t pid);
	void StopService(const std::string &name);
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
