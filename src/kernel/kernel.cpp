#include "kernel.hpp"
#include "locks.hpp"

extern "C" void kernel_main(multiboot_info_t *mbd, unsigned int magic)
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
	mm_init(mbd);
	disable_pic();
	PIC_init();
	enable_interrupts();
	sch_init();
	drv_init();
	terminal_add_device();
	fs_init();
	printf("Ready.");
	//while(true) asm volatile("hlt");
	int i=0;
	while(true){
		++i;
		terminal_move(0, 7);
		printf("%i ", i);
		sch_yield();
	}
	while(true)sch_block();
	panic("Kernel endpoint reached!\n");
}


void test_returnable(){
	sch_yield();
}
