#ifndef _SERVICERESOLVER_HPP
#define _SERVICERESOLVER_HPP

#include <sm/iserviceresolver.hpp>

class SessionServiceResolver : public btos_api::sm::IServiceResolver{
private:
	std::map<std::string, btos_api::sm::Service> serviceCache;
public:
	SessionServiceResolver();
	std::pair<bool, btos_api::sm::Service> GetService(const std::string &name) override;
	std::vector<btos_api::sm::Service> GetServices() override;

	void UpdateCache();
};

#endif
