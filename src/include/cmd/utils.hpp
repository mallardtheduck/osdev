#ifndef _CMD_UTILS_HPP
#define _CMD_UTILS_HPP

#include <string>
#include <vector>

namespace btos_api{
namespace cmd{

bool is_dir(const std::string &path);
std::string to_lower(const std::string &str);
std::vector<std::string> split(const std::string &str, char delim);
void trim(std::string& str);
void trimchar(std::string &str, char c);
bool starts_with(const std::string &str, const std::string &start);
bool ends_with(const std::string &str, const std::string &end);
std::string tempfile();
std::vector<std::string> get_paths();
std::string get_prompt();
std::string get_cwd();
void set_cwd(const std::string &value);
std::string get_env(const std::string &name);
std::string get_env(const std::string &name, const std::string &def_value);
void set_env(const std::string &name, const std::string &value);
std::vector<std::string> parse_command(const std::string &input);
bool is_integer(const std::string &s);
std::string replace(const std::string &input, const std::string &target, const std::string &replacement);

}
}

#endif
