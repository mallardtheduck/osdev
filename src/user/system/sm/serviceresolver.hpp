#ifndef _SERVICERESOLVER_HPP
#define _SERVICERESOLVER_HPP

#include <sm/iserviceresolver.hpp>

class SessionServiceResolver : public sm::IServiceResolver{
private:
	std::map<std::string, sm::Service> serviceCache;
public:
	SessionServiceResolver();
	std::pair<bool, sm::Service> GetService(const std::string &name) override;
	std::vector<sm::Service> GetServices() override;

	void UpdateCache();
};

#endif
