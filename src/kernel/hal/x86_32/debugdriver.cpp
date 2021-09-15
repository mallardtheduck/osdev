#include "../../kernel.hpp"
#include <util/bitset.hpp>

static const uint32_t CR4_DE=(1 << 3);

static inline void debug_setdr(char dr, uint32_t value){
	switch(dr){
		case 0:
			asm volatile("mov %0, %%dr0":: "b"(value));
			break;
		case 1:
			asm volatile("mov %0, %%dr1":: "b"(value));
			break;
		case 2:
			asm volatile("mov %0, %%dr2":: "b"(value));
			break;
		case 3:
			asm volatile("mov %0, %%dr3":: "b"(value));
			break;

		case 6:
			asm volatile("mov %0, %%dr6":: "b"(value));
			break;
		case 7:
			asm volatile("mov %0, %%dr7":: "b"(value));
			break;
	};
}

static inline uint32_t debug_getdr(char dr){
	uint32_t ret = 0;
	switch(dr){
		case 0:
			asm volatile("mov %%dr0, %0": "=b"(ret));
			break;
		case 1:
			asm volatile("mov %%dr1, %0": "=b"(ret));
			break;
		case 2:
			asm volatile("mov %%dr2, %0": "=b"(ret));
			break;
		case 3:
			asm volatile("mov %%dr3, %0": "=b"(ret));
			break;

		case 6:
			asm volatile("mov %%dr6, %0": "=b"(ret));
			break;
		case 7:
			asm volatile("mov %%dr7, %0": "=b"(ret));
			break;
	};
	return ret;
}

static void configure_dr7(size_t i, bool enable, uint8_t type, uint32_t &dr7){
	BitSet dr7Bits(32);
	dr7Bits.SetBits((void*)&dr7, 32);
	auto controlIndex = i * 2;
	dr7Bits.Set(controlIndex + 0, enable);
	dr7Bits.Set(controlIndex + 1, enable);
	auto typeIndex = 16 + (i * 4);
	BitSet typeBits(8);
	typeBits.SetBits((void*)&type, 8);
	dr7Bits.Set(typeIndex + 0, typeBits.IsSet(0));
	dr7Bits.Set(typeIndex + 1, typeBits.IsSet(1));
	dr7Bits.Set(typeIndex + 2, typeBits.IsSet(2));
	dr7Bits.Set(typeIndex + 3, typeBits.IsSet(3));
	memcpy(&dr7, dr7Bits.GetBits(), 4);
}

static size_t debug_dridx(char dr){
	if(dr >= 0 && dr <= 3) return dr;
	if(dr == 6) return 4;
	if(dr == 7) return 5;
	return 0xFFFFFFFF;
}

static uint32_t debug_getbpinfo(ThreadPointer thread){
	uint32_t *state = thread->GetDebugState();
	if(!state) return 0;
	return state[debug_dridx(6)];
}

static void debug_clearbpinfo(ThreadPointer thread){
	uint32_t *state = thread->GetDebugState();
	if(!state) return;
	state[debug_dridx(6)] = 0;
}

class DebugDriver_x86_32 : public IDebugDriver{
public:
	bool SetBreakpoint(ThreadPointer thread, intptr_t address, uint8_t type) override{
		bool ret = false;
		if(!thread) return false;
		uint32_t *state = thread->GetDebugState();
		if(!state) return false;
		uint32_t dr7 = state[debug_dridx(7)];
		for(size_t i = 0; i < 4; ++i){
			if(state[debug_dridx(i)] == 0){
				state[debug_dridx(i)] = address;
				configure_dr7(i, true, type, dr7);
				ret = true;
				dbgpf("DEBUG: Set breakpoint %lu at %p for thread %llu (DR7: %lx).\n", i, (void*)address, thread->ID(), dr7);
				break;
			}
		}
		state[debug_dridx(7)] = dr7;
		return ret;
	}

	bool ClearBreakpoint(ThreadPointer thread, intptr_t address) override{
		bool ret = false;
		if(!thread) return false;
		uint32_t *state = thread->GetDebugState();
		if(!state) return false;
		uint32_t dr7 = state[debug_dridx(7)];
		for(size_t i = 0; i < 4; ++i){
			if(state[debug_dridx(i)] == (uint32_t)address){
				state[debug_dridx(i)] = 0;
				configure_dr7(i, false, 0, dr7);
				ret = true;
				break;
			}
		}
		state[debug_dridx(7)] = dr7;
		return ret;
	}

	intptr_t GetBreakAddress(ThreadPointer thread) override{	
		auto info = debug_getbpinfo(thread);
		if(info < 4){
			auto state = thread->GetDebugState();
			if(!state) return 0;
			return state[debug_dridx(info)];
		}
		return 0;
	}

	bool SingleStep(ThreadPointer thread) override{
		//TODO: Not implemented! (nor was it implemented in the old kernel)
		return false;
	}

	void Continue(ThreadPointer thread) override{	
		debug_clearbpinfo(thread);
	}

	void GetDebugState(uint32_t *buffer) override{
		buffer[0] = debug_getdr(0);
		buffer[1] = debug_getdr(1);
		buffer[2] = debug_getdr(2);
		buffer[3] = debug_getdr(3);
		buffer[4] = debug_getdr(6);
		buffer[5] = debug_getdr(7);
	}

	void SetDebugState(const uint32_t *buffer) override{
		debug_setdr(0, buffer[0]);
		debug_setdr(1, buffer[1]);
		debug_setdr(2, buffer[2]);
		debug_setdr(3, buffer[3]);
		debug_setdr(6, buffer[4]);
		debug_setdr(7, buffer[5]);
	}
};

static OnDemandStaticAlloc<DebugDriver_x86_32> theDebugDriver;

void DebugDriver_Init(){
	uint32_t cr4;
	asm volatile("mov %%cr4, %0": "=b"(cr4));
	cr4 |= CR4_DE;
	asm volatile("mov %0, %%cr4":: "b"(cr4));
	debug_setdr(7, 0xF00);
}

IDebugDriver &GetDebugDriver(){
	return *theDebugDriver;
}