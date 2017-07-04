#include <btos/atom.hpp>

namespace btos_api{
	
	Atom::Atom(uint64_t i) : Handle(bt_create_atom(i)) {}

	uint64_t Atom::Modify(bt_atom_modify::Enum mod, uint64_t val){
		return bt_modify_atom(handle, mod, val);
	}
	
	uint64_t Atom::Wait(bt_atom_compare::Enum cmp, uint64_t val) const{
		return bt_wait_atom(handle, cmp, val);
	}

	uint64_t Atom::CompareExchange(uint64_t cmp, uint64_t xchg){
		return bt_cmpxchg_atom(handle, cmp, xchg);
	}

	uint64_t Atom::Read() const{
		return bt_read_atom(handle);
	}

}
