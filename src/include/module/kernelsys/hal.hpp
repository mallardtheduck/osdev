#ifndef MODULE_HAL_HPP
#define MODULE_HAL_HPP

#include <cstddef>

typedef void (*ProcessEntryPoint)(void *);

class IScheduler;

enum class Generic_Register{
	GP_Register_A, GP_Register_B, GP_Register_C, GP_Register_D,
	Instruction_Pointer
};

class ICPUState{
public:
	virtual void DebugOutput() = 0;
	virtual void DebugStackTrace() const = 0;

	virtual uint32_t &Get32BitRegister(Generic_Register reg) = 0;
	virtual uint64_t &Get64BitRegister(Generic_Register reg) = 0;
	
	virtual uint32_t GetInterruptNo() const = 0;
	virtual uint32_t GetErrorCode() const = 0;
	virtual intptr_t GetPageFaultAddress() const = 0;

	virtual void BreakpointResume() = 0;

	virtual void *GetRAW() = 0;

	virtual ICPUState *Clone() const = 0;
	virtual void Copy(const ICPUState &other) = 0;

	virtual ~ICPUState() {}
};

typedef void (*ISR_Routine)(ICPUState&);

class InterruptLock;
class SchedulerLock;

class IHAL{
public:
	virtual const char *HWDescription() = 0;
	virtual const char *CPUIDString() = 0;

	virtual uint32_t GetCPUUMIPS() = 0;

	virtual void HandleInterrupt(size_t intNo, ISR_Routine isr) = 0;
	virtual void HandleIRQ(size_t irqNo, ISR_Routine isr) = 0;
	virtual void RawHandleInterrupt(size_t intNo, void *asm_isr) = 0;
	virtual void RawHandleIRQ(size_t irqNo, void *asm_isr) = 0;
	virtual bool AreInterruptsEnabled() = 0;
	virtual void EnableInterrupts() = 0;
	virtual void DisableInterrupts() = 0;
	virtual void EnableIRQ(int irq) = 0;
	virtual void DisableIRQ(int irq) = 0;

	InterruptLock LockInterrupts();
	
	virtual void HandlePageFault(ISR_Routine isr) = 0;
	virtual void HandleUserSyscall(ISR_Routine isr) = 0;
	virtual void HandleHWBreakpoint(ISR_Routine isr) = 0;
	virtual void HandleSWBreakpoint(ISR_Routine isr) = 0;

	virtual void AcknowlegdeIRQ(size_t irqNo) = 0;
	virtual void AcknowlegdeIRQIfPending(size_t irqNo) = 0;

	virtual const uint8_t *GetDefaultFPUState() = 0;
	virtual void SaveFPUState(uint8_t *buf) = 0;
	virtual void RestoreFPUState(const uint8_t *buf) = 0;
	virtual void InvalidateFPUState() = 0;

	virtual void SetSchedulerFrequency(int hz) = 0;
	virtual void YieldToScheduler() = 0;

	virtual const ICPUState &GetDefaultCPUState() = 0;

	virtual void IOOutByte(uint16_t port, uint8_t val) = 0;
	virtual uint8_t IOInByte(uint16_t port) = 0;

	virtual void HaltCPU() = 0;

	virtual uint64_t GenerateStackToken(intptr_t addr) = 0;

	virtual void RunUsermode(intptr_t stackPointer, ProcessEntryPoint entryPoint) = 0;

	virtual ~IHAL() { panic("HAL Destroyed!"); }
};

class InterruptLock{
private:
	IHAL &hal;
	bool enable;
public:
	InterruptLock(IHAL &h) : hal(h), enable(true){
		hal.DisableInterrupts();
	}

	InterruptLock(InterruptLock &&other) : hal(other.hal), enable(true){
		other.enable = false;
	}

	InterruptLock &operator=(InterruptLock &&other){
		new (this) InterruptLock((InterruptLock &&)other);
		return *this;
	}

	InterruptLock(const InterruptLock&) = delete;
	InterruptLock &operator=(const InterruptLock&) = delete;

	~InterruptLock(){
		if(enable)hal.EnableInterrupts();
	}
};

inline InterruptLock IHAL::LockInterrupts(){
	return InterruptLock(*this);
}

#endif