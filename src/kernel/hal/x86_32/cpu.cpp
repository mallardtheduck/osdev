#include "../../kernel.hpp"
#include "cpu.hpp"
#include "idt.hpp"
#include "io.hpp"

extern "C"{
	#include "cpuid.h"
}

void init_fpu_xmm();
void fpu_nm_handler(ICPUState&);

static bool fpu_exists=false;
static bool sse_available=false;

uint8_t default_fpu_xmm_data[512];

static inline int cpuid_string(int code, int where[4]) {
  __asm__ volatile ("cpuid":"=a"(*where),"=b"(*(where+0)),
               "=d"(*(where+1)),"=c"(*(where+2)):"a"(code));
  return (int)where[0];
}

void init_cpu(){
	char *idstring=cpu_idstring();
	uint64_t speed=cpu_get_speed();	
	char *brandstring=get_brandstring();
	dbgpf("CPU: %s %s. Speed: %i UMIPS.\n", idstring, brandstring, (int)(speed/1000000));
	uint32_t a, b, c, d;
	cpuid(1, a, b, c, d);
	if(d & cpu_features::CPUID_FEAT_EDX_FPU) {
		dbgout("CPU: FPU detected.\n");
		fpu_exists=true;
	}
	if(d & cpu_features::CPUID_FEAT_EDX_SSE) {
		dbgout("CPU: SSE support detected.\n");
		sse_available=true;
	}
	init_fpu_xmm();
}

char *cpu_idstring() {
	static char s[16] = "UNKNOWN CPU.";
	cpuid_string(0, (int*)(s));
	return s;
}

char *cpu_brandstring(){
	return get_brandstring();
}

uint64_t cpu_get_speed(){
	static uint64_t speed = 0;
	if(!speed){
		outb(0x43,0x34);
		outb(0x40,0);
		outb(0x40,0);
		uint64_t start = rdtsc();
		for (volatile int i=0x10000;i>0;i--) (void)i;
		outb(0x43,0x04);
		uint64_t end=rdtsc();
		uint8_t lo=inb(0x40);
		uint8_t hi=inb(0x40);
		uint32_t ticks=(0x10000 - (hi*256+lo));
		speed = (end-start)*1193180 / ticks;
	}
	return speed;
}

uint32_t cpu_get_umips(){
    return cpu_get_speed() / 1000000;
}

void init_fpu_xmm(){
	if(fpu_exists) {
		uint32_t cr0;
		asm volatile("mov %%cr0, %0": "=b"(cr0));
		cr0 &= ~(1 << 2);
		cr0 |= (1 << 1);
		cr0 |= (1 << 5);
		asm volatile("mov %0, %%cr0":: "b"(cr0));
		reset_fpu();
		save_fpu_xmm_data(default_fpu_xmm_data);
		fpu_switch();
		int_handle(0x07, &fpu_nm_handler);
		int_handle(0x10, &fpu_nm_handler);
		if(sse_available){
			uint32_t cr4;
			asm volatile("mov %%cr4, %0": "=b"(cr4));
			cr4 |= (1 << 9);
			cr4 |= (1 << 10);
			asm volatile("mov %0, %%cr4":: "b"(cr4));
		}
	}
}

void fpu_switch() {
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 |= (1 << 3);
	asm volatile("mov %0, %%cr0":: "b"(cr0));
}

void fpu_ready() {
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	cr0 &= ~(1 << 3);
	asm volatile("mov %0, %%cr0":: "b"(cr0));
}

void reset_fpu(){
	asm volatile("fninit");
}

static uint8_t fpu_xmm_data_region[512] __attribute__((aligned(16)));

void save_fpu_xmm_data(uint8_t *data){
	uint32_t cr0;
	asm volatile("mov %%cr0, %0": "=b"(cr0));
	if((cr0 & (1 << 3))) return;
	if(sse_available){
		asm volatile("fxsave %0 " : "=m"(fpu_xmm_data_region));
	}else{
		asm volatile("fsave %0" : "=m"(fpu_xmm_data_region));
	}
	memcpy(data, fpu_xmm_data_region, 512);
}

void restore_fpu_xmm_data(const uint8_t *data){
	memcpy(fpu_xmm_data_region, data, 512);
	if(sse_available){
		asm volatile("fxrstor %0" :: "m"(fpu_xmm_data_region));
	}else{
		asm volatile("frstor %0" ::  "m"(fpu_xmm_data_region));
	}
}

void fpu_nm_handler(ICPUState &){
	fpu_ready();
	restore_fpu_xmm_data(sch_get_fpu_xmm_data());
}