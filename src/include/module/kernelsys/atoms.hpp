#ifndef MODULE_ATOMS_HPP
#define MODULE_ATOMS_HPP

#include <cstdint>
#include <btos/atoms.h>
#include <util/noncopyable.hpp>

#include "handles.hpp"

class IAtom : private nonmovable{
public:
	virtual uint64_t Modify(bt_atom_modify::Enum mod, uint64_t value) = 0;
	virtual uint64_t Wait(bt_atom_compare::Enum cmp, uint64_t value) = 0;
	virtual uint64_t CompareExchange(uint64_t cmp, uint64_t xchg) = 0;

	virtual IHandle *MakeWaitHandle(bt_atom_compare::Enum cmp, uint64_t value) = 0;

	virtual uint64_t Read() = 0;

	virtual ~IAtom() {}
};

#endif