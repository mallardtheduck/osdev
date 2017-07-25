#ifndef _SERVICES_HPP
#define _SERVICES_HPP

#include <string>
#include <map>
#include <utility>
#include <vector>

#include <btos/process.hpp>

namespace btos_api{
namespace sm{

class Service{
private:
	std::string name;
	std::string path;
	
	std::vector<bt_pid_t> refs;

public:
	Service(const std::string &n, const std::string &p) : name(n), path(p) {}
	Service() = default;

	Process Start();

	std::string Name();
	std::string Path();
};

}
}

#endif
