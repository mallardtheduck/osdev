#ifndef _ISERVICERESOLVER_HPP
#define _ISERVICERESOLVER_HPP

#include <sm/services.hpp>
#include <string>
#include <vector>
#include <utility>

namespace btos_api{
namespace sm{

class IServiceResolver{
public:
	virtual std::pair<bool, Service> GetService(const std::string &name) = 0;
	virtual std::vector<Service> GetServices() = 0;	

	virtual ~IServiceResolver() {}
};

}
}

#endif
