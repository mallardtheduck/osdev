#ifndef _COMMANDS_HPP
#define _COMMANDS_HPP

#include <string>

extern volatile btos_api::bt_pid_t selected_pid;
extern volatile uint64_t selected_thread;

std::string input_command();
bool do_command(std::string cmd);

void watch_thread(void *);

#endif
