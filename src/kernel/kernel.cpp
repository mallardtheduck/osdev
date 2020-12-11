#include "kernel.hpp"
#include "locks.hpp"

multiboot_info_t *mbt;

extern "C" void kernel_main(multiboot_info_t *mbd, unsigned int /*magic*/)
{
	mbt = mbd;
	init_serial_debug();
	dbgpf("%s %s (Build ID:%s)\n%s\n", KERNEL_OS_NAME, KERNEL_VERSION_STRING, kernel_buildid, KERNEL_COPYRIGHT);
	HAL_Init();
	mm2_init(mbt);
	GetHAL().EnableInterrupts();
	init_kvars();
	proc_init();
	sch_init();
	sch_yield();
	drv_init();
	fs_init();
	infofs_init();
	init_modules();
	init_handles();
	userapi_init();
    init_extensions();
    msg_init();
	init_debug_extension();
	hwpnp_init();
	rtc_init();
	
	load_module("INIT:/BOOT.SYS");
	//printf("Ready.");
	while(true)sch_block();
	panic("Kernel endpoint reached!\n");
}
