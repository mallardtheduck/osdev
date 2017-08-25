#ifndef _SCRIPT_COMMANDS_HPP
#define _SCRIPT_COMMANDS_HPP

#include "commands.hpp"

namespace btos_api{
namespace cmd{

void echo_command(const command &cmd);
void int_command(const command &cmd);
void str_command(const command &cmd);
void arr_command(const command &cmd);

}
}

#endif
