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
	CurrentThread().SetAbortable(true);
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

struct atom_wait_options{
	bt_atom *a;
	bt_atom_compare::Enum cmp;
	uint64_t value;
};

static bool atom_wait_lockcheck(void *vp){
	atom_wait_options &p = *(atom_wait_options*)vp;
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
	atom_wait_options p;
	p.a = a;
	p.cmp = cmp;
	p.value = value;
	CurrentThread().SetBlock(&atom_wait_lockcheck, (void*)p);
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

static void atom_wait_close(void *ptr){
	delete (atom_wait_options*)ptr;
}

static bool atom_wait_wait(void *ptr){
	return atom_wait_lockcheck(ptr);
}

bt_handle_info atom_make_wait(bt_atom *a, bt_atom_compare::Enum cmp, uint64_t value){
	atom_wait_options *p = new atom_wait_options();
	p->a = a;
	p->cmp = cmp;
	p->value = value;
	return create_handle(kernel_handle_types::atomwait, (void*)p, &atom_wait_close, &atom_wait_wait);
}