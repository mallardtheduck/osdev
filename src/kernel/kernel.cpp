#include "kernel.hpp"

extern "C" void kernel_main(multiboot_info_t *mbd, unsigned int magic)
{
	if(are_interrupts_enabled()){
		panic("Interrupts not disabled at kernel load!\n");
	}
	init_serial();
	GDT_init();
	IDT_init();
	terminal_initialize();
	printf("%s %s\n%s\n", KERNEL_OS_NAME, KERNEL_VERSION_STRING, KERNEL_COPYRIGHT);
	init_cpu();
	mm_init(mbd);
	disable_pic();
	PIC_init();
	enable_interrupts();
	fs_init();
	sch_init();
	printf("Ready.");
	while(true) asm volatile("hlt");
	panic("Kernel endpoint reached!\n");
}
