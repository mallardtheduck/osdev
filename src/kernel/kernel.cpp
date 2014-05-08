#include "kernel.hpp"
#include "locks.hpp"

void t(void *){
	dbgpf("T: %i\n", (uint32_t)sch_get_id());
	while(true){
		void *alloc=mm_alloc(4096);
		printf("*");
		mm_free(alloc);
		printf("-");
	}		
}

lock t_lock;

void t2(void *){
	dbgpf("T2: %i\n", (uint32_t)sch_get_id());
	while(true){
		take_lock(t_lock);
		if(t_lock!=sch_get_id())panic("(TEST) Faulty locking detected!\n");
		sch_yield();
		release_lock(t_lock);
		sch_yield();
	}
}

void t3(void *){
	dbgpf("T3: %i\n", (uint32_t)sch_get_id());
	hold_lock hl(t_lock);
	while(true){
		if(t_lock!=sch_get_id())panic("(TEST) Faulty locking detected!\n");
		sch_yield();
	}
}

void t4(void *){
	dbgpf("T4: %i\n", (uint32_t)sch_get_id());
	dbgpf("TEST: Doing nothing.\n");
}

void t5(void *){
	while(true){
		dbgpf("T5: %i\n", (uint32_t)sch_get_id()); 
		sch_yield();
	}
}

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
	//drv_init();
	//terminal_add_device();
	//fs_init();
	printf("Ready.");
	//while(true) asm volatile("hlt");
	int i=0;
	//sch_new_thread(&t, NULL);
	sch_new_thread(&t2, NULL);
	sch_new_thread(&t3, NULL);
	sch_new_thread(&t4, NULL);
	sch_new_thread(&t5, NULL);
	while(true){
		void *alloc=mm_alloc(4096);
		++i;
		terminal_move(0, 7);
		printf("%i ", i);
		sch_yield();
		mm_free(alloc);
		printf("~");
	}
	while(true)sch_block();
	panic("Kernel endpoint reached!\n");
}

