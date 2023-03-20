#ifndef KERNEL_HAL_x86_32_HAL_HPP
#define KERNEL_HAL_x86_32_HAL_HPP

#include "../../kernel.hpp"

void DebugDriver_Init();
IDebugDriver &GetDebugDriver();

class CPUState_x86_32 : public ICPUState{
private:
	isr_regs *regs = nullptr;
public:
	CPUState_x86_32(isr_regs *r);
	CPUState_x86_32() = default;

	void DebugOutput() override;
	void DebugStackTrace() const override;

	uint32_t &Get32BitRegister(Generic_Register reg) override;
	uint64_t &Get64BitRegister(Generic_Register /*reg*/) override;

	uint32_t GetInterruptNo() const override;
	uint32_t GetIRQNo() const override;
	uint32_t GetErrorCode() const override;
	uintptr_t GetPageFaultAddress() const override;

	void BreakpointResume() override;

	void *GetRaw() override;
	size_t GetRawSize() override;

	ICPUState *Clone() const override;

	void Copy(const ICPUState &other) override;
};

#endif