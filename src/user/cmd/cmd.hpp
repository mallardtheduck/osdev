#ifndef _CMD_HPP
#define _CMD_HPP
#include "../../include/btos_stubs.h"
#include <string>
#include <vector>

void print_os_version();
std::string get_env(const std::string &name);
std::string get_env(const std::string &name, const std::string &def_value);
void set_env(const std::string &name, const std::string &value);
std::string get_prompt();
std::string get_cwd();
void set_cwd(const std::string &value);
std::string prompt_string();
std::string get_input();
void display_file(const std::string &path);
std::vector<std::string> parse_input(const std::string &input);
bool run_command(std::vector<std::string> commandline);
std::string parse_path(std::string path);
std::string to_lower(const std::string &str);

#endif
