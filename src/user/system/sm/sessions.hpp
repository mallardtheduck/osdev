#ifndef _SESSIONS_HPP
#define _SESSIONS_HPP

#include <string>
#include <utility>
#include <map>

#include <btos/process.hpp>

class Session{
private:
	Process lead;
	std::vector<Process> procs;
	std::map<std::string, Process> services;
	
	Session(const Session&) = delete;
public:
	Session(const Process &p);
	Session(Session&&) = default;
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

std::pair<bool, SessionType> GetSessionType(std::string &name);

#endif
