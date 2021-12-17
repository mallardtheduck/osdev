#include "kernel.hpp"
#include "locks.hpp"

multiboot_info_t *mbt;

extern "C" void kernel_main(multiboot_info_t *mbd, unsigned int /*magic*/)
{
	mbt = mbd;
	Utils_Init();
	init_serial_debug();
	dbgpf("%s %s (Build ID:%s)\n%s\n", KERNEL_OS_NAME, KERNEL_VERSION_STRING, kernel_buildid, KERNEL_COPYRIGHT);
	HAL_Init();
	mm2_init(mbt);
	GetHAL().EnableInterrupts();
	KernelConfigVariables_Init();
	Scheduler_Init();
	Processes_Init();
	GetHAL().YieldToScheduler();
	Devices_Init();
	Filesystem_Init();
	Info_Init();
	Modules_Init();
	init_handles();
	userapi_init();
    Extensions_Init();
    Messaging_Init();
	init_debug_extension();
	hwpnp_init();
	rtc_init();
	
	GetModuleManager().LoadModule("INIT:/BOOT.SYS");
	//printf("Ready.");
	while(true) CurrentThread().Block();
	panic("Kernel endpoint reached!\n");
}
