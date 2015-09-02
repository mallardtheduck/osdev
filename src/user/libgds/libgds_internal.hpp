#ifndef _LIBGDS_INTERNAL_HPP
#define _LIBGDS_INTERNAL_HPP

#include <string>

std::string get_env(const std::string &name);
std::string get_env(const std::string &name, const std::string &def_value);
void set_env(const std::string &name, const std::string &value);

#endif