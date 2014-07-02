#include "kernel.hpp"
#include "locks.hpp"

extern "C" void kernel_main(multiboot_info_t *mbd, unsigned int /*magic*/)
{
	if(are_interrupts_enabled()){
		panic("Interrupts not disabled at kernel load!\n");
	}
	init_serial();
	terminal_initialize();
	printf("%s %s\n%s\n", KERNEL_OS_NAME, KERNEL_VERSION_STRING, KERNEL_COPYRIGHT);
	GDT_init();
	IDT_init();
	init_cpu();
	vmm_init(mbd);
	disable_pic();
	PIC_init();
	enable_interrupts();
	sch_init();
	sch_yield();
	drv_init();
	terminal_add_device();
	fs_init();
	init_modules();
	load_module("INIT:/BOOT.SYS");
	//printf("Ready.");
	while(true)sch_block();
	panic("Kernel endpoint reached!\n");
}
