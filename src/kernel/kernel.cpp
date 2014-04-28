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
	enable_interrupts();
	fs_init();
	printf("Ready.");
	asm volatile("hlt");
	panic("Kernel endpoint reached!\n");
}
