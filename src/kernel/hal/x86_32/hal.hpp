#ifndef KERNEL_HAL_x86_32_HAL_HPP
#define KERNEL_HAL_x86_32_HAL_HPP

#include "../../kernel.hpp"

class CPUState_x86_32 : public ICPUState{
private:
	isr_regs *regs;
public:
	CPUState_x86_32(isr_regs *r);

	void DebugOutput() override;
	void DebugStackTrace() const override;

	uint32_t &Get32BitRegister(Generic_Register reg) override;
	uint64_t &Get64BitRegister(Generic_Register /*reg*/) override;

	uint32_t GetInterruptNo() const override;
	uint32_t GetErrorCode() const override;
	intptr_t GetPageFaultAddress() const override;

	void BreakpointResume() override;

	void *GetRAW() override;

	ICPUState *Clone() const;
};

#endif