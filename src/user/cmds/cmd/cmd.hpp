#ifndef _CMD_HPP
#define _CMD_HPP
#include <btos.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>

#include <cmd/commands.hpp>
#include <cmd/utils.hpp>
#include <cmd/path.hpp>
#include <cmd/globbing.hpp>

using namespace btos_api::cmd;

void print_os_version();
std::string get_input();

#endif
