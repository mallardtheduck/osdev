#ifndef _SERVICES_HPP
#define _SERVICES_HPP

#include <string>
#include <map>
#include <utility>

#include <btos/process.hpp>

class Service{
private:
	std::string name;
	std::string path;

	Service(const std::string &n, const std::string &p) : name(n), path(p) {}

	friend std::pair<bool, Service> GetService(std::string name);
public:
	Service() = default;

	Process Start();

	std::string Name();
	std::string Path();
};

#endif
