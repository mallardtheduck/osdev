#include "kernel.hpp"
#include "locks.hpp"

bt_atom *atom_create(uint64_t ini_val){
	bt_atom *ret = new bt_atom();
	init_lock(ret->lk);
	ret->value = ini_val;
	return ret;
}

void atom_destroy(bt_atom *a){
	take_lock_exclusive(a->lk);
	delete a;
	sch_abortable(true);
}

uint64_t atom_modify(bt_atom *a, bt_atom_modify::Enum mod, uint64_t value){
	hold_lock hl(a->lk);
	switch(mod){
		case bt_atom_modify::Set:
			a->value = value;
			break;
		case bt_atom_modify::Add:
			a->value += value;
			break;
		case bt_atom_modify::Subtract:
			a->value -= value;
			break;
		case bt_atom_modify::Or:
			a->value |= value;
			break;
		case bt_atom_modify::And:
			a->value &= value;
			break;
	}
	return a->value;
}

struct atom_wait_lockcheck_p{
	bt_atom *a;
	bt_atom_compare::Enum cmp;
	uint64_t value;
};

static bool atom_wait_lockcheck(void *vp){
	atom_wait_lockcheck_p &p = *(atom_wait_lockcheck_p*)vp;
	if(!try_take_lock_exclusive(p.a->lk)) return false;
	bool ret = false;
	switch(p.cmp){
		case bt_atom_compare::Equal:
			ret = (p.a->value == p.value);
			break;
		case bt_atom_compare::NotEqual:
			ret = (p.a->value != p.value);
			break;
		case bt_atom_compare::LessThan:
			ret = (p.a->value < p.value);
			break;
		case bt_atom_compare::GreaterThan:
			ret = (p.a->value > p.value);
			break;
	}
	release_lock(p.a->lk);
	return ret;
}

uint64_t atom_wait(bt_atom *a, bt_atom_compare::Enum cmp, uint64_t value){
	atom_wait_lockcheck_p p;
	p.a = a;
	p.cmp = cmp;
	p.value = value;
	sch_setblock(&atom_wait_lockcheck, (void*)&p);
	return atom_read(a);
}

uint64_t atom_cmpxchg(bt_atom *a, uint64_t cmp, uint64_t xchg){
	hold_lock hl(a->lk);
	if(a->value == cmp) a->value = xchg;
	return a->value;
}

uint64_t atom_read(bt_atom *a){
	hold_lock hl(a->lk);
	return a->value;
}

