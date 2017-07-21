#ifndef _SESSIONS_HPP
#define _SESSIONS_HPP

#include <string>
#include <btos/process.hpp>
#include <utility>

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

	btos_api::Process Start();
};

std::pair<bool, SessionType> GetSessionType(std::string &name);

#endif
