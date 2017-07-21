#ifndef _ENVVARS_HPP
#define _ENVVARS_HPP

#include <string>

namespace btos_api{

std::string GetEnv(const std::string &var);
void SetEnv(const std::string &var, const std::string &val);
std::string EnvInterpolate(const std::string &tmpl);

}

#endif
