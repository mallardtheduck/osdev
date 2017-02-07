#ifndef _SYMBOLS_HPP
#define _SYMBOLS_HPP

#include <string>
#include <vector>
#include <btos.h>
#include <cstdint>

struct symbol{
	std::string file;
	std::string name;
	intptr_t address;
};

struct module{
	std::string name;
	std::string path;
	intptr_t base;
	size_t limit;
};

std::vector<module> get_modules(bt_pid_t pid);
std::vector<symbol> get_symbols(bt_pid_t pid);
symbol get_symbol(const std::vector<symbol> &symbols, intptr_t addr);
symbol get_symbol_by_name(const std::vector<symbol> &symbols, std::string name);
std::vector<symbol> get_symbols_by_name(const std::vector<symbol> &symbols, std::string name);
void load_symbols(bt_pid_t pid);

#endif
