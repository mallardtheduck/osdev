#include <btos/atom.hpp>

namespace btos_api{

	AtomValueClass AtomValue;
	
	AtomCompareOp AtomValueClass::operator==(uint64_t val){
		return {bt_atom_compare::Equal, val};
	}

	AtomCompareOp AtomValueClass::operator!=(uint64_t val){
		return {bt_atom_compare::NotEqual, val};
	}

	AtomCompareOp AtomValueClass::operator<(uint64_t val){
		return {bt_atom_compare::LessThan, val};
	}

	AtomCompareOp AtomValueClass::operator>(uint64_t val){
		return {bt_atom_compare::GreaterThan, val};
	}

	AtomModifyOp AtomValueClass::operator=(uint64_t val){
		return {bt_atom_modify::Set, val};
	}

	AtomModifyOp AtomValueClass::operator+=(uint64_t val){
		return {bt_atom_modify::Add, val};
	}	

	AtomModifyOp AtomValueClass::operator++(){
		return {bt_atom_modify::Add, 1};
	}

	AtomModifyOp AtomValueClass::operator++(int){
		return {bt_atom_modify::Add, 1};
	}

	AtomModifyOp AtomValueClass::operator-=(uint64_t val){
		return {bt_atom_modify::Subtract, val};
	}

	AtomModifyOp AtomValueClass::operator--(){
		return {bt_atom_modify::Subtract, 1};
	}

	AtomModifyOp AtomValueClass::operator--(int){
		return {bt_atom_modify::Subtract, 1};
	}

	AtomModifyOp AtomValueClass::operator|=(uint64_t val){
		return {bt_atom_modify::Or, val};
	}

	AtomModifyOp AtomValueClass::operator&=(uint64_t val){
		return {bt_atom_modify::And, val};
	}

	Atom::Atom(uint64_t i) : Handle(bt_create_atom(i)) {}

	uint64_t Atom::Modify(bt_atom_modify::Enum mod, uint64_t val){
		return bt_modify_atom(handle, mod, val);
	}
	
	uint64_t Atom::Modify(const AtomModifyOp &mod){
		return Modify(mod.mod, mod.val);
	}

	uint64_t Atom::Wait(bt_atom_compare::Enum cmp, uint64_t val) const{
		return bt_wait_atom(handle, cmp, val);
	}

	uint64_t Atom::WaitFor(const AtomCompareOp &cmp) const{
		return Wait(cmp.cmp, cmp.val);
	}

	uint64_t Atom::CompareExchange(uint64_t cmp, uint64_t xchg){
		return bt_cmpxchg_atom(handle, cmp, xchg);
	}

	uint64_t Atom::Read() const{
		return bt_read_atom(handle);
	}

}
