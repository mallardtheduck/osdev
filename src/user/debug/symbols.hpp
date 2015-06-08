#ifndef _SYMBOLS_HPP
#define _SYMBOLS_HPP

#include <string>
#include <vector>
#include <btos_api.h>

struct symbol{
	std::string name;
	intptr_t address;
};

std::vector<symbol> get_symbols(bt_pid_t pid);
symbol get_symbol(std::vector<symbol> symbols, intptr_t addr);

#endif