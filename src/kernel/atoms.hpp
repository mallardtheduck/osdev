#ifndef _ATOMS_HPP
#define _ATOMS_HPP

#include "kernel.hpp"
#include <btos/atoms.h>

class IAtom{
public:
	virtual uint64_t Modify(bt_atom_modify::Enum mod, uint64_t value) = 0;
	virtual uint64_t Wait(bt_atom_compare::Enum cmp, uint64_t value) = 0;
	virtual uint64_t CompareExchange(uint64_t cmp, uint64_t xchg) = 0;

	virtual bt_handle_info MakeWaitHandle(bt_atom_compare::Enum cmp, uint64_t value) = 0;

	virtual uint64_t Read() = 0;

	virtual ~IAtom() {}
};

IAtom *NewAtom(uint64_t value);

#endif
