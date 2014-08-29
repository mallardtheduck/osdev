#ifndef _AMM_HPP
#define _AMM_HPP

namespace amm_flags{
	enum Enum{
		Normal          = 0,
		Shared          = 1 << 1,
		Is_PageTable    = 1 << 2,
		File_Mapped     = 1 << 3,

		Do_Not_Use      = 1 << 9,
		Do_Not_Move     = 1 << 10,
		Do_Not_Swap     = 1 << 11,

		Kernel          = Do_Not_Move | Do_Not_Swap,
		User            = Normal,
		Guard_Page      = Do_Not_Use | Do_Not_Move | Do_Not_Swap,
		PageTable       = Is_PageTable | Do_Not_Move,
	};
}

void amm_init();
void amm_mark_alloc(uint32_t pageaddr, amm_flags::Enum flags, pid_t owner = proc_current_pid, void *ptr = NULL);
void amm_mark_free(uint32_t pageaddr);
amm_flags::Enum amm_get_flags(uint32_t pageaddr);

#endif