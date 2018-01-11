#ifndef _ATOMS_HPP
#define _ATOMS_HPP

#include "kernel.hpp"
#include <btos/atoms.h>

struct bt_atom{
	uint64_t value;
	lock lk;
};

bt_atom *atom_create(uint64_t ini_val);
void atom_destroy(bt_atom *a);
uint64_t atom_modify(bt_atom *a, bt_atom_modify::Enum mod, uint64_t value);
uint64_t atom_wait(bt_atom *a, bt_atom_compare::Enum cmp, uint64_t value);
uint64_t atom_cmpxchg(bt_atom *a, uint64_t cmp, uint64_t xchg);
uint64_t atom_read(bt_atom *a);

#endif
