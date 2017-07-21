#ifndef _ENVVARS_HPP
#define _ENVVARS_HPP

#include <string>
#include <functional>

namespace btos_api{

std::string GetEnv(const std::string &var);
void SetEnv(const std::string &var, const std::string &val);
std::string Interpolate(const std::string &tmpl, std::function<std::string(const std::string&)> lookup);
std::string EnvInterpolate(const std::string &tmpl);

}

#endif
