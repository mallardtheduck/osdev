#ifndef _PS2_HPP
#define _PS2_HPP

#include "module_stubs.h"
#include "module_cpp.hpp"
#include "keyboard.h"
#include "io.h"

uint8_t ps2_read_data();
uint8_t ps2_read_status();
void ps2_write_command(uint8_t byte);

#endif