#ifndef _CONFIG_HPP
#define _CONFIG_HPP

#include <string>

const std::string ConfigFilePath = "/btos/config/wm.ini";

void ParseConfig(const std::string &path);
std::string GetConfigValue(const std::string &name);

#endif
