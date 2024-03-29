#include "kernel.hpp"
#include "locks.hpp"
#include <module/utils/unique_ptr.hpp>

class Atom;

struct WaitOptions{
	Atom *a;
	bt_atom_compare::Enum cmp;
	uint64_t value;
};

class Atom : public IAtom{
private:
	uint64_t value;
	unique_ptr<ILock> lock {NewLock()};

	static bool WaitBlockCheck(WaitOptions &p){
		if(!p.a->lock->TryTakeExclusive()) return false;
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
		p.a->lock->Release();
		return ret;
	}

	static void WaitHandleClose(WaitOptions *ptr){
		delete ptr;
	}

	static bool WaitHandleWait(WaitOptions *ptr){
		return WaitBlockCheck(*ptr);
	}
	
public:
	Atom(uint64_t v) : value(v) {}

	uint64_t Modify(bt_atom_modify::Enum mod, uint64_t v) override{
		auto hl = lock->LockExclusive();
		switch(mod){
			case bt_atom_modify::Set:
				value = v;
				break;
			case bt_atom_modify::Add:
				value += v;
				break;
			case bt_atom_modify::Subtract:
				value -= v;
				break;
			case bt_atom_modify::Or:
				value |= v;
				break;
			case bt_atom_modify::And:
				value &= v;
				break;
		}
		return value;
	}

	uint64_t Read() override{
		auto hl = lock->LockExclusive();
		return value;
	}

	uint64_t Wait(bt_atom_compare::Enum cmp, uint64_t value) override{
		WaitOptions p;
		p.a = this;
		p.cmp = cmp;
		p.value = value;
		CurrentThread().SetBlock([&](){ return WaitBlockCheck(p); });
		return Read();
	}
	uint64_t CompareExchange(uint64_t cmp, uint64_t xchg) override{
		auto hl = lock->LockExclusive();
		if(value == cmp) value = xchg;
		return value;
	}

	IHandle *MakeWaitHandle(bt_atom_compare::Enum cmp, uint64_t value) override{
		WaitOptions *p = new WaitOptions();
		p->a = this;
		p->cmp = cmp;
		p->value = value;
		return MakeKernelGenericHandle<KernelHandles::AtomWait>(p, &WaitHandleClose, &WaitHandleWait);
	}

	~Atom() {}
};

IAtom *NewAtom(uint64_t value){
	return new Atom(value);
}
