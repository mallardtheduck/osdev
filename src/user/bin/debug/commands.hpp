#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP

#include <string>

std::string input_command();
bool do_command(std::string cmd);

void watch_thread(void *);

#endif
