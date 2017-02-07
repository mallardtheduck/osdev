#ifndef _EL_LOAD_ELF_HPP
#define _EL_LOAD_ELF_HPP

#include "elf.hpp"

struct loaded_module{
	uint32_t id;
	char *name;
	char *full_path;
	Elf32_Dyn *dynamic;
	intptr_t base;
	size_t limit;
	bool is_dynamic;
};

extern loaded_module *loaded_modules;
extern size_t loaded_module_count;

typedef void (*entrypoint)();

entrypoint load_elf_proc(bt_handle_t file, const char *path);
uint32_t load_elf_library(bt_handle_t file, const char *name, const char *full_path, bool dynamic = false);
void add_symbol_override(const char *name, intptr_t value);
intptr_t get_symbol_by_name(const loaded_module &module, const char *symname, size_t *sym_size = NULL, bool allow_self = true, bool ignore_overrides = false, bool warn = false);

#endif
