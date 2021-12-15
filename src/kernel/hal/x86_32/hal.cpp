#include "../../kernel.hpp"
#include "cpu.hpp"
#include "idt.hpp"
#include "hal.hpp"
#include "io.hpp"
#include "pic.hpp"

void GDT_init();

extern void HAL_sch_init();
extern "C" void sch_yield();
bool sch_inited = false;
extern char sch_isr_asm;

extern "C" void proc_run_usermode(uintptr_t stack, ProcessEntryPoint entry);

void HAL_Init(){
	GDT_init();
	IDT_init();
	init_cpu();
	disable_pic();
	PIC_init();
	HAL_sch_init();
}

const CPUState_x86_32 theDefaultCPUState;

CPUState_x86_32::CPUState_x86_32(isr_regs *r) : regs(r) {}

void CPUState_x86_32::DebugOutput(){
	out_int_info(*regs);
}

void CPUState_x86_32::DebugStackTrace() const{
	isr_regs *ctx = regs;
	uint32_t bp = 0;
	uint32_t stack[2] = {ctx->ebp, ctx->eip};
	for(int count = 0; count < 100; ++count){
		dbgpf("STACK TRACE: %i : %lx (EBP: %lx)\n", count, stack[1], stack[0]);
		if(stack[0] != bp){ 
			bp = stack[0];
			if(bp < 4096){
				dbgout("STACK CORRUPT.\n");
				break;
			}
			memcpy((void*)stack, (void*)bp, sizeof(stack));
		}
		else break;
	}
}

uint32_t &CPUState_x86_32::Get32BitRegister(Generic_Register reg){
	static uint32_t unused = -1;
	switch(reg){
		case Generic_Register::GP_Register_A:
			return *&regs->eax;
		case Generic_Register::GP_Register_B:
			return *&regs->ebx;
		case Generic_Register::GP_Register_C:
			return *&regs->ecx;
		case Generic_Register::GP_Register_D:
			return *&regs->edx;
		case Generic_Register::Instruction_Pointer:
			return *&regs->eip;
	}
	return unused;
}

uint64_t &CPUState_x86_32::Get64BitRegister(Generic_Register /*reg*/){
	static uint64_t unused = -1;
	return unused;
}

uint32_t CPUState_x86_32::GetInterruptNo() const{
	return regs->interrupt_number;
}

uint32_t CPUState_x86_32::GetErrorCode() const{
	return regs->error_code;
}

uintptr_t CPUState_x86_32::GetPageFaultAddress() const{
	uintptr_t addr;
	asm volatile("mov %%cr2, %%eax\r\n mov %%eax,%0": "=m"(addr): : "eax");
	return addr;
}

void CPUState_x86_32::BreakpointResume(){
	regs->eflags |= (1 << 16);
}

void *CPUState_x86_32::GetRAW(){
	return (void*)regs;
}

ICPUState *CPUState_x86_32::Clone() const{
	return new CPUState_x86_32(*this);
}

void CPUState_x86_32::Copy(const ICPUState &other){
	regs = static_cast<const CPUState_x86_32&>(other).regs;
}

class HAL_x86_32 : public IHAL{
public:
	const char *HWDescription() override{
		return "32-bit x86-compatible system";
	}
	const char *CPUIDString() override{
		return cpu_idstring();
	}

	uint32_t GetCPUUMIPS() override{
		return cpu_get_umips();
	}

	void HandleInterrupt(size_t intNo, ISR_Routine isr) override{
		int_handle(intNo, isr);
	}

	void HandleIRQ(size_t irqNo, ISR_Routine isr) override{
		irq_handle(irqNo, isr);
	}

	void RawHandleInterrupt(size_t intNo, void *asm_isr) override{
		int_handle_raw(intNo, asm_isr);
	}

	void RawHandleIRQ(size_t irqNo, void *asm_isr) override{
		irq_handle_raw(irqNo, asm_isr);
	}

	bool AreInterruptsEnabled() override{
		return are_interrupts_enabled();
	}

	void EnableInterrupts() override{
		enable_interrupts();
	}

	void DisableInterrupts() override{
		disable_interrupts();
	}

	void EnableIRQ(int irq){
		IRQ_clear_mask(irq);
	}

	void DisableIRQ(int irq){
		IRQ_set_mask(irq);
	}

	void HandlePageFault(ISR_Routine isr) override{
		HandleInterrupt(0x0E, isr);
	}

	void HandleUserSyscall(ISR_Routine isr) override{
		HandleInterrupt(0x80, isr);
	}

	void HandleHWBreakpoint(ISR_Routine isr) override{
		HandleInterrupt(1, isr);
	}

	void HandleSWBreakpoint(ISR_Routine isr) override{
		HandleInterrupt(3, isr);
	}

	void AcknowlegdeIRQ(size_t irqNo) override{
		irq_ack(irqNo);
	}

	void AcknowlegdeIRQIfPending(size_t irqNo) override{
		irq_ack_if_needed(irqNo);
	}

	const uint8_t *GetDefaultFPUState() override{
		return default_fpu_xmm_data;
	}

	void SaveFPUState(uint8_t *buf) override{
		save_fpu_xmm_data(buf);
	}

	void RestoreFPUState(const uint8_t *buf) override{
		restore_fpu_xmm_data(buf);
	}

	void InvalidateFPUState() override{
		fpu_switch();
	}

	void SetSchedulerFrequency(int hz) override{
		uint16_t value=193182 / hz;
		dbgpf("SCH: Scheduler frequency: %i\n", (int)hz);
		outb(0x43, 0x36);
		outb(0x40, value & 0xFF);
		outb(0x40, (value >> 8) & 0xFF);
		sch_inited = true;
		RawHandleIRQ(0, (void*)&sch_isr_asm);
	}

	void YieldToScheduler() override{
		sch_yield();
	}

	const ICPUState &GetDefaultCPUState() override{
		return theDefaultCPUState;
	}

	virtual void IOOutByte(uint16_t port, uint8_t val) override{
		outb(port, val);
	}

	virtual uint8_t IOInByte(uint16_t port) override{
		return inb(port);
	}

	virtual void HaltCPU() override{
		asm volatile("hlt");
	}

	uint64_t GenerateStackToken(uintptr_t addr){
		return (0x10ll << 32) | addr;
	}

	void RunUsermode(uintptr_t stackPointer, ProcessEntryPoint entryPoint){
		proc_run_usermode(stackPointer, entryPoint);
	}

	IDebugDriver &GetDebugDriver(){
		return ::GetDebugDriver();
	}
};

HAL_x86_32 theHAL;

IHAL &GetHAL(){
	DebugDriver_Init();
	return theHAL;
}