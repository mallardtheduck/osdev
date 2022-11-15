#ifndef _SYMBOLS_HPP
#define _SYMBOLS_HPP

#include <string>
#include <vector>
#include <btos.h>
#include <cstdint>
#include <memory>

struct symbol{
	std::shared_ptr<std::string> file;
	std::shared_ptr<std::string> name;
	std::shared_ptr<std::string> raw_name;
	std::shared_ptr<std::string> short_name;
	uintptr_t address;
	uintptr_t file_address;
	size_t size;
};

symbol get_null_symbol();

struct module{
	std::string name;
	std::string path;
	uintptr_t base;
	size_t limit;
};

std::vector<module> get_modules(btos_api::bt_pid_t pid);
std::vector<symbol> get_symbols(btos_api::bt_pid_t pid);
symbol get_symbol(const std::vector<symbol> &symbols, uintptr_t addr);
symbol get_symbol_by_name(const std::vector<symbol> &symbols, const std::string &name);
std::vector<symbol> get_symbols_by_name(const std::vector<symbol> &symbols, const std::string &name);
std::vector<symbol> load_symbols(btos_api::bt_pid_t pid, bool force_reload = false);
std::vector<symbol> stack_symbols(btos_api::bt_pid_t pid, context ctx);

#endif
