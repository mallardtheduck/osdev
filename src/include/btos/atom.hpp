#ifndef _ATOM_HPP
#define _ATOM_HPP

#include <btos.h>
#include "handle.hpp"

namespace btos_api{
	
	class Atom : public Handle{
	private:
	public:
		Atom(uint64_t i);
		uint64_t Modify(bt_atom_modify::Enum mod, uint64_t val = 0);
		uint64_t Wait(bt_atom_compare::Enum cmp, uint64_t val = 0);
		uint64_t CompareExchange(uint64_t cmp, uint64_t xchg);
		uint64_t Read();
	};

}

#endif
