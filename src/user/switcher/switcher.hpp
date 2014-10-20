#ifndef _SWITCHER_HPP
#define _SWITCHER_HPP

#include <string>
#include <vector>

std::vector<std::string> split(const std::string &str, char delim);
std::string get_env(const std::string &name);

#endif