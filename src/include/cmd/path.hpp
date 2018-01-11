#ifndef _CMD_PATH_HPP
#define _CMD_PATH_HPP

#include <string>

namespace btos_api{
namespace cmd{

std::string parse_path(std::string path);
bool is_directory(const std::string &path);
std::string path_file(const std::string &path);
std::string path_path(const std::string &fullpath);

}
}

#endif
