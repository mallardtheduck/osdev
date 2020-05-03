#ifndef _SYMBOLS_HPP
#define _SYMBOLS_HPP

#include <string>
#include <vector>
#include <btos.h>
#include <cstdint>

struct symbol{
	std::string file;
	std::string name;
	std::string raw_name;
	std::string short_name;
	intptr_t address;
	intptr_t file_address;
	size_t size;
};

extern const symbol null_symbol;

struct module{
	std::string name;
	std::string path;
	intptr_t base;
	size_t limit;
};

std::vector<module> get_modules(btos_api::bt_pid_t pid);
std::vector<symbol> get_symbols(btos_api::bt_pid_t pid);
symbol get_symbol(const std::vector<symbol> &symbols, intptr_t addr);
symbol get_symbol_by_name(const std::vector<symbol> &symbols, const std::string &name);
std::vector<symbol> get_symbols_by_name(const std::vector<symbol> &symbols, const std::string &name);
std::vector<symbol> load_symbols(btos_api::bt_pid_t pid, bool force_reload = false);
std::vector<symbol> stack_symbols(btos_api::bt_pid_t pid, context ctx);

#endif
