#ifndef _LIBWM_INTERNAL_HPP
#define _LIBWM_INTERNAL_HPP

#include <string>

namespace libwm_internal{
	std::string get_env(const std::string &name);
	std::string get_env(const std::string &name, const std::string &def_value);
	void set_env(const std::string &name, const std::string &value);
}

using namespace libwm_internal;
#endif