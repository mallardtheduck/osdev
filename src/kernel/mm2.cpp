#include "kernel.hpp"
#include "mm2/mm2_internal.hpp"

void mm2_init(multiboot_info_t *mbt){
	dbgout("MM2: Init.\n");
	MM2::mm2_physical_init(mbt);
	MM2::mm2_virtual_init();
	panic("(MM2) MM2 is not finished!");
}