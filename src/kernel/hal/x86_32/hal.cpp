#include "../../kernel.hpp"
#include "cpu.hpp"
#include "idt.hpp"

void GDT_init();

void HAL_Init(){
	GDT_init();
	IDT_init();
	init_cpu();
}

class HAL_x86_32 : public IHAL{
public:
	const char *HWDescription(){
		return "32-bit x86-compatible system";
	}
	const char *CPUIDString(){
		return cpu_idstring();
	}

	uint32_t GetCPUUMIPS(){
		return cpu_get_umips();
	}

	void HandleInterrupt(size_t intNo, ISR_Routine isr){
		int_handle(intNo, isr);
	}

	void HandleIRQ(size_t irqNo, ISR_Routine isr){
		irq_handle(irqNo, isr);
	}

	void RawHandleInterrupt(size_t intNo, void *asm_isr){
		int_handle_raw(intNo, asm_isr);
	}

	void RawHandleIRQ(size_t irqNo, void *asm_isr){
		irq_handle_raw(irqNo, asm_isr);
	}

	void AcknowlegdeIRQ(size_t irqNo){
		irq_ack(irqNo);
	}

	void AcknowlegdeIRQIfPending(size_t irqNo){
		irq_ack_if_needed(irqNo);
	}

	uint8_t *GetDefaultFPUState(){
		return default_fpu_xmm_data;
	}

	void SaveFPUState(uint8_t *buf){
		save_fpu_xmm_data(buf);
	}
	void RestoreFPUState(const uint8_t *buf){
		restore_fpu_xmm_data(buf);
	}

	void InvalidateFPUState(){
		fpu_switch();
	}
};

HAL_x86_32 theHAL;

IHAL &GetHAL(){
	return theHAL;
}