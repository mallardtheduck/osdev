#ifndef KERNEL_HAL_ABSTRACT_HPP
#define KERNEL_HAL_ABSTRACT_HPP

void HAL_Init();

typedef void (*ISR_Routine)(int, isr_regs*);

class IHAL{
public:
	virtual const char *HWDescription() = 0;
	virtual const char *CPUIDString() = 0;

	virtual uint32_t GetCPUUMIPS() = 0;

	virtual void HandleInterrupt(size_t intNo, ISR_Routine isr) = 0;
	virtual void HandleIRQ(size_t irqNo, ISR_Routine isr) = 0;
	virtual void RawHandleInterrupt(size_t intNo, void *asm_isr) = 0;
	virtual void RawHandleIRQ(size_t irqNo, void *asm_isr) = 0;
	virtual void AcknowlegdeIRQ(size_t irqNo) = 0;
	virtual void AcknowlegdeIRQIfPending(size_t irqNo) = 0;


	virtual uint8_t *GetDefaultFPUState() = 0;
	virtual void SaveFPUState(uint8_t *buf) = 0;
	virtual void RestoreFPUState(const uint8_t *buf) = 0;
	virtual void InvalidateFPUState() = 0;

	virtual ~IHAL() { panic("HAL Destroyed!"); }
};

IHAL &GetHAL();

#endif