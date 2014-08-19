#ifndef _CMD_HPP
#define _CMD_HPP
#include "../../include/btos_stubs.h"
#include <string>

void print_os_version();
std::string get_env(const std::string &name);
std::string get_env(const std::string &name, const std::string &def_value);
void set_env(const std::string &name, const std::string &value);
std::string get_prompt();
std::string get_cwd();
std::string prompt_string();
std::string get_input();
void display_file(const std::string &path);

#endif
