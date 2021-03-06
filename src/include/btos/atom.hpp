#ifndef _ATOM_HPP
#define _ATOM_HPP

#include <btos.h>
#include "handle.hpp"

namespace btos_api{

	struct AtomCompareOp{
		bt_atom_compare::Enum cmp;
		uint64_t val;

		AtomCompareOp(bt_atom_compare::Enum c, uint64_t v) : cmp(c), val(v) {} 
	};

	struct AtomModifyOp{
		bt_atom_modify::Enum mod;
		uint64_t val;

		AtomModifyOp(bt_atom_modify::Enum m, uint64_t v) : mod(m), val(v) {} 
	};
	
	class AtomValueClass{
	public:
		AtomCompareOp operator==(uint64_t val);
		AtomCompareOp operator!=(uint64_t val);
		AtomCompareOp operator<(uint64_t val);
		AtomCompareOp operator>(uint64_t val);

		AtomModifyOp operator=(uint64_t val);
		AtomModifyOp operator+=(uint64_t val);
		AtomModifyOp operator++();
		AtomModifyOp operator++(int);
		AtomModifyOp operator-=(uint64_t val);
		AtomModifyOp operator--();
		AtomModifyOp operator--(int);
		AtomModifyOp operator|=(uint64_t val);
		AtomModifyOp operator&=(uint64_t val);
	};

	extern AtomValueClass AtomValue;
	
	class AtomWait : public Handle{
	private:
		AtomWait(bt_handle_t a, bt_atom_compare::Enum cmp, uint64_t val);
		friend class Atom;
	public:
	};
	
	class Atom : public Handle{
	private:
	public:
		Atom(uint64_t i);
		uint64_t Modify(bt_atom_modify::Enum mod, uint64_t val = 0);
		uint64_t Modify(const AtomModifyOp &mod);
		uint64_t Wait(bt_atom_compare::Enum cmp, uint64_t val = 0) const;
		uint64_t WaitFor(const AtomCompareOp &cmp) const;
		AtomWait GetWait(bt_atom_compare::Enum cmp, uint64_t val = 0) const;
		AtomWait GetWaitFor(const AtomCompareOp &cmp) const;
		
		uint64_t CompareExchange(uint64_t cmp, uint64_t xchg);
		uint64_t Read() const;
	};

}

#endif
